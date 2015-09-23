#include "stdafx.h"
#include "PhotoMerge.h"
#include "PhotoMergeDlg.h"
#include "afxdialogex.h"
#include "afxwin.h"

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
public:
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};


CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CAboutDlg::OnNMClickSyslink1)
END_MESSAGE_MAP()


void CAboutDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	ShellExecute(NULL, NULL, _T("http://nancom.tistory.com/"), NULL, NULL, SW_SHOWNORMAL);
}


// CPhotoMergeDlg ��ȭ ����
CPhotoMergeDlg::CPhotoMergeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PHOTOMERGE_DIALOG, pParent)
	, mergeSizeX(_T("640"))
	, mergeSizeY(_T("480"))
	, arrangemNumX(_T(""))
	, arrangemNumY(_T(""))
	, arrangemSpace(_T("15"))
	, saveFileName(_T("Output"))
	, windowTopMost(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CPhotoMergeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PHOTO_CNT, dropFilesNumCtrl);

	DDX_Control(pDX, IDC_SIZE_EDIT1, mergeSizeCtrlX);
	DDX_Text(pDX, IDC_SIZE_EDIT1, mergeSizeX);
	DDV_MaxChars(pDX, mergeSizeX, 5);
	DDX_Control(pDX, IDC_SIZE_EDIT2, mergeSizeCtrlY);
	DDX_Text(pDX, IDC_SIZE_EDIT2, mergeSizeY);
	DDV_MaxChars(pDX, mergeSizeY, 5);
	DDX_Control(pDX, IDC_SIZE_COMBO1, mergeSizeComboCtrl);

	DDX_Control(pDX, IDC_SIZE_EDIT3, arrangemNumCtrlX);
	DDX_Text(pDX, IDC_SIZE_EDIT3, arrangemNumX);
	DDV_MaxChars(pDX, arrangemNumX, 3);
	DDX_Control(pDX, IDC_SIZE_EDIT4, arrangemNumCtrlY);
	DDX_Text(pDX, IDC_SIZE_EDIT4, arrangemNumY);
	DDV_MaxChars(pDX, arrangemNumY, 3);

	DDX_Control(pDX, IDC_EDIT1, arrangemSpaceCtrl);
	DDX_Text(pDX, IDC_EDIT1, arrangemSpace);
	DDV_MaxChars(pDX, arrangemSpace, 4);

	DDX_Check(pDX, IDC_WINDOW_CHECK1, windowTopMost);
	DDX_Control(pDX, IDC_WINDOW_TRNS_SLIDE, transSliderCtrl);

	DDX_Control(pDX, IDC_SAVE_EDIT1, saveFileNameCtrl);
	DDX_Text(pDX, IDC_SAVE_EDIT1, saveFileName);
	DDV_MaxChars(pDX, saveFileName, 20);
	DDX_Control(pDX, IDC_SAVE_RADIO1, saveDefFolderRadioCtrl);
	DDX_Control(pDX, IDC_SAVE_RADIO2, saveDifFolderRadioCtrl);
	DDX_Control(pDX, IDC_SAVE_EDIT2, saveDifFolderCtrl);
	DDX_Control(pDX, IDC_CHECK2, saveFileOption1);
}

BEGIN_MESSAGE_MAP(CPhotoMergeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_WINDOW_CHECK1, &CPhotoMergeDlg::OnClickWindowTopMostCheck)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_WINDOW_TRNS_SLIDE, &CPhotoMergeDlg::OnNMCustomdrawTransSlider)
	ON_CBN_SELCHANGE(IDC_SIZE_COMBO1, &CPhotoMergeDlg::OnSelectMergeSizeCombo)
	ON_BN_CLICKED(IDC_SAVE_SET_BUTTON2, &CPhotoMergeDlg::OnSelectSaveDifFolder)
	ON_BN_CLICKED(IDC_SAVE_OPEN_BUTTON1, &CPhotoMergeDlg::OnOpenSaveDefFolder)
	ON_BN_CLICKED(IDC_SAVE_OPEN_BUTTON2, &CPhotoMergeDlg::OnOpenSaveDifFolder)
	ON_BN_CLICKED(IDOK, &CPhotoMergeDlg::OnMergePhotos)
	ON_EN_CHANGE(IDC_SAVE_EDIT1, &CPhotoMergeDlg::OnEnChangeSaveEdit1)
	ON_BN_CLICKED(IDABOUT, &CPhotoMergeDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_SAVE_CHECK1, &CPhotoMergeDlg::OnBnClickSaveFileOption1)
