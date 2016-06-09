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
	VFTManager(PPDWORD classBase_, bool shouldReplace_)
	{
		classBase = classBase_;
		shouldReplace = shouldReplace_;

		if (shouldReplace)
		{
			originalTable = *classBase;
			uint32_t length = computeLength();

			newTable = new DWORD[length];
			memcpy(newTable, originalTable, length * sizeof(DWORD));

			DWORD old;
			VirtualProtect(classBase, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
			*classBase = newTable;
			VirtualProtect(classBase, sizeof(DWORD), old, &old);
		}
		else
		{
			originalTable = *classBase;
			newTable = *classBase;
		}
	}

	~VFTManager()
	{
		restoreTable();

		if (shouldReplace && newTable)
			delete[] newTable;
	}

	void restoreTable()
	{
		if (shouldReplace)
		{
			DWORD old;
			VirtualProtect(classBase, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &old);
			*classBase = originalTable;
			VirtualProtect(classBase, sizeof(DWORD), old, &old);
		}
		else
		{
			for (auto& pair : hookedIndexes)
				unhook(pair.first);
		}
	}

	template<class T>
	T hook(uint32_t index, T newFunction)
	{
		DWORD old = (DWORD)originalTable[index];
		newTable[index] = (DWORD)newFunction;
		hookedIndexes.insert(std::make_pair(index, (DWORD)old));
		return (T)old;
	}

	void unhook(uint32_t index)
	{
		auto it = hookedIndexes.find(index);
		if (it != hookedIndexes.end())
		{
			newTable[index] = (DWORD)it->second;
			hookedIndexes.erase(it);
		}
	}

	template<class T>
	T getOriginal(uint32_t index)
	{
		return (T)originalTable[index];
	}

private:
	uint32_t computeLength()
	{
		uint32_t index = 0;

		if (!originalTable)
			return 0;

		for (index = 0; originalTable[index]; index++)
		{
			if (IsBadCodePtr((FARPROC)originalTable[index]))
				break;
		}

		return index;
	}

private:
	std::map<uint32_t, DWORD>	hookedIndexes;
	PPDWORD						classBase;
	PDWORD						originalTable;
	PDWORD						newTable;
	bool						shouldReplace;
};

#endif