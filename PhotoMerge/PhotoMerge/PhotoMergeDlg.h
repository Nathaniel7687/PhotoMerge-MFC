
// PhotoMergeDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CPhotoMergeDlg ��ȭ ����
class CPhotoMergeDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CPhotoMergeDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOMERGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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

	CString mSizeEditX;
	CString mSizeEditY;
	afx_msg void OnCbnSelchangeSizeCombo1();
	CComboBox mSizeComboCtrl;
	CString mSizeComboVal;

	CSliderCtrl mWinTrnsSlideCtrl;
	LONG ExtendedStyle;
	afx_msg void OnNMCustomdrawWindowTrnsSlide(NMHDR *pNMHDR, LRESULT *pResult);

	// �������� ���� ��ư ����
	int mSaveFolder;
	CString mSizeEditNumX;
	CString mSizeEditNumY;
};
