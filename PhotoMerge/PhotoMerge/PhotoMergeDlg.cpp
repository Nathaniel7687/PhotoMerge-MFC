
// PhotoMergeDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PhotoMerge.h"
#include "PhotoMergeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CPhotoMergeDlg ��ȭ ����
CPhotoMergeDlg::CPhotoMergeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PHOTOMERGE_DIALOG, pParent)
	, mWinBtn(TRUE)
	, mSaveFileName(_T("Output"))
	, mSizeEditX(_T("640"))
	, mSizeEditY(_T("480"))
	, mSizeEditNumX(_T(""))
	, mSizeEditNumY(_T(""))
	, mSizeComboVal(_T(""))
	, mSaveFolder(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhotoMergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_WINDOW_CHECK1, mWinBtn);
	DDX_Text(pDX, IDC_SAVE_EDIT1, mSaveFileName);
	DDV_MaxChars(pDX, mSaveFileName, 20);

	DDX_Control(pDX, IDC_SIZE_EDIT1, mSizeEditCtrlX);
	DDX_Text(pDX, IDC_SIZE_EDIT1, mSizeEditX);
	DDV_MaxChars(pDX, mSizeEditX, 4);
	DDX_Control(pDX, IDC_SIZE_EDIT2, mSizeEditCtrlY);
	DDX_Text(pDX, IDC_SIZE_EDIT2, mSizeEditY);
	DDV_MaxChars(pDX, mSizeEditY, 4);

	DDX_Control(pDX, IDC_SIZE_EDIT3, mSizeEditNumCtrlX);
	DDX_Text(pDX, IDC_SIZE_EDIT3, mSizeEditNumX);
	DDV_MaxChars(pDX, mSizeEditNumX, 2);
	DDX_Control(pDX, IDC_SIZE_EDIT4, mSizeEditNumCtrlY);
	DDX_Text(pDX, IDC_SIZE_EDIT4, mSizeEditNumY);
	DDV_MaxChars(pDX, mSizeEditNumY, 2);

	DDX_Control(pDX, IDC_SIZE_COMBO1, mSizeComboCtrl);
	DDX_CBString(pDX, IDC_SIZE_COMBO1, mSizeComboVal);
	DDX_Control(pDX, IDC_WINDOW_TRNS_SLIDE, mWinTrnsSlideCtrl);
	DDX_Radio(pDX, IDC_SAVE_RADIO1, mSaveFolder);
	DDX_Control(pDX, IDC_PHOTO_CNT, mPhotoCntStaticCtrl);
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


// CPhotoMergeDlg �޽��� ó����

BOOL CPhotoMergeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	// ũ�� ������ �޺� �ڽ� ����
	mSizeComboCtrl.AddString(_T("����� ����"));
	mSizeComboCtrl.AddString(_T("640 x 480(4:3)"));

	if (mWinBtn)
	{
		//AfxMessageBox(_T("Checked"));
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
	
	// ���̾�α� ����ȭ�� ���� �ʱ� ����
	ExtendedStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, ExtendedStyle | WS_EX_LAYERED);
	
	// ���� �����̴� ����
	mWinTrnsSlideCtrl.SetRange(80, 255);	// ���� �����̴� ����
	mWinTrnsSlideCtrl.SetPos(255);
	mWinTrnsSlideCtrl.SetLineSize(2);
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, mWinTrnsSlideCtrl.GetPos(), LWA_ALPHA);
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
void CPhotoMergeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CPhotoMergeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPhotoMergeDlg::OnDropFiles(HDROP hDropInfo)
{
	CString strFilePath;
	CString strFilesPath[64];
	DWORD nBuffer = 0;

	CString strFilesCnt;

	// �巡�� ��ӵ� ������ ����
	int nFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	// �巡�� ��ӵ� ������ ���� Static Text�� ǥ��
	strFilesCnt.Format(_T("%d"), nFiles);
	mPhotoCntStaticCtrl.SetWindowTextW(strFilesCnt);

	for (int i = 0; i < nFiles; i++)
	{
		nBuffer = DragQueryFile(hDropInfo, i, NULL, 0);

		// ������ ��� ����
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

// ������ ���� �Լ�
void CPhotoMergeDlg::OnCbnSelchangeSizeCombo1()
{
	// TODO: Add your control notification handler code here

}

// ���� �����̴� ���� �Լ�
void CPhotoMergeDlg::OnNMCustomdrawWindowTrnsSlide(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, mWinTrnsSlideCtrl.GetPos(), LWA_ALPHA);

	*pResult = 0;
}
