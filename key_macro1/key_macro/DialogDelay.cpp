#include "stdafx.h"
#include "key_macro.h"
#include "DialogDelay.h"
#include "Common.h"

// 프로그램이 실행되는 동안 대화상자 아이템에 
// 설정된 값을 저장하고 있는 변수들을 static으로 선언
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
		SetWindowText ("시간 지연 추가");
		// 기본값 설정
		_item.type = sMacroItem::DELAY;
		_item.time.delay = _delay;
	}
	else {
		SetWindowText ("시간 지연 편집");
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
