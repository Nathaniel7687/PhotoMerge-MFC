#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CImage를 사용하기 위한 헤더
#include <atlimage.h>

// GDI+를 이용하기 위한 라이브러리
#include <gdiplus.h>
using namespace Gdiplus;

class CPhotoMergeDlg : public CDialogEx
{
public:
	CPhotoMergeDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOMERGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void checkIntToCString(int);


public:
	// 드래그 & 드롭 관련
	int dropFilesNum;
	CStatic dropFilesNumCtrl;
	CString dropFilesPath[100];
	afx_msg void OnDropFiles(HDROP hDropInfo);

	// 합성 사이즈 관련
	CString	mergeSizeX;
	CString	mergeSizeY;
	CEdit	mergeSizeCtrlX;
	CEdit	mergeSizeCtrlY;

	// 합성 사이즈 콤보박스 관련
	CComboBox mergeSizeComboCtrl;
	afx_msg void OnSelectMergeSizeCombo();

	// 합성 배열 관련
	CString	arrangemNumX;
	CString	arrangemNumY;
	CString	arrangemSpace;
	CEdit	arrangemNumCtrlX;
	CEdit	arrangemNumCtrlY;
	CEdit	arrangemSpaceCtrl;

	// 항상 위 관련
	BOOL windowTopMost;
	afx_msg void OnClickWindowTopMostCheck();

	// 투명도 관련
	LONG		transExtendedStyle;
	CSliderCtrl	transSliderCtrl;
	afx_msg void OnNMCustomdrawTransSlider(NMHDR *pNMHDR, LRESULT *pResult);

	// 저장폴더 라디오 버튼 관련
	CString saveFileName;
	CButton saveDefFolderRadioCtrl;
	CButton saveDifFolderRadioCtrl;
	CString saveDefFolder;
	CString saveDifFolder;
	CEdit	saveDifFolderCtrl;
	afx_msg void OnSelectSaveDifFolder();
	afx_msg void OnOpenSaveDefFolder();
	afx_msg void OnOpenSaveDifFolder();

	ULONG_PTR			gdiplustToken;
	GdiplusStartupInput	gdiplusStartupInput;
	afx_msg void OnMergePhotos();

	void Wait(DWORD);
};
