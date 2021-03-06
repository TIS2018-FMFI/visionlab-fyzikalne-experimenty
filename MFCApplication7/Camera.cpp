#include "stdafx.h"
#include "Camera.h"
#include "CameraConfig.h"
#include "MFCApplication7Dlg.h"

#include <thread>

using namespace cv;
using namespace chrono;

void task(Camera* cam) {
	int low_H = 284, low_S = 118, low_V = 53;
	int high_H = 355, high_S = 253, high_V = 255;
	int xy = 0, yy = 0, pocet = 0;
	while (true) {
		cam->vc >> cam->m;
		if (cam->nx != -1) {
			int y = (cam->ny * cam->m.rows) / cam->kky;
			int x = (cam->nx * cam->m.cols) / cam->kkx;
			Vec3b l = cam->m.at<Vec3b>(y, x);
			int ma = max(l[0], max(l[1], l[2]));
			int mi = min(l[0], min(l[1], l[2]));
			int del = ma - mi;
			int k[] = { 0, 0, ma };
			if (ma != 0) {
				k[1] = (255 * del) / ma;
			}
			if (del != 0) {
				if (ma == l[0]) {
					k[0] = 240 + (60 * (l[2] - l[1])) / del;
				}
				else if (ma == l[1]) {
					k[0] = 120 + (60 * (l[0] - l[2])) / del;
				}
				else {
					k[0] = (360 + (60 * (l[1] - l[0])) / del) % 360;
				}
			}
			low_S = k[1] - 40;
			high_S = k[1] + 40;
			low_V = k[2] - 40;
			high_V = k[2] + 40;
			low_H = k[0] - 70;
			high_H = k[0] + 70;
			if (low_H < 0) {
				low_H += 360;
			}
			if (high_H > 360) {
				high_H -= 360;
			}
			cam->nx = -1;
			cam->ny = -1;
		}

		for (int y = 0; y < cam->m.rows; y++) {
			for (int x = 0; x < cam->m.cols; x++) {
				Vec3b l = cam->m.at<Vec3b>(y, x);
				int ma = max(l[0], max(l[1], l[2]));
				int mi = min(l[0], min(l[1], l[2]));
				int del = ma - mi;
				int k[] = { 0, 0, ma };
				if (ma != 0) {
					k[1] = (255 * del) / ma;
				}
				if (del != 0) {
					if (ma == l[0]) {
						k[0] = 240 + (60 * (l[2] - l[1])) / del;
					}
					else if (ma == l[1]) {
						k[0] = 120 + (60 * (l[0] - l[2])) / del;
					}
					else {
						k[0] = (360 + (60 * (l[1] - l[0])) / del) % 360;
					}
				}
				if (((k[0] >= low_H && k[0] <= high_H && low_H < high_H) || (low_H > high_H && (k[0] >= low_H || k[0] <= high_H))) && k[1] >= low_S && k[1] <= high_S && k[2] >= low_V && k[2] <= high_V) {
					cam->m.at<Vec3b>(y, x)[1] = 255;
					xy += x;
					yy += y;
					pocet += 1;
				}
			}
		}
		if (pocet != 0) {
			for (int i = -2; i <= 2; i++) {
				for (int j = -2; j <= 2; j++) {
					if ((yy / pocet) + i < 0 || (yy / pocet) + i >= cam->m.rows || (xy / pocet) + j < 0 || (xy / pocet) + j >= cam->m.cols) continue;
					int hodnota = 255;
					if (i > -2 && j > -2 && i < 2 && j < 2) {
						hodnota = 0;
					}
					cam->m.at<Vec3b>((yy / pocet) + i, (xy / pocet) + j)[0] = hodnota;
					cam->m.at<Vec3b>((yy / pocet) + i, (xy / pocet) + j)[1] = hodnota;
					cam->m.at<Vec3b>((yy / pocet) + i, (xy / pocet) + j)[2] = hodnota;
				}
			}
		}
		if (pocet != 0) {
			cam->cx = xy / pocet;
			cam->cy = yy / pocet;
		/*	if (cam->cy > cam->by) {
				cam->by = cam->cy;
				cam->bx = cam->cx;
			}*/
		}
		else {
			cam->cx = 0;
			cam->cy = 0;
		}
		if (cam->started) {
			long long diff = duration_cast<milliseconds> (system_clock::now().time_since_epoch()).count();
			cam->ds->getValues(cam->cx, cam->cy, diff - cam->initTime);
		}
		yy = 0;
		xy = 0;
		pocet = 0;
		if (cam->ide == 1) {
			cam->win->Invalidate(FALSE);
		}
		char key = (char)cv::waitKey(20);
		if (key == 'q' || key == 27)
		{
			break;
		}
		
	}
}

Camera::Camera(cv::Mat& frame, CMFCApplication7Dlg* window, HWND hPE, CameraConfig config) {
	m = frame;
	win = window;
	h = hPE;
	vc = VideoCapture((int)config.configuration.at("CAM_NUMBER"));
	std::thread t1(task, this);
	t1.detach();
}

Camera::~Camera() {
	bx = -1;
	by = -1;
	cx = 0;
	cy = 0;
	nx = -1;
	ny = -1;
	kkx = -1;
	kky = -1;
	ide = 1;
	initTime = 0;
	started = false;
	ds = nullptr;
}

void Camera::Start(double l, double w, double g) {
	//double firstX, double firstY, double mX, double mY, double l, double w, long long time
	initTime = duration_cast<milliseconds> (system_clock::now().time_since_epoch()).count();
	ds = new DataSet(cx, cy, bx, by, l, w, 0, h, g);
	started = true;
}

void Camera::End() {
	started = false;
}

void Camera::SetBot() {
	by = cy;
	bx = cx;
}

void Camera::SetHSV(int x, int y, int kx, int ky) {
	nx = x;
	ny = y;
	kkx = kx;
	kky = ky;
}


void Camera::Save() {
	vc >> m2;
	resize(m2, m2, Size(), 0.55, 0.51);
	imwrite("zaznam.jpg", m2);
}

void Camera::StopStart() {
	ide *= -1;
}
