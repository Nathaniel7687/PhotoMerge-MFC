
// PhotoMerge.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPhotoMergeApp:
// �� Ŭ������ ������ ���ؼ��� PhotoMerge.cpp�� �����Ͻʽÿ�.
//

class CPhotoMergeApp : public CWinApp
{
public:
	CPhotoMergeApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPhotoMergeApp theApp;