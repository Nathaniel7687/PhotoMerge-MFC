#pragma once
#include "afxwin.h"
#include "afxcmn.h"

// CImage�� ����ϱ� ���� ���
#include <atlimage.h>

// GDI+�� �̿��ϱ� ���� ���̺귯��
#include <gdiplus.h>
using namespace Gdiplus;

class CPhotoMergeDlg : public CDialogEx
{
public:
	CPhotoMergeDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHOTOMERGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void checkIntToCString(CString str, int w);
	void checkIntToCString(CString str, int w, int x);
	void checkIntToCString(CString str, int w, int x, int y);
	void checkIntToCString(CString str, int w, int x, int y, int z);


public:
	// �巡�� & ��� ����
	int dropFilesNum;
	CStatic dropFilesNumCtrl;
	CString dropFilesPath[1000];
	afx_msg void OnDropFiles(HDROP hDropInfo);

	// �ռ� ������ ����
	CString	mergeSizeX;
	CString	mergeSizeY;
	CEdit	mergeSizeCtrlX;
	CEdit	mergeSizeCtrlY;

	// �ռ� ������ �޺��ڽ� ����
	CComboBox mergeSizeComboCtrl;
	afx_msg void OnSelectMergeSizeCombo();

	// �ռ� �迭 ����
	CString	arrangemNumX;
	CString	arrangemNumY;
	CString	arrangemSpace;
	CEdit	arrangemNumCtrlX;
	CEdit	arrangemNumCtrlY;
	CEdit	arrangemSpaceCtrl;

	// �׻� �� ����
	BOOL windowTopMost;
	afx_msg void OnClickWindowTopMostCheck();

	// ���� ����
	LONG		transExtendedStyle;
	CSliderCtrl	transSliderCtrl;
	afx_msg void OnNMCustomdrawTransSlider(NMHDR *pNMHDR, LRESULT *pResult);

	// �������� ���� ��ư ����
	CString saveFileName;
	CEdit	saveFileNameCtrl;
	CButton saveDefFolderRadioCtrl;
	CButton saveDifFolderRadioCtrl;
	CString saveFolder;
	CString saveDefFolder;
	CString saveDifFolder;
	CEdit	saveDifFolderCtrl;
	afx_msg void OnEnChangeSaveEdit1();
	afx_msg void OnSelectSaveDifFolder();
	afx_msg void OnOpenSaveDefFolder();
	afx_msg void OnOpenSaveDifFolder();

	ULONG_PTR			gdiplustToken;
	GdiplusStartupInput	gdiplusStartupInput;
	afx_msg void OnMergePhotos();

	int GetEncoderClsid(const WCHAR *format, CLSID *pClsid);
	afx_msg void OnBnClickedAbout();
};
