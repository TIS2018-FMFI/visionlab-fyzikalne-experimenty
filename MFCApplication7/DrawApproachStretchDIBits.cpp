#include "StdAfx.h"
#include "DrawApproachStretchDIBits.h"

CDrawApproachStretchDIBits::CDrawApproachStretchDIBits(void)
{
	m_bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256);
	::ZeroMemory(&m_bmi->bmiHeader, sizeof(BITMAPINFOHEADER));
}

CDrawApproachStretchDIBits::~CDrawApproachStretchDIBits(void)
{
	if (m_bmi)
	{
		delete m_bmi;
		m_bmi = NULL;
	}
}

void CDrawApproachStretchDIBits::StretchImage(CDC* dc, const CRect& rect, cv::Mat& image)
{
	StretchImage(dc, rect, &IplImage(image));
}

void CDrawApproachStretchDIBits::StretchImage( CDC* dc, const CRect& rect, IplImage* pImage )
{
	m_bmi->bmiHeader.biBitCount = (WORD)(pImage->depth * pImage->nChannels);
	m_bmi->bmiHeader.biCompression = BI_RGB;
	m_bmi->bmiHeader.biPlanes = 1;
	m_bmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_bmi->bmiHeader.biWidth = pImage->width;
	m_bmi->bmiHeader.biHeight = -pImage->height;

	if (pImage->nChannels == 1)
	{
		for( int i = 0; i < 256; i++ )
		{
			m_bmi->bmiColors[i].rgbBlue = m_bmi->bmiColors[i].rgbGreen = m_bmi->bmiColors[i].rgbRed = (BYTE)i;
			m_bmi->bmiColors[i].rgbReserved = 0;
		}
	}

	::StretchDIBits(dc->GetSafeHdc(),
		rect.left, rect.top, rect.Width(), rect.Height(),
		0, 0, pImage->width, pImage->height,
		pImage->imageData, m_bmi, DIB_RGB_COLORS, SRCCOPY);
}

CRect CDrawApproachStretchDIBits::ComputeRatioSaveImageBox( IplImage* pImage, const CRect& bRect )
{
	CRect rect(0, 0, 0, 0);

	if (pImage == NULL) return rect;

	int iWidth = pImage->width;
	int iHeight = pImage->height;
	int rWidth = bRect.Width();
	int rHeight = bRect.Height();
	int dWidth = 0;
	int dHeight = 0;

	if ( iWidth == 0 || iHeight == 0 || rWidth == 0 || rHeight == 0 ) return rect;

	double iRatio = (double)iWidth / (double)iHeight;
	double rRatio = (double)rWidth / (double)rHeight;

	if (iRatio > rRatio)
	{
		// image is wider
		dWidth = rWidth;
		dHeight = (int)(dWidth / iRatio);

		int top = (bRect.top + bRect.bottom - dHeight) / 2;
		rect.SetRect(bRect.left, top, bRect.right, top + dHeight);
	} else {
		// rectangle is wider
		dHeight = rHeight;
		dWidth = (int)(dHeight * iRatio);

		int left = (bRect.left + bRect.right - dWidth) / 2;
		rect.SetRect(left, bRect.top, left + dWidth, bRect.bottom);
	}

	return rect;
}