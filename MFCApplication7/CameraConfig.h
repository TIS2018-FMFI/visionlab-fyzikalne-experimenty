#pragma once

#include "Camera.h"

using namespace std;

#if !defined( _CAMERACONFIG_H_ )
#define _CAMERACONFIG_H_

class CameraConfig {

public:
	CameraConfig();
	map<string, double> configuration;
	void LoadDefaultConfig();
	int ExportConfigFile(bool default);
	void ImportConfigFile(const char* path);
};

#endif