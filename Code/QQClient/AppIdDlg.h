#if !defined(AFX_APPIDDLG_H__076A655E_9376_49BE_8651_B4E345198DE4__INCLUDED_)
#define AFX_APPIDDLG_H__076A655E_9376_49BE_8651_B4E345198DE4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AppIdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAppIdDlg dialog

class CAppIdDlg : public CDialog
{
// Construction
public:
	CAppIdDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAppIdDlg)
	enum { IDD = IDD_DIALOG5 };
	CString	m_username;
	UINT	m_usercode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAppIdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAppIdDlg)
	afx_msg void OnButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_APPIDDLG_H__076A655E_9376_49BE_8651_B4E345198DE4__INCLUDED_)
