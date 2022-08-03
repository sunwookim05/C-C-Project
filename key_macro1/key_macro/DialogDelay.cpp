#include "stdafx.h"
#include "key_macro.h"
#include "DialogDelay.h"
#include "Common.h"

// ���α׷��� ����Ǵ� ���� ��ȭ���� �����ۿ� 
// ������ ���� �����ϰ� �ִ� �������� static���� ����
static long _delay = 1000;

IMPLEMENT_DYNAMIC(CDialogDelay, CDialog)

CDialogDelay::CDialogDelay(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogDelay::IDD, pParent)
{
}

CDialogDelay::~CDialogDelay()
{
}

void CDialogDelay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogDelay, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogDelay::OnBnClickedOk)
END_MESSAGE_MAP()

double CDialogDelay::GetDlgItemDouble (int nIDDlgItem)
{
	char text[256];

	GetDlgItemText (nIDDlgItem, text, 255);
	text[255] = 0;

	return strtod (text, NULL);
}

void CDialogDelay::SetDlgItemDouble (int nIDDlgItem, double value)
{
	char text[256];

	sprintf (text, "%0.3f", value);
	SetDlgItemText (nIDDlgItem, text);
}

BOOL CDialogDelay::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (_item.type == sMacroItem::NONE) {
		SetWindowText ("�ð� ���� �߰�");
		// �⺻�� ����
		_item.type = sMacroItem::DELAY;
		_item.time.delay = _delay;
	}
	else {
		SetWindowText ("�ð� ���� ����");
	}

	SetDlgItemDouble (IDC_EDIT_DELAY, (double)_item.time.delay/1000.);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogDelay::OnBnClickedOk()
{
	_delay = (int)(1000*GetDlgItemDouble (IDC_EDIT_DELAY));
	_delay = BOUND(_delay, 33L, 86400000L);

	_item.time.delay = _delay;

	OnOK();
}
