#if !defined(AFX_SENDMSG_H__6C507651_2CB1_449C_B7C3_E78D6BD23EB8__INCLUDED_)
#define AFX_SENDMSG_H__6C507651_2CB1_449C_B7C3_E78D6BD23EB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SendMsg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSendMsg dialog

class CSendMsg : public CDialog
{
// Construction
public:
	CSendMsg(CWnd* pParent = NULL);   // standard constructor
	CString m_title;
// Dialog Data
	//{{AFX_DATA(CSendMsg)
	enum { IDD = IDD_DIALOG4 };
	CString	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSendMsg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSendMsg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SENDMSG_H__6C507651_2CB1_449C_B7C3_E78D6BD23EB8__INCLUDED_)
