// MsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "QQClient.h"
#include "MsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsgDlg dialog


CMsgDlg::CMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMsgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMsgDlg)
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void CMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMsgDlg)
	DDX_Text(pDX, IDC_EDIT_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CMsgDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsgDlg message handlers

void CMsgDlg::OnOK() 
{
	// TODO: Add extra validation here
	if(m_IsSate)
	{
    m_msg="";
	UpdateData(FALSE);//
    SetDlgItemText(IDOK,"发送");
	m_IsSate=FALSE;
	}
	else
    {
	UpdateData();
 	CDialog::OnOK();
	}
}

BOOL CMsgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    m_IsSate=TRUE;
	SetDlgItemText(IDOK,"回复");
    m_title+="给你发来信息";
 
	CTime tm=CTime::GetCurrentTime();
   	 
	SetDlgItemText(IDC_EDIT_TIME,tm.Format("%H:%M:%S")+"   "+m_title);
	
	SetWindowText(m_title);
	
	return TRUE;   
}

HBRUSH CMsgDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
