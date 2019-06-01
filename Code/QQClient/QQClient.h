// QQClient.h : main header file for the QQCLIENT application
//

#if !defined(AFX_QQCLIENT_H__B05767D9_AE16_49EE_BEA1_AD02D85AB878__INCLUDED_)
#define AFX_QQCLIENT_H__B05767D9_AE16_49EE_BEA1_AD02D85AB878__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQQClientApp:
// See QQClient.cpp for the implementation of this class
//

class CQQClientApp : public CWinApp
{
public:
	CQQClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQQClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQQClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QQCLIENT_H__B05767D9_AE16_49EE_BEA1_AD02D85AB878__INCLUDED_)
