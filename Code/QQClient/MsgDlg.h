#if !defined(AFX_MSGDLG_H__08A67906_A481_465A_88E2_6651E933ECDA__INCLUDED_)
#define AFX_MSGDLG_H__08A67906_A481_465A_88E2_6651E933ECDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMsgDlg dialog

class CMsgDlg : public CDialog
{
// Construction
public:
	CString m_title;
	CMsgDlg(CWnd* pParent = NULL);   // standard constructor
    BOOL m_IsSate;
// Dialog Data
	//{{AFX_DATA(CMsgDlg)
	enum { IDD = IDD_DIALOG3 };
	CString	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMsgDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGDLG_H__08A67906_A481_465A_88E2_6651E933ECDA__INCLUDED_)
