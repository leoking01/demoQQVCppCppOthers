#if !defined(AFX_SYSMSGSENDDLG_H__D4AD4C30_2920_47E8_B55D_4497AB206446__INCLUDED_)
#define AFX_SYSMSGSENDDLG_H__D4AD4C30_2920_47E8_B55D_4497AB206446__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysMsgSendDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSysMsgSendDlg dialog

class CSysMsgSendDlg : public CDialog
{
// Construction
public:
	CSysMsgSendDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSysMsgSendDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysMsgSendDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSysMsgSendDlg)
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnOk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSMSGSENDDLG_H__D4AD4C30_2920_47E8_B55D_4497AB206446__INCLUDED_)
