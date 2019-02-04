#pragma once


#include "DataSet.h"
#include <thread>

class CMFCApplication7Dlg;

class Camera {
public:
	int bx = -1, by = -1;
	int cx = 0, cy = 0;
	int nx = -1, ny = -1;
	int kkx = -1, kky = -1;
	long long initTime;
	bool started = false;
	DataSet* ds;
	cv::Mat m;
	CMFCApplication7Dlg* win;
	HWND h;
	cv::VideoCapture vc;
	map<string, double> configuration;
public:
	Camera(cv::Mat&, CMFCApplication7Dlg*, HWND);
	void Start(double l, double w);
	void End();
	void SetBot();
	void SetHSV(int x, int y, int kx, int ky);
	int ExportConfigFile(bool default);
	void LoadDefaultConfig();
	void ImportConfigFile(const char* path);
};