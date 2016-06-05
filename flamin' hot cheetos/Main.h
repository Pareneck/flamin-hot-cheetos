#ifndef MAIN_H
#define MAIN_H

#pragma once
#pragma warning(disable: 4244)
#pragma warning(disable: 4307)

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <string>
#include <memory>

#include "cx_strenc.h"

#include "Vector.h"
#include "SDK.h"
#include "SDKDefinitions.h"

#include "Color.h"
#include "Drawing.h"

#include "Interfaces.h"
#include "Hooks.h"

#include "Menu.h"
#include "Visuals.h"

#include "Control Variables.h"

extern bool bUnload;

#endif