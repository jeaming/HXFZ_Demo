
// HXFZ_Demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHXFZ_DemoApp: 
// �йش����ʵ�֣������ HXFZ_Demo.cpp
//

class CHXFZ_DemoApp : public CWinApp
{
public:
	CHXFZ_DemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHXFZ_DemoApp theApp;