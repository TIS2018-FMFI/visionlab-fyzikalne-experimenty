
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include "stdafx.h"
#include <string>

using namespace std;

#include "CameraConfig.h"


CameraConfig::CameraConfig() {

	ImportConfigFile("config\\config_default.txt");


}

void CameraConfig::LoadDefaultConfig() {
	configuration["CAM_NUMBER"] = 0;
	configuration["PEND_WEIGHT"] = 0.063;
	configuration["ROPE_LENGTH"] = 0.53;
	configuration["GRAVITY"] = 9.80665;
	ExportConfigFile(true);
}

int CameraConfig::ExportConfigFile(bool default) {
	string filePath;
	if (default == true) filePath = "config\\config_default.txt";
	else filePath = "config\\config_export.txt";
	ofstream configFile(filePath);
	if (configFile.is_open())
	{
		map<string, double>::iterator it = configuration.begin();
		for (pair<string, double> p : configuration) {
			std::ostringstream strs;
			strs << p.second;
			std::string str = strs.str();
			configFile << p.first + " " + str + "\n";
		}
		configFile.close();
		return 0;
	}
	return -1;
}

template<typename T>
std::vector<T> split(const std::string& line) {
	std::istringstream is(line);
	return std::vector<T>(std::istream_iterator<T>(is), std::istream_iterator<T>());
}

void CameraConfig::ImportConfigFile(const char* path) {
	string line;
	ifstream configFile(path);
	vector<string> tuple;
	string paramName, value;

	if (configFile.is_open())
	{
		while (getline(configFile, line))
		{
			tuple = split<string>(line);
			paramName = tuple[0];
			value = tuple[1];
			configuration[paramName] = stod(value);
		}

		configFile.close();

	}
	if (configuration.size() != 4)
	{
		LoadDefaultConfig();
	}
}