END_MESSAGE_MAP()


// CPhotoMergeDlg �޽��� ó����
BOOL CPhotoMergeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	mergeSizeComboCtrl.AddString(_T("����� ����"));
	mergeSizeComboCtrl.AddString(_T("640 x 480(4:3)"));
	mergeSizeComboCtrl.AddString(_T("800 x 600(4:3)"));
	mergeSizeComboCtrl.AddString(_T("1024 x 768(4:3)"));
	mergeSizeComboCtrl.AddString(_T("1280 x 960(4:3)"));
	mergeSizeComboCtrl.AddString(_T("1600 x 1200(4:3)"));
	mergeSizeComboCtrl.AddString(_T("1920 x 1440(4:3)"));
	mergeSizeComboCtrl.AddString(_T("2560 x 1920(4:3)"));
	mergeSizeComboCtrl.AddString(_T("3200 x 2400(4:3)"));
	mergeSizeComboCtrl.AddString(_T("4096 x 3072(4:3)"));
	mergeSizeComboCtrl.AddString(_T("6400 x 4800(4:3)"));
	mergeSizeComboCtrl.AddString(_T("640 x 360(16:9)"));
	mergeSizeComboCtrl.AddString(_T("1024 x 576(16:9)"));
	mergeSizeComboCtrl.AddString(_T("1280 x 720(16:9)"));
	mergeSizeComboCtrl.AddString(_T("1600 x 900(16:9)"));
	mergeSizeComboCtrl.AddString(_T("2048 x 1152(16:9)"));
	mergeSizeComboCtrl.AddString(_T("2560 x 1440(16:9)"));
	mergeSizeComboCtrl.AddString(_T("3200 x 1800(16:9)"));
	mergeSizeComboCtrl.AddString(_T("3840 x 2160(16:9)"));
	mergeSizeComboCtrl.AddString(_T("5120 x 2880(16:9)"));
	mergeSizeComboCtrl.AddString(_T("7680 x 4320(16:9)"));
	mergeSizeComboCtrl.AddString(_T("8192 x 4608(16:9)"));
	mergeSizeComboCtrl.SetCurSel(1);

	// �׻� �� üũ
	if (windowTopMost)
	{
		//AfxMessageBox(_T("Checked"));
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	// ���̾�α� ����ȭ�� ���� �ʱ� ����
	transExtendedStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, transExtendedStyle | WS_EX_LAYERED);

	// ���� �����̴� ����
	transSliderCtrl.SetRange(80, 255);	// ���� �����̴� ����
	transSliderCtrl.SetPos(255);
	transSliderCtrl.SetLineSize(2);
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, transSliderCtrl.GetPos(), LWA_ALPHA);

	// �������� Radio��ư ����
	saveDefFolderRadioCtrl.SetCheck(BST_CHECKED);
	saveDifFolderRadioCtrl.SetCheck(BST_UNCHECKED);

	// �ٸ����� ���� �ʱ� ��� ����
	TCHAR desktopPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, (LPWSTR)desktopPath, CSIDL_DESKTOP, FALSE);
	saveDifFolder = desktopPath;
	saveDifFolder += _T("\\");
	saveDifFolderCtrl.SetWindowTextW(saveDifFolder);
	//AfxMessageBox(saveDifFolder);

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


// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� �Ʒ� �ڵ尡 �ʿ��մϴ�.
// ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡�� �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.
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


// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ��� �� �Լ��� ȣ���մϴ�.
HCURSOR CPhotoMergeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPhotoMergeDlg::checkIntToCString(CString str, int w)
{
	CString temp;
	temp.Format(_T("%d"), w);
	AfxMessageBox(str + temp);
}

void CPhotoMergeDlg::checkIntToCString(CString str, int w, int x)
{
	CString temp;
	temp.Format(_T("%d, %d"), w, x);
	AfxMessageBox(str + temp);
}

