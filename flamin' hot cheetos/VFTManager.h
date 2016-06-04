#ifndef VFTMANAGER_H
#define VFTMANAGER_H

#pragma once

#include <Windows.h>
#include <stdio.h>
#include <map>
#include <stdint.h>

typedef DWORD** PPDWORD;

class CVFTManager
{
	CVFTManager(const CVFTManager&) = delete;

public:
	CVFTManager(PPDWORD ppClass, bool bReplace)
	{
		m_ppClassBase = ppClass;
		m_bReplace = bReplace;

		if (bReplace)
		{
			m_pOriginalVMTable = *ppClass;
			uint32_t dwLength = CalculateLength();

			m_pNewVMTable = new DWORD[dwLength];
			memcpy(m_pNewVMTable, m_pOriginalVMTable, dwLength * sizeof(DWORD));

			DWORD dwOld;
			VirtualProtect(m_ppClassBase, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwOld);
			*m_ppClassBase = m_pNewVMTable;
			VirtualProtect(m_ppClassBase, sizeof(DWORD), dwOld, &dwOld);
		}
		else
		{
			m_pOriginalVMTable = *ppClass;
			m_pNewVMTable = *ppClass;
		}
	}

	~CVFTManager()
	{
		RestoreTable();

		if (m_bReplace && m_pNewVMTable)
			delete[] m_pNewVMTable;
	}

	void RestoreTable()
	{
		if (m_bReplace)
		{
			DWORD dwOld;
			VirtualProtect(m_ppClassBase, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &dwOld);
			*m_ppClassBase = m_pOriginalVMTable;
			VirtualProtect(m_ppClassBase, sizeof(DWORD), dwOld, &dwOld);
		}
		else
		{
			for (auto& pair : m_vecHookedIndexes)
				Unhook(pair.first);
		}
	}

	template<class Type>
	Type Hook(uint32_t index, Type fnNew)
	{
		DWORD dwOld = (DWORD)m_pOriginalVMTable[index];
		m_pNewVMTable[index] = (DWORD)fnNew;
		m_vecHookedIndexes.insert(std::make_pair(index, (DWORD)dwOld));
		return (Type)dwOld;
	}

	void Unhook(uint32_t index)
	{
		auto it = m_vecHookedIndexes.find(index);
		if (it != m_vecHookedIndexes.end())
		{
			m_pNewVMTable[index] = (DWORD)it->second;
			m_vecHookedIndexes.erase(it);
		}
	}

	template<class Type>
	Type GetOriginal(uint32_t index)
	{
		return (Type)m_pOriginalVMTable[index];
	}

private:
	uint32_t CalculateLength()
	{
		uint32_t dwIndex = 0;

		if (!m_pOriginalVMTable)
			return 0;

		for (dwIndex = 0; m_pOriginalVMTable[dwIndex]; dwIndex++)
		{
			if (IsBadCodePtr((FARPROC)m_pOriginalVMTable[dwIndex]))
				break;
		}

		return dwIndex;
	}

private:
	std::map<uint32_t, DWORD>	m_vecHookedIndexes;
	PPDWORD						m_ppClassBase;
	PDWORD						m_pOriginalVMTable;
	PDWORD						m_pNewVMTable;
	bool						m_bReplace;
};

#endif