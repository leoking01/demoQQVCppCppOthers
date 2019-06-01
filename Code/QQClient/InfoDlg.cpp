// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QQClient.h"
#include "InfoDlg.h"
#include"AppIdDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
	m_nPort = 0;
	m_code = 0;
	m_id = 0;
	//}}AFX_DATA_INIT
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
	DDX_Control(pDX, IDC_IPADDRESS, m_ipAddr);
	DDX_Text(pDX, IDC_EDIT_PORTID, m_nPort);
	DDX_Text(pDX, IDC_EDIT_CODE, m_code);
	DDX_Text(pDX, IDC_EDIT_NAME, m_id);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoDlg)
	ON_BN_CLICKED(IDC_BTN_NETSET, OnBtnNetset)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_USER_APP, OnUserApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers

BOOL CInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    GetWindowRect(&m_strrc);
	GetWindowRect(&m_rect);

    m_rect.bottom=m_rect.top;
	m_rect.bottom+=20;

    IsExplore=FALSE;
    m_strrc.bottom-=150;
    SetWindowRect();
	SetTimer(1,140,NULL);
 	((CEdit*)GetDlgItem(IDC_EDIT_NAME))->SetWindowText("");
 	((CEdit*)GetDlgItem(IDC_EDIT_CODE))->SetWindowText("");
    
	m_str="About\n\r\n\rName:\n\rMyQQ\n\r\n\rProgramer:\n\rzhaoning\n\r\n\rQQ:\n\r363788603\n\rE_mail:\n\rzhaoning@zzti.edu.cn\n\r\n\rAddress:\n\rZhongyuan Universty of Technology\n\r\n\rDate:\n\r2005/12/7"; 
    m_nPort=6020;
	UpdateData(FALSE);
	msgType=1;
	return TRUE;   
}

void CInfoDlg::SetWindowRect()
{
    SetWindowPos(NULL,m_strrc.left,m_strrc.top,m_strrc.Width(),m_strrc.Height(),SWP_NOMOVE|SWP_SHOWWINDOW);
}

void CInfoDlg::OnBtnNetset() 
{
	// TODO: Add your control notification handler code here
	if(IsExplore)
	{
	    m_strrc.bottom-=150;
		IsExplore=FALSE;
	
	}
	else
	{
		m_strrc.bottom+=150;
		IsExplore=TRUE;
	}
	
	SetWindowRect();
	
}

HBRUSH CInfoDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

void CInfoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
 	static int i=0;
	m_bitmap.DeleteObject();
	switch(i%8)
	{
	case 0:
	m_bitmap.LoadBitmap(IDB_BITMAP1);
	break;
	case 1:
	m_bitmap.LoadBitmap(IDB_BITMAP2);
	break;
	case 2:
	m_bitmap.LoadBitmap(IDB_BITMAP3);
	break;
	case 3:
	m_bitmap.LoadBitmap(IDB_BITMAP4);
	break;
	case 4:
	m_bitmap.LoadBitmap(IDB_BITMAP5);
	break;
	case 5:
	m_bitmap.LoadBitmap(IDB_BITMAP6);
	break;
	case 6:
	m_bitmap.LoadBitmap(IDB_BITMAP7);
	break;
	case 7:
	m_bitmap.LoadBitmap(IDB_BITMAP8);
	break;
	}
	i++;
	i%=8;
	 
	InvalidateRect(m_rect);
    if(m_rect.bottom-m_rect.top>=300)
	{
		m_rect.top=m_rect.bottom;
	}


	m_rect.top-=10;

	((CStatic*)GetDlgItem(IDC_STATIC_BT))->SetBitmap(m_bitmap);

  
	CDialog::OnTimer(nIDEvent);
}

void CInfoDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
    dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,0,0));
	CRect rc;
	rc.right=m_rect.right;
	rc.left=m_rect.left;
	rc.bottom=m_rect.bottom;
	rc.top=rc.bottom;
	rc.top-=50;
	dc.FillSolidRect(rc,RGB(100,100,100));
	dc.DrawText(m_str,&m_rect,DT_CENTER);
 
}

void CInfoDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS))->GetAddress(ip);
	if(msgType==1)
	{
	UpdateData();
    msg.Format("%d#%d@%d",msgType,m_id,m_code);
	}
	
	CDialog::OnOK();
}

void CInfoDlg::OnUserApp() 
{
	// TODO: Add your control notification handler code here
	CAppIdDlg dlg;
    
	if(dlg.DoModal()==IDOK)
	{
		msgType=2;
		msg.Format("%d#%s@%d",msgType,dlg.m_username,dlg.m_usercode);
		m_id=0;
		m_code=0;
		UpdateData(FALSE);
    }
}
