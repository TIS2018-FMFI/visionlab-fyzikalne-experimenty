#pragma once

class CDrawApproachStretchDIBits
{
public:
	CDrawApproachStretchDIBits(void);
	~CDrawApproachStretchDIBits(void);

	BITMAPINFO* m_bmi;

	void StretchImage(CDC* dc, const CRect& rect, IplImage* pImage);
	void StretchImage(CDC* dc, const CRect& rect, cv::Mat& image);

	static CRect ComputeRatioSaveImageBox(IplImage* pImage, const CRect& bRect);
};
