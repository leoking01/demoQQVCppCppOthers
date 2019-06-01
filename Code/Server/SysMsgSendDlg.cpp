// SysMsgSendDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chat.h"
#include "SysMsgSendDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSysMsgSendDlg dialog


CSysMsgSendDlg::CSysMsgSendDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysMsgSendDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysMsgSendDlg)
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void CSysMsgSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysMsgSendDlg)
	DDX_Text(pDX, IDC_EDIT_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSysMsgSendDlg, CDialog)
	//{{AFX_MSG_MAP(CSysMsgSendDlg)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysMsgSendDlg message handlers

void CSysMsgSendDlg::OnBtnCancel() 
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CSysMsgSendDlg::OnBtnOk() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	OnOK();
}
