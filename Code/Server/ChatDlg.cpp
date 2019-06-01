// ChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chat.h"
#include "ChatDlg.h"
#include"SysMsgSendDlg.h"
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
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
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDlg dialog

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
: CDialog(CChatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatDlg)
	m_userdisp = _T("");
	m_UserNum = 0;
	m_OnlineNum = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatDlg)
	DDX_Control(pDX, IDC_LIST2, m_list);
	//	DDX_Text(pDX, IDC_EDIT_DATA, m_userdisp);
	DDX_Text(pDX, IDC_EDIT1, m_UserNum);
	DDX_Text(pDX, IDC_EDIT2, m_OnlineNum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatDlg, CDialog)
//{{AFX_MSG_MAP(CChatDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_MESSAGE(WM_RECVDATA,OnRecvData)
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
ON_WM_CTLCOLOR()
ON_BN_CLICKED(IDC_BTN_START_SEV, OnBtnStartSev)
ON_WM_TIMER()
ON_NOTIFY(NM_RCLICK, IDC_LIST2, OnRclickList2)
ON_COMMAND(IDM_SENDMSG, OnSendmsg)
//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatDlg message handlers

BOOL CChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
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
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
    m_list.InsertColumn(0,_T("ID"));
	m_list.InsertColumn(1,_T("用户名"));
	m_list.InsertColumn(2,_T("密码"));
	m_list.InsertColumn(3,_T("IP"));
	m_list.InsertColumn(4,_T("状态"));
	m_list.SetColumnWidth(0,50);
	m_list.SetColumnWidth(1,50);
	m_list.SetColumnWidth(2,50);
	m_list.SetColumnWidth(3,120);
	m_list.SetColumnWidth(4,46);
	m_list.SetTextColor(RGB(0,255,0));
	// TODO: Add extra initialization here
    InitSocket();
	Param *p=new Param;
	p->hwnd=m_hWnd;
	p->socket=m_socket;
	
	Pfrienddata=new UserData[15];
	
	SetTimer(6,30000,NULL);
    HANDLE handle=::CreateThread(NULL,0,RecvProc,(LPVOID)p,0,NULL);
	CloseHandle(handle);
	//	ReleaseHandle(handle);
	CWnd *pWnd=GetDlgItem(IDC_BUTTON_SEND);
	pWnd->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CChatDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
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
HCURSOR CChatDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CChatDlg::InitSocket()
{
	
	msocket=socket(AF_INET,SOCK_STREAM,0);
	
    m_socket=socket(AF_INET,SOCK_DGRAM,0);
	if(m_socket==INVALID_SOCKET)
	{
		MessageBox("创建失败!");
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
	CWnd*p=GetDlgItem(IDC_EDIT_IP);
	p->SetWindowText(m_strIP);
	p=GetDlgItem(IDC_EDIT_PORT);
	p->SetWindowText("6020");
	SOCKADDR_IN SevAddr;
	SevAddr.sin_addr = ia;  // .S_un.S_addr=inet_addr("192.168.87.100");//
	SevAddr.sin_family=AF_INET;
	SevAddr.sin_port=htons(6020);
	
	
	Result=bind(m_socket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
	if(Result==SOCKET_ERROR)
	{
		MessageBox("套节字帮定失败!");
		closesocket(m_socket);
		return FALSE;
	}
	//	SevAddr.sin_port=htons(6020);
	return TRUE;
	
}

DWORD  CChatDlg::RecvProc(LPVOID lpParameter)
{
	HWND hwnd=((Param*)lpParameter)->hwnd;
	SOCKET socket=((Param*)lpParameter)->socket;
	
	char buf[200];
	//	char temp[300];
	
	SOCKADDR_IN CliAddr;
	int len=sizeof(SOCKADDR_IN);
    int Result;
	
	while(TRUE)
	{
		//::MessageBox(NULL,"Thread is Runing!","",MB_OK);
		
		Result=recvfrom(socket,buf,100,0,(sockaddr*)&CliAddr,&len);
		//	 ::MessageBox(NULL,data.Name,0,MB_OK);
		
		if(Result==SOCKET_ERROR)
		{
			::MessageBox(NULL,"Socket ERRoR!","",MB_OK);
			break;
		} 
		buf[strlen(buf)+1]='/0';
		
		
		::PostMessage(hwnd,WM_RECVDATA,(WPARAM)&CliAddr,(LPARAM)buf);
		
	}
	::MessageBox(NULL,"Thread Exit","",MB_OK);
	return 0;
	
	
}
LRESULT   CChatDlg::OnRecvData(WPARAM wParam,LPARAM lParam)
{
	SOCKADDR_IN SevAddr=*((SOCKADDR_IN*)wParam);
	SevAddr.sin_family=AF_INET;
	SevAddr.sin_port=htons(4000);
	// MessageBox(inet_ntoa(SevAddr.sin_addr));
    SOCKET m_socket1=socket(AF_INET,SOCK_DGRAM,0);
	CString str=(char*)lParam;
    //MessageBox(str);
	int i=str.Find("#",0);;
    UINT msgType;
	msgType=atoi(str.Left(i));
    str=str.Right(str.GetLength()-i-1);
	 
	CString temp;
	UINT id;
	UINT code;
	BOOL IsYes;
	UINT port1,port2,port3;
	int j,Num,n=0;
	char buf[10];
	switch(msgType)
	{
	case 1://
		//MessageBox("用户登录");
		i=str.Find("@",0);
	//	MessageBox(str);
		id=atoi(str.Left(i));

		str=str.Right(str.GetLength()-i-1);
		 
		i=str.Find("#",0);
        code=atoi(str.Left(i));
        str=str.Right(str.GetLength()-i-1);
		
		i=str.Find("#",0);
        port1=atoi(str.Left(i));
        str=str.Right(str.GetLength()-i-1);
		i=str.Find("#",0);
        port2=atoi(str.Left(i));
        str=str.Right(str.GetLength()-i-1);
		i=str.Find("#",0);
        port3=atoi(str.Left(i));
        str=str.Right(str.GetLength()-i-1);

	     
		IsYes=FALSE;
		int Result;
		for (j=0;j<UserNum;j++)
		{
			if(Pfrienddata[j].code==code&&Pfrienddata[j].id==id)
			{
				Pfrienddata[j].IsOnline=1;
				Pfrienddata[j].ip=inet_ntoa(SevAddr.sin_addr);
				Pfrienddata[j].RecvMsgPort=port3;
				Num=j;
				SevAddr.sin_port=htons(port1);
				Result=connect(Pfrienddata[j].m_socket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
				while(Result==SOCKET_ERROR&&n<3)
				{
					Result=connect(Pfrienddata[j].m_socket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
					n++;
				}
				IsYes=TRUE;
				sprintf(buf,"1@%d",UserNum);
				/////	Sleep(2000);
				if(Result==SOCKET_ERROR)
					sprintf(buf,"2@3");
					/*	else
                MessageBox("连接成功");*/
				
				break;
			}
			
		}	break;
	case 2://
		// MessageBox("用户注册");
	 
		i=str.Find("@",0);
		Pfrienddata[UserNum].Name=str.Left(i);
		str=str.Right(str.GetLength()-i-1);
		i=str.Find("#",0);
		Pfrienddata[UserNum].code=atoi(str.Left(i));

		
        str=str.Right(str.GetLength()-i-1);
		
		i=str.Find("#",0);
        port1=atoi(str.Left(i));
        str=str.Right(str.GetLength()-i-1);
		i=str.Find("#",0);
        port2=atoi(str.Left(i));
        str=str.Right(str.GetLength()-i-1);
		i=str.Find("#",0);
        port3=atoi(str.Left(i));
        str=str.Right(str.GetLength()-i-1);

		Pfrienddata[UserNum].id=1000+UserNum;
		Pfrienddata[UserNum].IsOnline=1;
		Pfrienddata[UserNum].RecvMsgPort=port3;
		Pfrienddata[UserNum].ip=inet_ntoa(SevAddr.sin_addr);
		SevAddr.sin_port=htons(port1);
		Result=connect(Pfrienddata[UserNum].m_socket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
		while(Result==SOCKET_ERROR&&n<3)
		{
			Result=connect(Pfrienddata[UserNum].m_socket,(sockaddr*)&SevAddr,sizeof(SOCKADDR));
			n++;
		}
		IsYes=TRUE;
		Num=UserNum;
		sprintf(buf,"3@%d",1000+UserNum);
		if(Result==SOCKET_ERROR)
			sprintf(buf,"2@3");
			/* MessageBox("连接失败");
			else
			MessageBox("连接成功");
		*/
		//  Sleep(2000);
		UserNum++;
		break;
	}
	
    m_DataStr.Empty();
	m_DataStr.Format("%d*",UserNum);
	for (j=0;j<(int)UserNum;j++)
	{
		temp.Format("%d@%d@%s@%d@%s@%d@#",Pfrienddata[j].code,Pfrienddata[j].id,Pfrienddata[j].Name,Pfrienddata[j].IsOnline,Pfrienddata[j].ip,Pfrienddata[j].RecvMsgPort);
		m_DataStr+=temp;
	}
	//	MessageBox(m_DataStr);
	if(msgType==2)
	{
		CString FileStr;
		for (j=0;j<UserNum;j++)
		{
			temp.Format("%d@%d@%s%@#",Pfrienddata[j].code,Pfrienddata[j].id,Pfrienddata[j].Name);
			FileStr+=temp;
		}
		CFile file;//将新注册用户信息写入文件.
		file.Open("c://userdata.txt",CFile::modeWrite);
		file.Write(FileStr,FileStr.GetLength());
		file.Close();
	}
    SevAddr.sin_port=htons(port2);
    if(IsYes)
	{
		
		//	MessageBox(m_DataStr);
		int Result=sendto(m_socket1,buf,100,0,(SOCKADDR*)&SevAddr,sizeof(SOCKADDR));
		//Sleep(3000);
		CString str=m_DataStr;
		int i;
		/*	for(i=0;i<UserNum;i++)
		if(Pfrienddata[i].m_socket==SOCKET_ERROR)
		{
		Pfrienddata[i].IsOnline=0;
		Pfrienddata[i].ip="未知IP";
	}*/
		//	send(Pfrienddata[i].m_socket,str,1000+1,0);
		//MessageBox(str);
		int SocketResult;
		for(i=0;i<UserNum;i++)
			if(Pfrienddata[i].IsOnline==1)
			{
				SocketResult=send(Pfrienddata[i].m_socket,str,str.GetLength(),0);
				if(SocketResult==SOCKET_ERROR)
				{
					Pfrienddata[i].IsOnline=0;
					Pfrienddata[i].ip="未知IP";
				}
			}
	}
	else
	{
		sprintf(buf,"2@3");
		sendto(m_socket1,buf,100,0,(SOCKADDR*)&SevAddr,sizeof(SOCKADDR));
	}
	
	return 0;
}

void CChatDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CChatDlg::OnButtonSend() 
{
	CSysMsgSendDlg dlg;
	CString str;
	int i;
	str.Format("%d*",200);
	if(dlg.DoModal()==IDOK)
	{
		str+=dlg.m_msg;
		str+="$";
		
		for(i=0;i<UserNum;i++)
		{
			if(Pfrienddata[i].IsOnline==1)
			{
				send(Pfrienddata[i].m_socket,str,str.GetLength(),0);
				
			}
		}
	}
	
}

HBRUSH CChatDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	
	HBRUSH hbr = CreateSolidBrush(RGB(100,150,240));//CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(100,150,240));
	}
	// TODO: Change any attributes of the DC here
	if(nCtlColor==CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(100,150,240));
	}
	
	return hbr;
}

void CChatDlg::OnBtnStartSev() 
{
	//////////////////读取文件中用户信息并保存在数组中//////////////////
    CFile file;
	char *ch;
	if(!file.Open("c://userdata.txt",CFile::modeRead))
	{
		if(IDYES==MessageBox("查找文件失败!是否要重新创建?","Error!",MB_ICONQUESTION|MB_YESNO))
			file.Open("c://userdata.txt",CFile::modeCreate);
			else
			return;
	}
	int length=file.GetLength();
	ch=new char[length];
	file.Read(ch,length);
	file.Close();
	CString str=ch;
	
	CString temp2,temp3;
	CString Usertemp;
    UserNum=0;
	int i,j=0;
	i=str.Find("#");
	while(i!=-1) 
	{
		
		temp2=str.Left(i);
		
		str=str.Right(str.GetLength()-i-1);
		
		i=temp2.Find("@");
		temp3=temp2.Left(i);
		temp2=temp2.Right(temp2.GetLength()-i-1);
		Pfrienddata[j].code=atoi(temp3);//1密码
		
		i=temp2.Find("@");
		temp3=temp2.Left(i);
		temp2=temp2.Right(temp2.GetLength()-i-1);
		Pfrienddata[j].id=atoi(temp3);//2用户ID
		
		i=temp2.Find("@");
		temp3=temp2.Left(i);
        temp2=temp2.Right(temp2.GetLength()-i-1);
		Pfrienddata[j].Name=temp3;//3用户姓名
        Pfrienddata[j].IsOnline=0;
        Pfrienddata[j].ip="未知IP";
		
		
		i=str.Find("#");
		j++;
		UserNum++;
	}
    m_UserNum=UserNum;
	for(j=0;j<15;j++)
	{
		Pfrienddata[j].m_socket=socket(AF_INET,SOCK_STREAM,0);
        Pfrienddata[j].RecvMsgPort=0;
	}
	////////////////////向ListCtrl中添加用户信息////////////////////////
	CString disptemp;
	for(j=0;j<UserNum;j++)
	{
		disptemp.Format("%d",Pfrienddata[j].id);
		m_list.InsertItem(j,disptemp);
		disptemp.Format("%s",Pfrienddata[j].Name);
		m_list.SetItemText(j,1,disptemp);
		disptemp.Format("%d",Pfrienddata[j].code);
		m_list.SetItemText(j,2,disptemp);
		disptemp.Format("%s",Pfrienddata[j].ip);
		m_list.SetItemText(j,3,disptemp);
		if(Pfrienddata[j].IsOnline==1)
			disptemp="在线";
		else
			disptemp="离线";
		m_list.SetItemText(j,4,disptemp);
		
	}
	////////////隐藏开启服务器按纽显示发送系统信息按纽////////////////
	CWnd *pWnd=GetDlgItem(IDC_BTN_START_SEV);
	pWnd->ShowWindow(SW_HIDE);
    
    pWnd=GetDlgItem(IDC_BUTTON_SEND);
	pWnd->ShowWindow(SW_SHOW);
	//////////////////////////////////////////////////////////////////
	UpdateData(FALSE);
	
}

void CChatDlg::OnTimer(UINT nIDEvent) 
{
	/////////////////////将所有用户信息格式华保存在 m_DataStr中/////////////////////////
	CString temp;
	int j;
    m_DataStr.Empty();
	m_DataStr.Format("%d*",UserNum);
	for (j=0;j<UserNum;j++)
	{
		temp.Format("%d@%d@%s@%d@%s@%d@#",Pfrienddata[j].code,Pfrienddata[j].id,Pfrienddata[j].Name,Pfrienddata[j].IsOnline,Pfrienddata[j].ip,Pfrienddata[j].RecvMsgPort);
		m_DataStr+=temp;
	}
	int SocketResult,i;
	////////////////////////向所有在线用户发送当前所有用户信息/////////////////////
	for(i=0;i<UserNum;i++)
		if(Pfrienddata[i].IsOnline==1)
		{
			SocketResult=send(Pfrienddata[i].m_socket,m_DataStr,m_DataStr.GetLength(),0);
			if(SocketResult==SOCKET_ERROR)
			{
				Pfrienddata[i].IsOnline=0;
				closesocket(Pfrienddata[i].m_socket);
				Pfrienddata[i].m_socket=socket(AF_INET,SOCK_STREAM,0);
				Pfrienddata[i].ip="未知IP";
			}
		}
		
		
		CString disptemp;
		m_OnlineNum=0;
		////////////////////////////更新ListCtrl中的用户信息///////////////////
		for(j=0;j<UserNum;j++)
			m_list.DeleteItem(0);
		for(j=0;j<UserNum;j++)
		{
			disptemp.Format("%d",Pfrienddata[j].id);
			m_list.InsertItem(j,disptemp);
			disptemp.Format("%s",Pfrienddata[j].Name);
			m_list.SetItemText(j,1,disptemp);
			disptemp.Format("%d",Pfrienddata[j].code);
			m_list.SetItemText(j,2,disptemp);
		
			if(Pfrienddata[j].IsOnline==1)
			{
				disptemp.Format("%s:%d",Pfrienddata[j].ip,Pfrienddata[j].RecvMsgPort);
				m_list.SetItemText(j,3,disptemp);
				disptemp="在线";
				m_OnlineNum++;
				m_list.SetItemText(j,4,disptemp);
			}
			else
			{
				disptemp.Format("%s:%d",Pfrienddata[j].ip,Pfrienddata[j].RecvMsgPort);
				m_list.SetItemText(j,3,disptemp);
				disptemp="离线";
				m_list.SetItemText(j,4,disptemp);
			}
			
		}
		
		/////////////////////////////////////////////////////////
		m_UserNum=UserNum;
		UpdateData(FALSE);
		
		CDialog::OnTimer(nIDEvent);
}

void CChatDlg::OnRclickList2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu menu;
	CPoint Point;
	menu.LoadMenu(IDR_MENU1);
	CMenu* pPopup = menu.GetSubMenu(0);
	
	GetCursorPos( &Point );
	SetForegroundWindow();
	pPopup->TrackPopupMenu(
		TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		Point.x, Point.y, this); 
	*pResult = 0;
}

void CChatDlg::OnSendmsg() 
{
	
}
