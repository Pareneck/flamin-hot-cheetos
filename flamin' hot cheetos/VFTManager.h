#ifndef VFTMANAGER_H
#define VFTMANAGER_H

#pragma once

#include <Windows.h>
#include <stdio.h>
#include <map>
#include <stdint.h>

typedef DWORD** PPDWORD;

class VFTManager
{
	VFTManager(const VFTManager&) = delete;

public:
	VFTManager(PPDWORD classBase, bool shouldReplace)
	{
		classBase_ = classBase;
		shouldReplace_ = shouldReplace;

		if (shouldReplace_)
		{
			originalTable_ = *classBase;
			uint32_t length = computeLength();

			newTable_ = new DWORD[length];
			memcpy(newTable_, originalTable_, length * sizeof(DWORD));

			DWORD old;
			VirtualProtect(classBase_, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
			*classBase_ = newTable_;
			VirtualProtect(classBase_, sizeof(DWORD), old, &old);
		}
		else
		{
			originalTable_ = *classBase;
			newTable_ = *classBase;
		}
	}

	~VFTManager()
	{
		restoreTable();

		if (shouldReplace_ && newTable_)
			delete[] newTable_;
	}

	void restoreTable()
	{
		if (shouldReplace_)
		{
			DWORD old;
			VirtualProtect(classBase_, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
			*classBase_ = originalTable_;
			VirtualProtect(classBase_, sizeof(DWORD), old, &old);
		}
		else
		{
			for (auto& pair : hookedIndexes_)
				unhook(pair.first);
		}
	}

	template<class T>
	T hook(uint32_t index, T newFunction)
	{
		DWORD old = (DWORD)originalTable_[index];
		newTable_[index] = (DWORD)newFunction;
		hookedIndexes_.insert(std::make_pair(index, (DWORD)old));
		return (T)old;
	}

	void unhook(uint32_t index)
	{
		auto it = hookedIndexes_.find(index);
		if (it != hookedIndexes_.end())
		{
			newTable_[index] = (DWORD)it->second;
			hookedIndexes_.erase(it);
		}
	}

	template<class T>
	T getOriginal(uint32_t index)
	{
		return (T)originalTable_[index];
	}

private:
	uint32_t computeLength()
	{
		uint32_t index = 0;

		if (!originalTable_)
			return 0;

		for (index = 0; originalTable_[index]; index++)
		{
			if (IsBadCodePtr((FARPROC)originalTable_[index]))
				break;
		}

		return index;
	}

private:
	std::map<uint32_t, DWORD>	hookedIndexes_;
	PPDWORD						classBase_;
	PDWORD						originalTable_;
	PDWORD						newTable_;
	bool						shouldReplace_;
};

#endif