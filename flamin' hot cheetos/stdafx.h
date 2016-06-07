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

#include "cx_strenc.h"

#include "Menu.h"
#include "Visuals.h"
#include "Miscellaneous.h"

extern bool shouldUnload;

#endif