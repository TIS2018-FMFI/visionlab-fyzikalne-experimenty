// MFCApplication7Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCApplication7.h"
#include "MFCApplication7Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "Pegrpapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication7Dlg dialog

CMFCApplication7Dlg::CMFCApplication7Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION7_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//CStringA filename = CStringA(_T("test.jpg"));
	//m_imgMat = cv::imread(filename.GetBuffer(), cv::IMREAD_ANYCOLOR);

	cv::VideoCapture cap(0);
	cap >> m_imgMat;
}

void CMFCApplication7Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication7Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(CameraSettings_BUTTON, &CMFCApplication7Dlg::OnBnClickedButton)
	ON_BN_CLICKED(IDC_RADIO3, &CMFCApplication7Dlg::OnBnClickedRadio3)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCApplication7Dlg::OnEnChangeEdit4)
	ON_BN_CLICKED(IDOK, &CMFCApplication7Dlg::OnBnClickedOk)
	ON_BN_CLICKED(GraphSettings_BUTTON, &CMFCApplication7Dlg::OnBnClickedGraphSet)
	ON_BN_CLICKED(Save_BUTTON, &CMFCApplication7Dlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication7Dlg::OnBnClickedHotovo1)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication7Dlg::OnBnClickedHotovo2)
	ON_BN_CLICKED(IDC_BUTTON7, &CMFCApplication7Dlg::OnBnClickedCSV)
	ON_BN_CLICKED(IDC_BUTTON8, &CMFCApplication7Dlg::OnBnClickedPDF)
	ON_BN_CLICKED(PlayStop_BUTTON, &CMFCApplication7Dlg::OnPlayStopClickedButton)
	ON_BN_CLICKED(Min_BUTTON, &CMFCApplication7Dlg::OnMinClickedButton)
	ON_STN_CLICKED(IDC_STATIC37, &CMFCApplication7Dlg::CameraClick)
END_MESSAGE_MAP()


// CMFCApplication7Dlg message handlers

BOOL CMFCApplication7Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	CString cs = CString("1");

	SetDlgItemText(IDC_EDIT3, cs);
	SetDlgItemText(IDC_EDIT4, cs);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_drawingApproach = DA_STRETCHDIBITS;

	m_stretchBltMode = COLORONCOLOR;

	CWnd* pWndRect = NULL;
	pWndRect = GetDlgItem(IDC_STATIC37);
	if (pWndRect)
	{
		pWndRect->GetClientRect(&m_imgRect);
		pWndRect->MapWindowPoints(this, &m_imgRect);
	}

	hPE = NULL;

	

	

	CWnd* graphWin = NULL;
	graphWin = GetDlgItem(IDC_STATIC222);
	//    graphWin->GetClientRect(&m_imgRect);
	//    graphWin->MapWindowPoints(this, &m_imgRect);
	RECT r;
	int dwColor;
	float f[] = { 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
					0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
					0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
					0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
					0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,

					0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
					0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
					0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
					0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,
					0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, };

	GetClientRect(&r);
	hPE = PEcreate(PECONTROL_GRAPH, 0, &r, graphWin->m_hWnd, 1000);
	PEszset(hPE, PEP_szMAINTITLE, TEXT(""));
	PEszset(hPE, PEP_szSUBTITLE, TEXT(" "));
	PEnset(hPE, PEP_nSUBSETS, 10);
	PEnset(hPE, PEP_nPOINTS, 60);

	PEvset(hPE, PEP_faYDATA, f, 600);

	for (int i = 0; i < 60; i++) {
		PEvsetcell(hPE, PEP_szaPOINTLABELS, i, TEXT(""));
	}


	//fyz.veliciny, ktore sa zobrazuju
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 0, TEXT("Uhlová výchylka"));
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 1, TEXT("Uhlové zrýchlenie"));
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 2, TEXT("Uhlová rýchlosť"));
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 3, TEXT("Kinetická Enegria"));
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 4, TEXT("Potenciálna Energia"));
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 5, TEXT("Rýchlosť"));
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 6, TEXT("Zrýchlenie"));
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 7, TEXT("Maximálna výchylka"));
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 8, TEXT("Perióda"));
	PEvsetcell(hPE, PEP_szaSUBSETLABELS, 9, TEXT("Frekvencia"));


	PEszset(hPE, PEP_szYAXISLABEL, TEXT("Hodnota"));
	PEszset(hPE, PEP_szXAXISLABEL, TEXT("Uplynulý čas"));

	dwColor = PERGB(60, 0, 180, 0); PEvsetcell(hPE, PEP_dwaSUBSETCOLORS, 0, &dwColor);
	dwColor = PERGB(180, 0, 0, 130); PEvsetcell(hPE, PEP_dwaSUBSETCOLORS, 1, &dwColor);

	PEnset(hPE, PEP_nGRAPHPLUSTABLE, PEGPT_BOTH);
	PEnset(hPE, PEP_nDATAPRECISION, 0);
	PEnset(hPE, PEP_bLABELBOLD, TRUE);

	PEnset(hPE, PEP_nCOMPARISONSUBSETS, 3);
	PEnset(hPE, PEP_nPLOTTINGMETHOD, PEGPM_LINE);
	PEnset(hPE, PEP_nPLOTTINGMETHODII, PEGPM_POINT);

	PEnset(hPE, PEP_nGRAPHPLUSTABLE, 0);
	PEnset(hPE, PEP_nGRADIENTBARS, 8);
	PEnset(hPE, PEP_bBARGLASSEFFECT, TRUE);
	PEnset(hPE, PEP_nLEGENDLOCATION, PELL_BOTTOM);
	PEnset(hPE, PEP_nDATASHADOWS, PEDS_3D);
	PEnset(hPE, PEP_nFONTSIZE, PEFS_LARGE);
	PEnset(hPE, PEP_bPREPAREIMAGES, TRUE);
	PEnset(hPE, PEP_bCACHEBMP, TRUE);
	PEnset(hPE, PEP_nRENDERENGINE, PERE_DIRECT2D);
	PEnset(hPE, PEP_bANTIALIASGRAPHICS, TRUE);
	PEnset(hPE, PEP_bANTIALIASTEXT, TRUE);
	PEnset(hPE, PEP_bALLOWDATAHOTSPOTS, TRUE);
	PEnset(hPE, PEP_bBITMAPGRADIENTMODE, FALSE);
	PEnset(hPE, PEP_nQUICKSTYLE, PEQS_LIGHT_SHADOW);
	PEnset(hPE, PEP_bFIXEDFONTS, TRUE);

	cam = new Camera(m_imgMat, this, hPE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication7Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication7Dlg::OnPaint()
{
	if (IsIconic())
	{
		PEreinitialize(hPE);
		PEresetimage(hPE, 600, 500);
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		PEreinitialize(hPE);
		PEresetimage(hPE, 600, 500);
		//Invalidate(FALSE);
		CPaintDC dc(this);
		dc.SetStretchBltMode(m_stretchBltMode);
		m_drawer1.StretchImage(&dc, m_imgRect, m_imgMat);
		CDialogEx::OnPaint();
		//CWnd* pWndRect = NULL;
		//pWndRect = GetDlgItem(IDC_STATIC37);
		//pWndRect->InvalidateRect(FALSE);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication7Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

boolean cameraOpen = false;

void CMFCApplication7Dlg::OnBnClickedButton()
{
	if (cameraOpen) {
		this->GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO3)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO4)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_RADIO5)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_SET1)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);

		cameraOpen = false;
	}
	else {
		this->GetDlgItem(IDC_RADIO1)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_RADIO2)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_RADIO3)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_RADIO4)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_RADIO5)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_EDIT1)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_SET1)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_STATIC1)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);

		cameraOpen = true;
	}
	
}

