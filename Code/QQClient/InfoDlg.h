#if !defined(AFX_INFODLG_H__A5D83249_ED2E_46EC_9AA0_F5932F2CA399__INCLUDED_)
#define AFX_INFODLG_H__A5D83249_ED2E_46EC_9AA0_F5932F2CA399__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog

class CInfoDlg : public CDialog
{
// Construction
public:
	CString msg;
	UINT msgType;
	void SetWindowRect();
	CInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInfoDlg)
	enum { IDD = IDD_DIALOG2 };
	CIPAddressCtrl	m_ipAddr;
	UINT	m_nPort;
	UINT	m_code;
	UINT	m_id;
	DWORD ip;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnNetset();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnUserApp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_str;
	CBitmap m_bitmap;
	CRect m_rect;
	CRect m_strrc;
	BOOL IsExplore;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFODLG_H__A5D83249_ED2E_46EC_9AA0_F5932F2CA399__INCLUDED_)
