#ifndef CONFIGS_H
#define CONFIGS_H

#pragma once

#include <fstream>

#include "Config Manager.h"
#include "Weapons.h"

inline bool doesFileExist(const std::string& filePath)
{
	std::ifstream file(filePath);
	return (bool)file;
}

class Config
{
public:
	struct SkinConfig
	{
		int skin = 0;
		int stattrak = 0;
		int seed = 0;
		float wear = 0.000001f;
		char* name = "";
	}; std::vector<SkinConfig> skincfg = std::vector<SkinConfig>(517);

public:
	Config(void);

	void loadConfig(void);
	void saveConfig(void);

	void loadSkinConfig(void);
	void saveSkinConfig(void);
};

extern Config config;

#endif