// ChatDlg.h : header file
//

#if !defined(AFX_CHATDLG_H__0CB92418_7525_4276_A88A_07F80B485DE3__INCLUDED_)
#define AFX_CHATDLG_H__0CB92418_7525_4276_A88A_07F80B485DE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WM_RECVDATA   WM_USER+1
/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog
struct Param
{
	SOCKET socket;
	HWND hwnd;
};
struct UserData
{
	UINT id;
	CString Name;
	UINT code;
	BOOL IsOnline;
	int FriendId[10];
	CString ip;
	SOCKET m_socket;
	UINT RecvMsgPort;
};
class CChatDlg : public CDialog
{
// Construction
public:
	UINT UserNum;
	SOCKET sockettemp;
	CChatDlg(CWnd* pParent = NULL);	// standard constructor
    UserData *Pfrienddata;
	CString m_DataStr;
	SOCKADDR_IN AddrMsgSend;
	SOCKET msocket;
// Dialog Data
	//{{AFX_DATA(CChatDlg)
	enum { IDD = IDD_CHAT_DIALOG };
	CListCtrl	m_list;
	CString	m_userdisp;
	UINT	m_UserNum;
	UINT	m_OnlineNum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    SOCKADDR_IN SevAddr;
	// Generated message map functions
	//{{AFX_MSG(CChatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT  OnRecvData(WPARAM wParam,LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonSend();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnStartSev();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSendmsg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	static DWORD  WINAPI RecvProc( LPVOID lpParameter);
	BOOL InitSocket();
	SOCKET m_socket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATDLG_H__0CB92418_7525_4276_A88A_07F80B485DE3__INCLUDED_)
