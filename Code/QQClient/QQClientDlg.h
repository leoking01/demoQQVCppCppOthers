// QQClientDlg.h : header file
//

#if !defined(AFX_QQCLIENTDLG_H__D1A81BD6_E04B_4701_ACEF_4700658E50DB__INCLUDED_)
#define AFX_QQCLIENTDLG_H__D1A81BD6_E04B_4701_ACEF_4700658E50DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include"LoginDlg.h"
////////////自定义消息/////////////////////

#define WM_MSGRECV WM_USER+1//接收好友信息
#define WM_SEVMSG WM_USER+2//接收服务器信息
#define WM_NOTIFYICONMSG WM_USER+3//托盘消息
#define WM_RECVFRIENDDATA WM_USER+4//接收好友信息
/////////////////////////////////////////////////////////////////////////////
 
struct UserData//用户信息结构
{
	UINT id;//用户ID
	CString Name;//用户姓名
	UINT code;//密码
	BOOL IsOnline;//状态
	int FriendId[10];//好友ID（服务器尚未支持）
	CString ip;//IP地址
	UINT port;
};
//////////////以下为线程参数结构体////////////////////
struct Param
{
	HWND hwnd;
	SOCKET m_socket;
}; 
struct SevParam
{
	SOCKET m_socket;
	CString str;
	SOCKADDR_IN addr;
	HWND hwnd;
};
struct ReavDataParam
{
	SOCKET m_socket;
	SOCKADDR_IN addr;
	HWND hwnd;

};
 
class CQQClientDlg : public CDialog
{
 
public:
	CQQClientDlg(CWnd* pParent = NULL);	 
	static DWORD WINAPI SevConProc(LPVOID lpParameter);//请求连接服务器
	BOOL InitSocket();//初试华套接字
	static DWORD WINAPI RecMsgProc( LPVOID lpParameter);//接收好友好来信息函数
	static DWORD WINAPI RecvFriendData(LPVOID lpParameter);//接收好友信息和服务器信息
	
	void SendMsg();//发送消息
	~CQQClientDlg();
  
	// Dialog Data
	//{{AFX_DATA(CQQClientDlg)
	enum { IDD = IDD_QQCLIENT_DIALOG };
	CListBox	m_listUser;
	//}}AFX_DATA
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQQClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
    
// Implementation
protected:
	HICON m_hIcon;
   
	// Generated message map functions
	//{{AFX_MSG(CQQClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg LRESULT OnMsgRecv(WPARAM wParam,LPARAM lParam);//响应自定消息WM-RECVMSG
	afx_msg LRESULT OnSevMsg(WPARAM wParam,LPARAM lParam);//响应自定消息WM-SEVMSG
	afx_msg LRESULT OnRecvFriendData(WPARAM wParam,LPARAM lParam);//响应自定消息WM-RECVFRIENDDATA
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
    afx_msg LRESULT OnNotifyIconMsg(WPARAM wParam,LPARAM lParam);////响应自定消息WM-NOTIFYICONMSG
	afx_msg void OnExit();
	afx_msg void OnHide();
	afx_msg void OnShow();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDblclkList1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnButton1();
	afx_msg void OnButAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	

	SOCKADDR_IN m_AddrSev;//服务器地址
	SOCKET m_sevSocket;
	SOCKADDR_IN m_SevAddr;
	SOCKADDR_IN m_SendToAddr;
	SOCKET SendToSocket;
	
	UINT FriendDataPort;
	UINT RecvMsgPort;
    UINT SevMsgPort;

	SOCKET m_sendSocket;
	CString m_msg;
	UserData *Pfrienddata;
	UINT friendCount;
	UserData me;//  保存个人信息
	NOTIFYICONDATA nd;
 
	SOCKADDR_IN AddrMsgSend;
	SOCKET dataRecvSocket;
	SOCKET m_listenSocket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QQCLIENTDLG_H__D1A81BD6_E04B_4701_ACEF_4700658E50DB__INCLUDED_)
