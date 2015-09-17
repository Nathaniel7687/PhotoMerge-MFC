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
}

BEGIN_MESSAGE_MAP(CPhotoMergeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	ON_CBN_SELCHANGE(IDC_SIZE_COMBO1, &CPhotoMergeDlg::OnSelectMergeSizeCombo)
	ON_BN_CLICKED(IDC_WINDOW_CHECK1, &CPhotoMergeDlg::OnClickWindowTopMostCheck)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_WINDOW_TRNS_SLIDE, &CPhotoMergeDlg::OnNMCustomdrawTransSlider)
	ON_BN_CLICKED(IDC_SAVE_SET_BUTTON2, &CPhotoMergeDlg::OnSelectSaveDifFolder)
	ON_BN_CLICKED(IDC_SAVE_OPEN_BUTTON1, &CPhotoMergeDlg::OnOpenSaveDefFolder)
	ON_BN_CLICKED(IDC_SAVE_OPEN_BUTTON2, &CPhotoMergeDlg::OnOpenSaveDifFolder)
	ON_BN_CLICKED(IDOK, &CPhotoMergeDlg::OnMergePhotos)
	ON_EN_CHANGE(IDC_SAVE_EDIT1, &CPhotoMergeDlg::OnEnChangeSaveEdit1)
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
	mergeSizeComboCtrl.AddString(_T("사용자 지정"));
	mergeSizeComboCtrl.AddString(_T("640 x 480(4:3)"));
	mergeSizeComboCtrl.SetCurSel(1);

	// 항상 위 체크
	if (windowTopMost)
	{
		//AfxMessageBox(_T("Checked"));
		SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	// 다이얼로그 투명화를 위한 초기 셋팅
	transExtendedStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, transExtendedStyle | WS_EX_LAYERED);

	// 투명도 슬라이더 셋팅
	transSliderCtrl.SetRange(80, 255);	// 투명도 슬라이더 범위
	transSliderCtrl.SetPos(255);
	transSliderCtrl.SetLineSize(2);
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, transSliderCtrl.GetPos(), LWA_ALPHA);

	// 저장폴더 Radio버튼 설정
	saveDefFolderRadioCtrl.SetCheck(BST_CHECKED);
	saveDifFolderRadioCtrl.SetCheck(BST_UNCHECKED);

	// 다른폴더 저장 초기 경로 셋팅
	TCHAR desktopPath[MAX_PATH];
	SHGetSpecialFolderPath(NULL, (LPWSTR)desktopPath, CSIDL_DESKTOP, FALSE);
	saveDifFolder = desktopPath;
	saveDifFolder += _T("\\");
	saveDifFolderCtrl.SetWindowTextW(saveDifFolder);
	//AfxMessageBox(saveDifFolder);

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


// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면 아래 코드가 필요합니다.
// 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는 프레임워크에서 이 작업을 자동으로 수행합니다.
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


// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서 이 함수를 호출합니다.
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

	// 드래그 드롭된 파일의 갯수
	dropFilesNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (dropFilesNum < 2)
	{
		AfxMessageBox(_T("2개 이상의 사진이 필요합니다."));
		return;
	}

	for (int i = 0; i < dropFilesNum; i++)
	{
		nBuffer = DragQueryFile(hDropInfo, i, NULL, 0);

		// 파일의 경로 얻어옴
		DragQueryFile(hDropInfo, i, strFilePath.GetBuffer(nBuffer + 1), nBuffer + 1);
		dropFilesPath[i] = strFilePath;
		strFilePath.ReleaseBuffer();
		//AfxMessageBox(dropFilesPath[i]);
	}
	DragFinish(hDropInfo);

	// 드래그 드롭된 파일의 갯수 Static Text Box에 표시
	strFilesCnt.Format(_T("%d"), dropFilesNum);
	dropFilesNumCtrl.SetWindowTextW(strFilesCnt);

	// 사진 배열 값 Edit Text Box에 표시
	if ((dropFilesNum % 2) == 0)
	{
		// 세로 사진 배열 갯수를 1/2로 맞춤
		CString numY;
		numY.Format(_T("%d"), dropFilesNum / 2);

		arrangemNumCtrlX.SetWindowTextW(_T("2"));
		arrangemNumCtrlY.SetWindowTextW(numY);
	}
	else
	{
		// 세로 사진 배열 갯수를 1/2로 맞춤
		CString numY;
		numY.Format(_T("%d"), dropFilesNum / 2 + 1);

		arrangemNumCtrlX.SetWindowTextW(_T("2"));
		arrangemNumCtrlY.SetWindowTextW(numY);
	}

	// 저장폴더 셋팅
	int i = dropFilesPath[0].ReverseFind('\\');			// 파일 이름을 지우기 위해서 오른쪽 마지막 '/'를 찾는다.
	saveDefFolder = dropFilesPath[0].Left(i) + _T("\\");	// i칸까지 경로가 확보된다(뒤에 있는 파일 이름이 지워짐)
	//AfxMessageBox(saveDefFolder);

	AfxMessageBox(strFilesCnt + _T("개의 사진을 불러왔습니다."));

	CDialogEx::OnDropFiles(hDropInfo);
}


// 사이즈 선택 함수
void CPhotoMergeDlg::OnSelectMergeSizeCombo()
{
	if (mergeSizeComboCtrl.GetCurSel() == 1)
	{
		mergeSizeCtrlX.SetWindowTextW(_T("640"));
		mergeSizeCtrlY.SetWindowTextW(_T("480"));
	}
}


// 항상 위 함수
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


// 투명도 슬라이더 조절 함수
void CPhotoMergeDlg::OnNMCustomdrawTransSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	::SetLayeredWindowAttributes(GetSafeHwnd(), 0, transSliderCtrl.GetPos(), LWA_ALPHA);

	*pResult = 0;
}


void CPhotoMergeDlg::OnOpenSaveDefFolder()
{
	if (saveDefFolder != "")
	{
		ShellExecute(NULL, _T("open"), _T("explorer.exe"), saveDefFolder, NULL, SW_SHOW);
	}
	else
	{
		AfxMessageBox(_T("사진을 첨부해주세요."));
	}
}


void CPhotoMergeDlg::OnOpenSaveDifFolder()
{
	ShellExecute(NULL, _T("open"), _T("explorer.exe"), saveDifFolder, NULL, SW_SHOW);
}


void CPhotoMergeDlg::OnEnChangeSaveEdit1()
{
	saveFileNameCtrl.GetWindowTextW(saveFileName);
}


void CPhotoMergeDlg::OnSelectSaveDifFolder()
{
	BROWSEINFO bi;
	TCHAR szBuffer[MAX_PATH];
	::ZeroMemory(&bi, sizeof(BROWSEINFO));
	::ZeroMemory(szBuffer, MAX_PATH);

	bi.hwndOwner = m_hWnd;
	bi.lpszTitle = _T("파일이 저장될 폴더를 선택해주세요.");
	bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST itemIdList = ::SHBrowseForFolder(&bi);
	if (::SHGetPathFromIDList(itemIdList, szBuffer))
	{
		// Radio버튼 설정
		saveDefFolderRadioCtrl.SetCheck(BST_UNCHECKED);
		saveDifFolderRadioCtrl.SetCheck(BST_CHECKED);

		saveDifFolder = szBuffer;
		saveDifFolder += _T("\\");
		saveDifFolderCtrl.SetWindowTextW(saveDifFolder);
	}
}