void CPhotoMergeDlg::checkIntToCString(CString str, int w, int x, int y)
{
	CString temp;
	temp.Format(_T("%d, %d, %d"), w, x, y);
	AfxMessageBox(str + temp);
}

void CPhotoMergeDlg::checkIntToCString(CString str, int w, int x, int y, int z)
{
	CString temp;
	temp.Format(_T("%d, %d, %d, %d"), w, x, y, z);
	AfxMessageBox(str + temp);
}

void CPhotoMergeDlg::OnDropFiles(HDROP hDropInfo)
{
	CString strFilePath;
	DWORD nBuffer = 0;

	CString strFilesCnt;

	for (int i = 0; i < 1000; i++)
		dropFilesPath[i] = "";

	// �巡�� ��ӵ� ������ ����
	dropFilesNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (dropFilesNum < 1)
	{
		AfxMessageBox(_T("1�� �̻��� ������ �ʿ��մϴ�."));
		return;
	}

	for (int i = 0; i < dropFilesNum; i++)
	{
		nBuffer = DragQueryFile(hDropInfo, i, NULL, 0);

		// ������ ��� ����
		DragQueryFile(hDropInfo, i, strFilePath.GetBuffer(nBuffer + 1), nBuffer + 1);
		dropFilesPath[i] = strFilePath;
		strFilePath.ReleaseBuffer();
		//AfxMessageBox(dropFilesPath[i]);
	}
	DragFinish(hDropInfo);

	// �巡�� ��ӵ� ������ ���� Static Text Box�� ǥ��
	strFilesCnt.Format(_T("÷�ε� ����: %d"), dropFilesNum);
	dropFilesNumCtrl.SetWindowTextW(strFilesCnt);

	// ���� �迭 �� Edit Text Box�� ǥ��
	if ((dropFilesNum % 2) == 0)
	{
		// ���� ���� �迭 ������ 1/2�� ����
		CString numY;
		numY.Format(_T("%d"), dropFilesNum / 2);

		arrangemNumCtrlX.SetWindowTextW(_T("2"));
		arrangemNumCtrlY.SetWindowTextW(numY);
	}
	else
	{
		// ���� ���� �迭 ������ 1/2�� ����
		CString numY;
		numY.Format(_T("%d"), dropFilesNum / 2 + 1);
	
		if (dropFilesNum != 1)
			arrangemNumCtrlX.SetWindowTextW(_T("2"));
		else
			arrangemNumCtrlX.SetWindowTextW(_T("1"));

		arrangemNumCtrlY.SetWindowTextW(numY);
	}
	

	// �������� ����
	int i = dropFilesPath[0].ReverseFind('\\');			// ���� �̸��� ����� ���ؼ� ������ ������ '/'�� ã�´�.
	saveDefFolder = dropFilesPath[0].Left(i) + _T("\\");	// iĭ���� ��ΰ� Ȯ���ȴ�(�ڿ� �ִ� ���� �̸��� ������)
	//AfxMessageBox(saveDefFolder);

	//AfxMessageBox(strFilesCnt + _T("���� ������ �ҷ��Խ��ϴ�."));

	CDialogEx::OnDropFiles(hDropInfo);
}


// �׻� �� �Լ�
void CPhotoMergeDlg::OnClickWindowTopMostCheck()
{
	if (windowTopMost)
	{
		//AfxMessageBox(_T("UnChecked"));
		SetWindowPos(&wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		windowTopMost = false;
	}
	else if (windowTopMost == false)
	{
		//AfxMessageBox(_T("Checked"));
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
		windowTopMost = true;
	}
}


// ���� �����̴� ���� �Լ�
void CPhotoMergeDlg::OnNMCustomdrawTransSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, transSliderCtrl.GetPos(), LWA_ALPHA);

	*pResult = 0;
}


