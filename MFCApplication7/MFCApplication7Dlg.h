
// MFCApplication7Dlg.h : header file
//

#pragma once
#include "DrawApproachStretchDIBits.h"
#include "Camera.h"

enum EDrawingApproach
{
	DA_STRETCHDIBITS = 0
	// 	DA_SETDIBITS,
	// 	DA_CVVIMAGE,
	// 	DA_HBITMAP
};

// CMFCApplication7Dlg dialog
class CMFCApplication7Dlg : public CDialogEx
{
// Construction
public:
	CMFCApplication7Dlg(CWnd* pParent = nullptr);	// standard constructor
	HWND hPE;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION7_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CDrawApproachStretchDIBits m_drawer1;
	EDrawingApproach m_drawingApproach;
	int m_stretchBltMode;
	bool nahrava = false;
private:
	cv::Mat m_imgMat;
	Camera* cam;
public:
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedGraphSet();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedHotovo1();
	afx_msg void OnBnClickedHotovo2();
	afx_msg void OnBnClickedCSV();
	afx_msg void OnBnClickedPDF();
	CRect m_imgRect;
	afx_msg void OnPlayStopClickedButton();
	afx_msg void OnMinClickedButton();
	afx_msg void CameraClick();
	afx_msg void OnBnClickedCheck1();
};
