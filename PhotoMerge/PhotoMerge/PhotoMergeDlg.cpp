
// PhotoMergeDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PhotoMerge.h"
#include "PhotoMergeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CPhotoMergeDlg 대화 상자



CPhotoMergeDlg::CPhotoMergeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PHOTOMERGE_DIALOG, pParent)
	, mWinBtn(TRUE)
	, mSaveFileName(_T("Output"))
	, mSizeEditX(_T("640"))
	, mSizeEditY(_T("480"))
	, mSizeComboVal(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhotoMergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_WINDOW_CHECK1, mWinBtn);
	DDX_Text(pDX, IDC_SAVE_EDIT1, mSaveFileName);
	DDV_MaxChars(pDX, mSaveFileName, 20);
	DDX_Text(pDX, IDC_SIZE_EDIT1, mSizeEditX);
	DDV_MaxChars(pDX, mSizeEditX, 4);
	DDX_Text(pDX, IDC_SIZE_EDIT2, mSizeEditY);
	DDV_MaxChars(pDX, mSizeEditY, 4);
	DDX_Control(pDX, IDC_SIZE_COMBO1, mSizeComboCtrl);
	DDX_CBString(pDX, IDC_SIZE_COMBO1, mSizeComboVal);
	DDX_Control(pDX, IDC_WINDOW_TRNS_SLIDE, mWinTrnsSlideCtrl);
}

BEGIN_MESSAGE_MAP(CPhotoMergeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_WINDOW_CHECK1, &CPhotoMergeDlg::OnBnClickedWindowCheck1)
	ON_CBN_SELCHANGE(IDC_SIZE_COMBO1, &CPhotoMergeDlg::OnCbnSelchangeSizeCombo1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_WINDOW_TRNS_SLIDE, &CPhotoMergeDlg::OnNMCustomdrawWindowTrnsSlide)
END_MESSAGE_MAP()


// CPhotoMergeDlg 메시지 처리기

BOOL CPhotoMergeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 크기 조절에 콤보 박스 셋팅
	mSizeComboCtrl.AddString(_T("사용자 지정"));
	mSizeComboCtrl.AddString(_T("640 x 480(4:3)"));

	if (mWinBtn)
	{
		//AfxMessageBox(_T("Checked"));
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
	
	// 다이얼로그 투명화를 위한 초기 셋팅
	ExtendedStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, ExtendedStyle | WS_EX_LAYERED);
	
	// 투명도 슬라이더 셋팅
	mWinTrnsSlideCtrl.SetRange(80, 255);	// 투명도 슬라이더 범위
	mWinTrnsSlideCtrl.SetPos(255);
	mWinTrnsSlideCtrl.SetLineSize(2);
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, mWinTrnsSlideCtrl.GetPos(), LWA_ALPHA);
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPhotoMergeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
void CPhotoMergeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPhotoMergeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPhotoMergeDlg::OnDropFiles(HDROP hDropInfo)
{
	CString strFilePath;
	CString strFilesPath[64];
	DWORD nBuffer = 0;

	// 드롭된 파일의 갯수
	int nFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	
	for (int i = 0; i < nFiles; i++)
	{
		nBuffer = DragQueryFile(hDropInfo, i, NULL, 0);

		// 파일의 경로 얻어옴
		DragQueryFile(hDropInfo, i, strFilePath.GetBuffer(nBuffer + 1), nBuffer + 1);
		strFilesPath[i] = strFilePath;
		strFilePath.ReleaseBuffer();
		AfxMessageBox(strFilesPath[i]);
	}
	::DragFinish(hDropInfo);

	CDialogEx::OnDropFiles(hDropInfo);
}

void CPhotoMergeDlg::OnBnClickedWindowCheck1()
{
	if (mWinBtn)
	{
		//AfxMessageBox(_T("UnChecked"));
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		mWinBtn = false;
	}
	else if (mWinBtn == false)
	{
		//AfxMessageBox(_T("Checked"));
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		mWinBtn = true;
	}
}


void CPhotoMergeDlg::OnCbnSelchangeSizeCombo1()
{
	// TODO: Add your control notification handler code here

}



void CPhotoMergeDlg::OnNMCustomdrawWindowTrnsSlide(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, mWinTrnsSlideCtrl.GetPos(), LWA_ALPHA);

	*pResult = 0;
}
