
// DrawTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDrawToolApp:
// �йش����ʵ�֣������ DrawTool.cpp
//

class CDrawToolApp : public CWinApp
{
public:
	CDrawToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

protected:
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_pGdiToken;
public:
	virtual int ExitInstance();
};

extern CDrawToolApp theApp;