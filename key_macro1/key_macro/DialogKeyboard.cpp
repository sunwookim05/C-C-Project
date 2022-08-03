#include "stdafx.h"
#include "key_macro.h"
#include "virtual_key.h"
#include "DialogKeyboard.h"
#include "key_hook.h"

CDialogKeyboard  *g_keyDlg = NULL;

// 프로그램이 실행되는 동안 대화상자 아이템에 
// 설정된 값을 저장하고 있는 변수들을 static으로 선언
static long _key = 0x30;
static long _flags = 3;

IMPLEMENT_DYNAMIC(CDialogKeyboard, CDialog)

CDialogKeyboard::CDialogKeyboard(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogKeyboard::IDD, pParent)
{
	g_keyDlg = this;
}

CDialogKeyboard::~CDialogKeyboard()
{
	g_keyDlg = NULL;
}

void CDialogKeyboard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogKeyboard, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogKeyboard::OnBnClickedOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


BOOL CDialogKeyboard::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (_item.type == sMacroItem::NONE) {
		SetWindowText ("키보드 이벤트 추가");
		// 기본값 설정
		_item.type = sMacroItem::KEY;
		_item.key.vk = _key;
		_item.key.flags = _flags;
	}
	else {
		SetWindowText ("키보드 이벤트 편집");
	}

	SendDlgItemMessage (IDC_COMBO_KEYBOARD, CB_INITSTORAGE, 256, 100);
	SendDlgItemMessage (IDC_COMBO_KEYBOARD, WM_SETREDRAW, 0, 0);
	for (int i=0; i<255 && g_vk_list[i].vk != -1; ++i) {
		SendDlgItemMessage (IDC_COMBO_KEYBOARD, CB_INSERTSTRING, i, (LPARAM)GetVirtualKeyDesc(i));
	}
	SendDlgItemMessage (IDC_COMBO_KEYBOARD, CB_SETCURSEL, getVkIndex (_item.key.vk));
	SendDlgItemMessage (IDC_COMBO_KEYBOARD, WM_SETREDRAW, 1, 0);

	CheckDlgButton (IDC_RADIO_KEY_3, (_item.key.flags == 3) ? BST_CHECKED : BST_UNCHECKED); // 누르고 떼기
	CheckDlgButton (IDC_RADIO_KEY_1, (_item.key.flags == 1) ? BST_CHECKED : BST_UNCHECKED); // 누르기
	CheckDlgButton (IDC_RADIO_KEY_2, (_item.key.flags == 2) ? BST_CHECKED : BST_UNCHECKED); // 떼기

	GetDlgItem(IDC_COMBO_KEYBOARD)->SetFocus ();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogKeyboard::OnKeyEvent (int vk)
{
	if (GetFocus () == GetDlgItem (IDC_COMBO_KEYBOARD)) {
		if (vk && !(vk&0x10000)) {
			// 키보드 이벤트를 바로 처리하지 않고 timer를 사용하여 30ms 후에
			// 입력된 가상키로 ComboBox 항목을 선택한다: OnTimer() 함수에서 nIDEvent == 1000 참조
			_vk = vk;
			SetTimer (1000, 30, NULL);
		}
	}
}

void CDialogKeyboard::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1000) {
		GetDlgItem(IDC_COMBO_KEYBOARD)->PostMessage (CB_SETCURSEL, getVkIndex (_vk));
		KillTimer (1000);
	}

	CDialog::OnTimer(nIDEvent);
}

void CDialogKeyboard::OnBnClickedOk()
{
	int index = SendDlgItemMessage (IDC_COMBO_KEYBOARD, CB_GETCURSEL, 0, 0);
	if (index != -1) {
		_item.key.vk = GetVirtualKeyCode (index);
	}

	if      (IsDlgButtonChecked (IDC_RADIO_KEY_3)) _item.key.flags = 3;	// 누르고 떼기
	else if (IsDlgButtonChecked (IDC_RADIO_KEY_1)) _item.key.flags = 1;	// 누르기
	else if (IsDlgButtonChecked (IDC_RADIO_KEY_2)) _item.key.flags = 2;	// 떼기

	_key = _item.key.vk;
	_flags = _item.key.flags;

	OnOK();
}

