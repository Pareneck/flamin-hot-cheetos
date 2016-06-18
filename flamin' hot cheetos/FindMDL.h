#ifndef FINDMDL_H
#define FINDMDL_H

#pragma once

#include "stdafx.h"

MDLHandle_t __stdcall FindMDL(const char* pMDLRelativePath);

typedef MDLHandle_t(__thiscall* FindMDL_t)(IMDLCache*, const char*);
extern FindMDL_t originalFindMDL;

#endif