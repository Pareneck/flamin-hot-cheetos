#ifndef MAIN_H
#define MAIN_H

#pragma once
#pragma warning(disable: 4244)

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <string>
#include <memory>

#include "Vector.h"
#include "SDK.h"
#include "SDKDefinitions.h"

#include "Interfaces.h"
#include "Hooks.h"

#include "Color.h"
#include "Drawing.h"

#include "Visuals.h"

extern bool bUnload;

#endif