#pragma once


#include "DataSet.h"
#include <thread>

class CMFCApplication7Dlg;

class CameraConfig;

class Camera {
public:
	int bx = -1, by = -1;
	int cx = 0, cy = 0;
	int nx = -1, ny = -1;
	int kkx = -1, kky = -1;
	int ide = 1;
	long long initTime = 0;
	bool started = false;
	DataSet* ds = nullptr;
	cv::Mat m, m2;
	CMFCApplication7Dlg* win;
	HWND h;
	cv::VideoCapture vc;
public:
	Camera(cv::Mat&, CMFCApplication7Dlg*, HWND, CameraConfig);
	~Camera();
	void Start(double l, double w, double g);
	void End();
	void SetBot();
	void SetHSV(int x, int y, int kx, int ky);
	void Save();
	void StopStart();
};
