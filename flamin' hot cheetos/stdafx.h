#ifndef STDAFX_H
#define STDAFX_H

#pragma once
#pragma warning(disable: 4244)
#pragma warning(disable: 4307)

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include "cx_strenc.h"

#include "SDK.h"
#include "SDKDefinitions.h"

#include "Color.h"
#include "Drawing.h"

#include "Interfaces.h"
#include "Hooks.h"

#include "Control Variables.h"

#include "Menu.h"
#include "Visuals.h"
#include "Miscellaneous.h"
#include "Aimbot.h"

extern bool shouldUnload;

#endif