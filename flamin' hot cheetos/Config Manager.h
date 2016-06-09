#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#pragma once

#include "stdafx.h"

class ConfigManager
{
public:
	void  initialize();

	void  getInteger(const char* section, const char* key, int& value);
	void  getFloat(const char* section, const char* key, float& value);
	void  getBoolean(const char* section, const char* key, bool& value);
	char* getString(const char* section, const char* key, char* value);

	void  setInteger(const char* section, const char* key, int value);
	void  setFloat(const char* section, const char* key, float value);
	void  setBoolean(const char* section, const char* key, bool value);
	void  setString(const char* section, const char* key, char* value);

private:
	char  directory[255];
};

extern ConfigManager configManager;

#endif