void CPhotoMergeDlg::OnMergePhotos()
{
	if (dropFilesNum < 2)
	{
		AfxMessageBox(_T("2개 이상의 사진이 필요합니다."));
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
		nResult = AfxMessageBox(saveFolder + _T(" 파일이 이미 존재 합니다.\n덮어 쓰시겠습니까?"), MB_YESNO | MB_ICONWARNING);
		
		if (nResult == IDNO)
			return;
	}

	if (GdiplusStartup(&gdiplustToken, &gdiplusStartupInput, NULL) == Ok) {
		// Editbox에서 정보 가져오기
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

		// 각각의 사진이 가져야할 크기
		int eaPhotoSizeX = (mergeX - (arrX + 1) * arrSpace) / arrX;
		int eaPhotoSizeY = (mergeY - (arrY + 1) * arrSpace) / arrY;
		int posX = arrSpace;
		int posY = arrSpace;

		// 그리기 작업을 위한 객체 선언
		CDC *dc = GetDC();
		CDC memDC;
		memDC.CreateCompatibleDC(dc);

		CBitmap bmpbuffer;
		bmpbuffer.CreateCompatibleBitmap(dc, mergeX, mergeY); // 호환성 조절
		CBitmap *oldBitmap = (CBitmap *)memDC.SelectObject(&bmpbuffer);

		CBrush brush;
		memDC.FillSolidRect(0, 0, mergeX, mergeY, RGB(255, 255, 255));

		Graphics graphics(memDC);
		CImage	image;
		CRect	rc;
		HRESULT hResult = NULL;

		// ArrangemNumY 개수
		int num = 0;
		for (int i = 0; i < arrY; i++, posX = arrSpace, posY += (eaPhotoSizeY + arrSpace))
		{
			// ArrangemNumX 개수
			for (int j = 0; (j < arrX) && (num < dropFilesNum); j++, posX += (eaPhotoSizeX + arrSpace))
			{
				hResult = image.Load(dropFilesPath[num++]);

				if (FAILED(hResult))
				{
					AfxMessageBox(_T("사진파일을 인식할 수 없습니다.\n다시 확인해주세요."));
					return;
				}

				if ((num == dropFilesNum) && (dropFilesNum % 2 == 1))
				{
					// 남은 여백 구하는 공식
					int tmpWidth = posX + eaPhotoSizeX * (arrX - j) + arrSpace * (arrX - j - 1);

					rc.SetRect(posX, posY, tmpWidth, posY + eaPhotoSizeY);
					image.Draw(graphics.GetHDC(), rc, InterpolationModeDefault);
					image.Destroy();
					graphics.ReleaseHDC(memDC);

					continue;
				}

				//checkIntToCString(_T("i, arrX, j, arrY "), i, arrX, j, arrY);
				//checkIntToCString(_T("좌표 "), posX, posY, eaPhotoSizeX, eaPhotoSizeY);
				rc.SetRect(posX, posY, posX + eaPhotoSizeX, posY + eaPhotoSizeY);
				image.Draw(graphics.GetHDC(), rc, InterpolationModeDefault);
				image.Destroy();
				graphics.ReleaseHDC(memDC);
			}
		}

		HPALETTE hpal;
		hpal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

		//Gdiplus::Bitmap을 만든다!!!  
		Bitmap bitmap((HBITMAP)bmpbuffer, hpal);
		int width = bitmap.GetWidth();
		int height = bitmap.GetHeight();

		/* GDI plus로 저장하기 !! */
		CLSID				encoderClsid;
		EncoderParameters	encoderParameters;
		ULONG				quality;

		encoderParameters.Count = 1;
		encoderParameters.Parameter[0].Guid = EncoderQuality;
		encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
		encoderParameters.Parameter[0].NumberOfValues = 1;

		// 이미지 jpg 저장시 Quality level 100.
		quality = 100;
		encoderParameters.Parameter[0].Value = &quality;

		GetEncoderClsid(_T("image/jpeg"), &encoderClsid);
		bitmap.Save(saveFolder, &encoderClsid, &encoderParameters);

		ReleaseDC(&memDC);
	}
	else
	{
		AfxMessageBox(_T("GDI+ 클래스를 초기화 하지 못했습니다.\n제작자에게 문의하세요."));
		return;
	}

	GdiplusShutdown(gdiplustToken);
	AfxMessageBox(_T("합성한 사진이 저장되었습니다.\n경로: ") + saveFolder);
}


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
