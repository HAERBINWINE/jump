
// jump.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CjumpApp:
// See jump.cpp for the implementation of this class
//

const int width=1080/3;
const int height=1920/3;
class CjumpApp : public CWinApp
{
public:
	CjumpApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CjumpApp theApp;