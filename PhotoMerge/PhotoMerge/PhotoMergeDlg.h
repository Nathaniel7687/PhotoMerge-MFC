
// PhotoMergeDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPhotoMergeDlg 대화 상자
class CPhotoMergeDlg : public CDialogEx
{
// 생성입니다.
public:
	CPhotoMergeDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOMERGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedWindowCheck1();
	BOOL mWinBtn;
	CString mSaveFileName;

	// 합성 사이즈 에디트 컨트롤러 멤버변수
	CString mSizeEditX;
	CString mSizeEditY;
	CEdit mSizeEditCtrlX;
	CEdit mSizeEditCtrlY;

	// 합성 배열 에디트 컨트롤러 멤버변수
	CString mSizeEditNumX;
	CString mSizeEditNumY;
	CEdit mSizeEditNumCtrlX;
	CEdit mSizeEditNumCtrlY;

	afx_msg void OnCbnSelchangeSizeCombo1();
	CComboBox mSizeComboCtrl;
	CString mSizeComboVal;

	CSliderCtrl mWinTrnsSlideCtrl;
	LONG ExtendedStyle;
	CStatic mPhotoCntStaticCtrl;	// 드래그 드롭한 파일 갯수 표시
	afx_msg void OnNMCustomdrawWindowTrnsSlide(NMHDR *pNMHDR, LRESULT *pResult);

	// 저장폴더 라디오 버튼 변수
	int mSaveFolder;
};