// ������ ���� �Լ�
void CPhotoMergeDlg::OnSelectMergeSizeCombo()
{
	switch (mergeSizeComboCtrl.GetCurSel())
	{
	case 1:
		mergeSizeCtrlX.SetWindowTextW(_T("640"));
		mergeSizeCtrlY.SetWindowTextW(_T("480"));
		break;
	case 2:
		mergeSizeCtrlX.SetWindowTextW(_T("800"));
		mergeSizeCtrlY.SetWindowTextW(_T("600"));
		break;
	case 3:
		mergeSizeCtrlX.SetWindowTextW(_T("1024"));
		mergeSizeCtrlY.SetWindowTextW(_T("768"));
		break;
	case 4:
		mergeSizeCtrlX.SetWindowTextW(_T("1280"));
		mergeSizeCtrlY.SetWindowTextW(_T("960"));
		break;
	case 5:
		mergeSizeCtrlX.SetWindowTextW(_T("1600"));
		mergeSizeCtrlY.SetWindowTextW(_T("1200"));
		break;
	case 6:
		mergeSizeCtrlX.SetWindowTextW(_T("1920"));
		mergeSizeCtrlY.SetWindowTextW(_T("1440"));
		break;
	case 7:
		mergeSizeCtrlX.SetWindowTextW(_T("2560"));
		mergeSizeCtrlY.SetWindowTextW(_T("1920"));
		break;
	case 8:
		mergeSizeCtrlX.SetWindowTextW(_T("3200"));
		mergeSizeCtrlY.SetWindowTextW(_T("2400"));
		break;
	case 9:
		mergeSizeCtrlX.SetWindowTextW(_T("4096"));
		mergeSizeCtrlY.SetWindowTextW(_T("3072"));
		break;
	case 10:
		mergeSizeCtrlX.SetWindowTextW(_T("6400"));
		mergeSizeCtrlY.SetWindowTextW(_T("4800"));
		break;
	case 11:
		mergeSizeCtrlX.SetWindowTextW(_T("640"));
		mergeSizeCtrlY.SetWindowTextW(_T("360"));
		break;
	case 12:
		mergeSizeCtrlX.SetWindowTextW(_T("1024"));
		mergeSizeCtrlY.SetWindowTextW(_T("480"));
		break;
	case 13:
		mergeSizeCtrlX.SetWindowTextW(_T("1280"));
		mergeSizeCtrlY.SetWindowTextW(_T("720"));
		break;
	case 14:
		mergeSizeCtrlX.SetWindowTextW(_T("1600"));
		mergeSizeCtrlY.SetWindowTextW(_T("900"));
		break;
	case 15:
		mergeSizeCtrlX.SetWindowTextW(_T("2048"));
		mergeSizeCtrlY.SetWindowTextW(_T("1152"));
		break;
	case 16:
		mergeSizeCtrlX.SetWindowTextW(_T("2560"));
		mergeSizeCtrlY.SetWindowTextW(_T("1440"));
		break;
	case 17:
		mergeSizeCtrlX.SetWindowTextW(_T("3200"));
		mergeSizeCtrlY.SetWindowTextW(_T("1800"));
		break;
	case 18:
		mergeSizeCtrlX.SetWindowTextW(_T("3840"));
		mergeSizeCtrlY.SetWindowTextW(_T("2160"));
		break;
	case 19:
		mergeSizeCtrlX.SetWindowTextW(_T("5120"));
		mergeSizeCtrlY.SetWindowTextW(_T("2880"));
		break;
	case 20:
		mergeSizeCtrlX.SetWindowTextW(_T("7680"));
		mergeSizeCtrlY.SetWindowTextW(_T("4320"));
		break;
	case 21:
		mergeSizeCtrlX.SetWindowTextW(_T("8192"));
		mergeSizeCtrlY.SetWindowTextW(_T("4608"));
		break;
	default:
		break;
	}
}


// �⺻ ���� ���� ���� 
void CPhotoMergeDlg::OnOpenSaveDefFolder()
{
	if (saveDefFolder != "")
	{
		ShellExecute(NULL, _T("open"), _T("explorer.exe"), saveDefFolder, NULL, SW_SHOW);
	}
	else
	{
		AfxMessageBox(_T("������ ÷�����ּ���."));
	}
}


// ������ ���� ���� ���� 
void CPhotoMergeDlg::OnOpenSaveDifFolder()
{
	ShellExecute(NULL, _T("open"), _T("explorer.exe"), saveDifFolder, NULL, SW_SHOW);
}


