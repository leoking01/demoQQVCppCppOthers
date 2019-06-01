// AppIdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "qqclient.h"
#include "AppIdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAppIdDlg dialog


CAppIdDlg::CAppIdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAppIdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAppIdDlg)
	m_username = _T("");
	m_usercode = 0;
	//}}AFX_DATA_INIT
}


void CAppIdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAppIdDlg)
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_usercode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAppIdDlg, CDialog)
	//{{AFX_MSG_MAP(CAppIdDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAppIdDlg message handlers

void CAppIdDlg::OnButton1() 
{
OnCancel();	
}

HBRUSH CAppIdDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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