boolean graphOpen = false;
void CMFCApplication7Dlg::OnBnClickedGraphSet()
{
	if (graphOpen) {
		this->GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_SET2)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);

		graphOpen = false;
	}
	else {
		this->GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_EDIT5)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_SET2)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_STATIC6)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_STATIC7)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_STATIC8)->ShowWindow(SW_SHOW);

		graphOpen = true;
	}
}


boolean saveOpen = false;
void CMFCApplication7Dlg::OnBnClickedSave()
{
	if (saveOpen) {
		this->GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);

		this->GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		this->GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);

		saveOpen = false;
	}
	else {
		this->GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_SHOW);

		this->GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		this->GetDlgItem(IDC_STATIC5)->ShowWindow(SW_SHOW);

		saveOpen = true;
	}
}

void CMFCApplication7Dlg::OnBnClickedRadio3()
{
	// TODO: Add your control notification handler code here
}


void CMFCApplication7Dlg::OnEnChangeEdit4()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CMFCApplication7Dlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}




void CMFCApplication7Dlg::OnBnClickedHotovo1()
{
	this->GetDlgItem(IDC_RADIO1)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_RADIO2)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_RADIO3)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_RADIO4)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_RADIO5)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_EDIT1)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_BUTTON5)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_SET1)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_STATIC1)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);

	cameraOpen = false;
}


void CMFCApplication7Dlg::OnBnClickedHotovo2()
{
	this->GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_BUTTON6)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_SET2)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);

	graphOpen = false;
}


void CMFCApplication7Dlg::OnBnClickedCSV()
{
	this->GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);

	saveOpen = false;

	cam->ds->exportRawData();
}


void CMFCApplication7Dlg::OnBnClickedPDF()
{
	this->GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_BUTTON7)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_BUTTON8)->ShowWindow(SW_HIDE);

	this->GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
	this->GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);

	saveOpen = false;

	POINT p;
	p.x = 600;
	p.y = 500;

	LPWSTR strFull = L"image.png";
	string graphName = "image.png";
	PEcopyjpegtofile(hPE, &p, strFull);

	//Erikov kód
	cam->ds->exportGraphData()
}


void CMFCApplication7Dlg::OnPlayStopClickedButton()
{
	if (!nahrava) {
		nahrava = true;
		CString cs1;
		GetDlgItemText(IDC_EDIT3, cs1);
		float hmot = _ttof(cs1);
		CString cs2;
		GetDlgItemText(IDC_EDIT4, cs2);
		float dlzk = _ttof(cs2);
		cam->Start(dlzk, hmot); //TODO: Nastavit tieto hodnoty na dlzku lana a vahu zavazia v metroch a kilogramoch
	}
	else {
		nahrava = false;
		cam->End();
	}
}


void CMFCApplication7Dlg::OnMinClickedButton()
{
	cam->SetBot();
}


void CMFCApplication7Dlg::CameraClick()
{
	if (!nahrava) {
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(&pt);
		cam->SetHSV(pt.x - 26, pt.y - 151, 630-26, 573-151); //x=630, y=573
	}
}