// ���� �̸� ����� �̸� ���� ���� �Լ�
void CPhotoMergeDlg::OnEnChangeSaveEdit1()
{
	saveFileNameCtrl.GetWindowTextW(saveFileName);
}


// ���� ���� �����ϴ� ������
void CPhotoMergeDlg::OnSelectSaveDifFolder()
{
	BROWSEINFO bi;
	TCHAR szBuffer[MAX_PATH];
	::ZeroMemory(&bi, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, MAX_PATH);

	bi.hwndOwner = m_hWnd;
	bi.lpszTitle = _T("������ ����� ������ �������ּ���.");
	bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST itemIdList = ::SHBrowseForFolder(&bi);
	if (::SHGetPathFromIDList(itemIdList, szBuffer))
	{
		// Radio��ư ����
		saveDefFolderRadioCtrl.SetCheck(BST_UNCHECKED);
		saveDifFolderRadioCtrl.SetCheck(BST_CHECKED);

		saveDifFolder = szBuffer;
		saveDifFolder += _T("\\");
		saveDifFolderCtrl.SetWindowTextW(saveDifFolder);
	}
}


// �ռ� ���� �Լ�
void CPhotoMergeDlg::OnMergePhotos()
{
	if (dropFilesNum < 1)
	{
		AfxMessageBox(_T("1�� �̻��� ������ �ʿ��մϴ�."));
		return;
	}

	if (saveDefFolderRadioCtrl.GetCheck())
	{
		saveFolder = saveDefFolder + saveFileName + _T(".jpg");
	}
	else
	{
		saveFolder = saveDifFolder + saveFileName + _T(".jpg");
	}

	CFileFind pFind;
	BOOL bRet = pFind.FindFile(saveFolder);
	if (bRet)
	{
		int nResult;
		nResult = AfxMessageBox(saveFolder + _T(" ������ �̹� ���� �մϴ�.\n���� ���ðڽ��ϱ�?"), MB_YESNO | MB_ICONWARNING);
		
		if (nResult == IDNO)
			return;
	}

	if (GdiplusStartup(&gdiplustToken, &gdiplusStartupInput, NULL) == Ok) {
		// Editbox���� ���� ��������
		CString tempMergeX, tempMergeY;
		mergeSizeCtrlX.GetWindowTextW(tempMergeX);
		mergeSizeCtrlY.GetWindowTextW(tempMergeY);
		int mergeX = _ttoi(tempMergeX);
		int mergeY = _ttoi(tempMergeY);

		CString tempArrangemNumX, tempArrangemNumY;
		arrangemNumCtrlX.GetWindowTextW(tempArrangemNumX);
		arrangemNumCtrlY.GetWindowTextW(tempArrangemNumY);
		int arrX = _ttoi(tempArrangemNumX);
		int arrY = _ttoi(tempArrangemNumY);

		CString tempArrangemSpace;
		arrangemSpaceCtrl.GetWindowTextW(tempArrangemSpace);
		int arrSpace = _ttoi(tempArrangemSpace);

		// ������ ������ �������� ũ��
		int eaPhotoSizeX = (mergeX - (arrX + 1) * arrSpace) / arrX;
		int eaPhotoSizeY = (mergeY - (arrY + 1) * arrSpace) / arrY;
		int posX = arrSpace;
		int posY = arrSpace;

		// �׸��� �۾��� ���� ��ü ����
		CDC *dc = GetDC();
		CDC memDC;
		memDC.CreateCompatibleDC(dc);

		CBitmap bmpbuffer;
		bmpbuffer.CreateCompatibleBitmap(dc, mergeX, mergeY); // ȣȯ�� ����
		CBitmap *oldBitmap = (CBitmap *)memDC.SelectObject(&bmpbuffer);

		CBrush brush;
		memDC.FillSolidRect(0, 0, mergeX, mergeY, RGB(255, 255, 255));

		Graphics graphics(memDC);
		CImage	image;
		CRect	rc;
		HRESULT hResult = NULL;

		// ArrangemNumY ����
		int num = 0;
		for (int i = 0; i < arrY; i++, posX = arrSpace, posY += (eaPhotoSizeY + arrSpace))
		{
			// ArrangemNumX ����
			for (int j = 0; (j < arrX) && (num < dropFilesNum); j++, posX += (eaPhotoSizeX + arrSpace))
			{
				hResult = image.Load(dropFilesPath[num++]);

				if (FAILED(hResult))
				{
					AfxMessageBox(_T("���������� �ν��� �� �����ϴ�.\n�ٽ� Ȯ�����ּ���."));
					return;
				}

				if ((num == dropFilesNum) && (dropFilesNum % 2 == 1))
				{
					// ���� ���� ���ϴ� ����
					int tmpWidth = posX + eaPhotoSizeX * (arrX - j) + arrSpace * (arrX - j - 1);

					rc.SetRect(posX, posY, tmpWidth, posY + eaPhotoSizeY);
					image.Draw(graphics.GetHDC(), rc, InterpolationModeDefault);
					image.Destroy();
					graphics.ReleaseHDC(memDC);

					continue;
				}

				//checkIntToCString(_T("i, arrX, j, arrY "), i, arrX, j, arrY);
				//checkIntToCString(_T("��ǥ "), posX, posY, eaPhotoSizeX, eaPhotoSizeY);
				rc.SetRect(posX, posY, posX + eaPhotoSizeX, posY + eaPhotoSizeY);
				image.Draw(graphics.GetHDC(), rc, InterpolationModeDefault);
				image.Destroy();
				graphics.ReleaseHDC(memDC);
			}
		}

		HPALETTE hpal;
		hpal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

		//Gdiplus::Bitmap�� �����!!!  
		Bitmap bitmap((HBITMAP)bmpbuffer, hpal);
		int width = bitmap.GetWidth();
		int height = bitmap.GetHeight();

		/* GDI plus�� �����ϱ� !! */
		CLSID				encoderClsid;
		EncoderParameters	encoderParameters;
		ULONG				quality;

		encoderParameters.Count = 1;
		encoderParameters.Parameter[0].Guid = EncoderQuality;
		encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;

		// �̹��� jpg ����� Quality level 100.
		quality = 100;
		encoderParameters.Parameter[0].Value = &quality;

		GetEncoderClsid(_T("image/jpeg"), &encoderClsid);
		bitmap.Save(saveFolder, &encoderClsid, &encoderParameters);

		ReleaseDC(&memDC);
	}
	else
	{
		AfxMessageBox(_T("GDI+ Ŭ������ �ʱ�ȭ ���� ���߽��ϴ�.\n�����ڿ��� �����ϼ���."));
		return;
	}

	GdiplusShutdown(gdiplustToken);

	if (saveFileOption1.GetCheck())
	{
		for (int i = 0; i < dropFilesNum; i++)
		{
			DeleteFile(dropFilesPath[i]);
			//AfxMessageBox(dropFilesPath[i]);
		}
	}

	AfxMessageBox(_T("�ռ��� ������ ����Ǿ����ϴ�.\n���: \"") + saveFolder + _T("\""));
}


// �̹��� ���忡 �ʿ��� �Լ�
int CPhotoMergeDlg::GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
{
	UINT num = 0;
	UINT size = 0;
	ImageCodecInfo * pImageCodecInfo = NULL;
	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;

	pImageCodecInfo = (ImageCodecInfo *)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;

	GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}
	free(pImageCodecInfo);
	return -1;
}


// About Box ���� �Լ�
void CPhotoMergeDlg::OnBnClickedAbout()
{
	static CAboutDlg Dlg;

	if (Dlg.GetSafeHwnd() == NULL)
		Dlg.Create(IDD_ABOUTBOX);

	Dlg.ShowWindow(SW_SHOW);
}


void CPhotoMergeDlg::OnBnClickSaveFileOption1()
{
	// TODO: Add your control notification handler code here
	if (saveFileOption1.GetCheck())
	{
		int nResult;
		nResult = AfxMessageBox(_T("�ռ��� ���� �������� ���ŵ˴ϴ�.\n�ش� ����� ����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONWARNING);

		if (nResult == IDNO)
			saveFileOption1.SetCheck(FALSE);
	}
}
