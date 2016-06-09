#ifndef CONFIGS_H
#define CONFIGS_H

#pragma once

#include "Config Manager.h"

class Config
{
public:
	Config(void);

	void load(void);
	void save(void);
};

extern Config config;

#endif