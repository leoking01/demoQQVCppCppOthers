// SendMsg.cpp : implementation file
//

#include "stdafx.h"
#include "qqclient.h"
#include "SendMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSendMsg dialog


CSendMsg::CSendMsg(CWnd* pParent /*=NULL*/)
	: CDialog(CSendMsg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSendMsg)
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void CSendMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSendMsg)
	DDX_Text(pDX, IDC_EDIT1, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSendMsg, CDialog)
	//{{AFX_MSG_MAP(CSendMsg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSendMsg message handlers

BOOL CSendMsg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(m_title);
	SetDlgItemText(IDC_EDIT_ABOUT,m_title);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSendMsg::OnOK() 
{
 
	UpdateData();
	CDialog::OnOK();
}

void CSendMsg::OnButton1() 
{
 
	OnCancel();
}

HBRUSH CSendMsg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CreateSolidBrush(RGB(150,200,150));
	if(nCtlColor==CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(255,0,0));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(100,150,240));
	}
	
	if(nCtlColor==CTLCOLOR_EDIT)
	{
		pDC->SetTextColor(RGB(0,0,255));
		pDC->SetBkColor(TRANSPARENT);
		pDC->SetBkColor(RGB(150,200,150));
	}
	return hbr;
	
}
