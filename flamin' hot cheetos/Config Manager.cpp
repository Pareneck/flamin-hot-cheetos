#include "Config Manager.h"

ConfigManager configManager;

void ConfigManager::initialize(const char* fileName)
{
	std::string folder = charenc("csgo\\cfg\\cheetos\\");
	CreateDirectory(folder.c_str(), 0);

	std::string file = folder + fileName;

	memset(directory, 0, 255);
	memcpy(directory, file.c_str(), strlen(file.c_str()));
}

void ConfigManager::getInteger(const char* section, const char* key, int& value)
{
	value = GetPrivateProfileInt(section, key, value, directory);
}

void ConfigManager::getFloat(const char* section, const char* key, float& value)
{
	char result[255];
	char buffer[255];

	sprintf(buffer, "%f", value);
	GetPrivateProfileStringA(section, key, buffer, result, 255, directory);
	value = (float)atof(result);
}

void ConfigManager::getBoolean(const char* section, const char* key, bool& value)
{
	char result[255];
	char buffer[255];

	sprintf(buffer, "%s", value ? "true" : "false");
	GetPrivateProfileString(section, key, buffer, result, 255, directory);
	value = (strcmp(result, "True") == 0 || strcmp(result, "true") == 0) ? true : false;
}

char* ConfigManager::getString(const char* section, const char* key, char* value)
{
	char* result = new char[255];

	memset(result, 0x00, 255);
	GetPrivateProfileString(section, key, value, result, 255, directory);
	return result;
}

void ConfigManager::setInteger(const char* section, const char* key, int value)
{
	char buffer[255];

	sprintf(buffer, "%d", value);
	WritePrivateProfileString(section, key, buffer, directory);
}

void ConfigManager::setFloat(const char* section, const char* key, float value)
{
	char buffer[255];

	sprintf(buffer, "%f", value);
	WritePrivateProfileString(section, key, buffer, directory);
}

void ConfigManager::setBoolean(const char* section, const char* key, bool value)
{
	char buffer[255];

	sprintf(buffer, "%s", value ? "true" : "false");
	WritePrivateProfileString(section, key, buffer, directory);
}

void ConfigManager::setString(const char* section, const char* key, char* value)
{
	WritePrivateProfileString(section, key, value, directory);
}