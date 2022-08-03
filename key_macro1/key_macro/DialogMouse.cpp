#include "stdafx.h"
#include "key_macro.h"
#include "macro_def.h"
#include "DialogMouse.h"
#include "virtual_key.h"
#include "key_hook.h"
#include "Common.h"
#include "AppIni.h"

CDialogMouse *g_mouseDlg = NULL;

// 프로그램이 실행되는 동안 대화상자 아이템에 
// 설정된 값을 저장하고 있는 변수들을 static으로 선언
static long _flags = MOUSEEVENTF_MOVE|MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP;
static long _x = 0;
static long _y = 0;

IMPLEMENT_DYNAMIC(CDialogMouse, CDialog)

CDialogMouse::CDialogMouse(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMouse::IDD, pParent)
{
	g_mouseDlg = this;
}

CDialogMouse::~CDialogMouse()
{
	g_mouseDlg = NULL;
}

void CDialogMouse::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialogMouse, CDialog)
	ON_BN_CLICKED(IDOK, &CDialogMouse::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_ABSPOS, &CDialogMouse::OnBnClickedCheckAbspos)
	ON_BN_CLICKED(IDC_CHECK_WHEEL, &CDialogMouse::OnBnClickedCheckWheel)
	ON_CBN_SELCHANGE(IDC_COMBO_KEY, &CDialogMouse::OnCbnSelchangeComboKey)
END_MESSAGE_MAP()


BOOL CDialogMouse::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (_item.type == sMacroItem::NONE) {
		SetWindowText ("마우스 이벤트 추가");
		// 기본값 설정
		_item.type = sMacroItem::MOUSE;
		_item.mouse.flags = _flags;
		_item.mouse.x = _x;
		_item.mouse.y = _y;
	}
	else {
		SetWindowText ("마우스 이벤트 편집");
	}

	SendDlgItemMessage (IDC_COMBO_KEY, CB_INITSTORAGE, 256, 100);
	SendDlgItemMessage (IDC_COMBO_KEY, WM_SETREDRAW, 0, 0);
	for (int i=0; i<255 && g_vk_list[i].vk != -1; ++i) {
		SendDlgItemMessage (IDC_COMBO_KEY, CB_INSERTSTRING, i, (LPARAM)GetVirtualKeyDesc(i));
	}
	SendDlgItemMessage (IDC_COMBO_KEY, CB_SETCURSEL, getVkIndex (g_ini.keyMousePosCapture));
	SendDlgItemMessage (IDC_COMBO_KEY, WM_SETREDRAW, 1, 0);

	CheckDlgButton (IDC_CHECK_ABSPOS, (_item.mouse.flags & MOUSEEVENTF_MOVE) ? BST_CHECKED : BST_UNCHECKED); 
	SetDlgItemInt (IDC_EDIT_ABSPOS_X, _item.mouse.x);
	SetDlgItemInt (IDC_EDIT_ABSPOS_Y, _item.mouse.y);

	CheckDlgButton (IDC_CHECK_WHEEL, (_item.mouse.flags & MOUSEEVENTF_WHEEL) ? BST_CHECKED : BST_UNCHECKED); 
	SetDlgItemInt  (IDC_EDIT_WHEEL,  (_item.mouse.flags & MOUSEEVENTF_WHEEL) ? (short)HIWORD(_item.mouse.flags) : 0);
	
	int button_select = 0;
	int button_state = 3;

	if (_item.mouse.flags & (MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP)) {
		button_select = 1;
		button_state = (_item.mouse.flags >> 1) & 0x03;
	}
	else if (_item.mouse.flags & (MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP)) { 
		button_select = 2;
		button_state = (_item.mouse.flags >> 3) & 0x03;
	}
	else if (_item.mouse.flags & (MOUSEEVENTF_MIDDLEDOWN|MOUSEEVENTF_MIDDLEUP)) { 
		button_select = 3;
		button_state = (_item.mouse.flags >> 5) & 0x03;
	}
	else if (_item.mouse.flags & (MOUSEEVENTF_XDOWN|MOUSEEVENTF_XUP)) {
		if      (HIWORD(_item.mouse.flags) == XBUTTON1) button_select = 4;
		else if (HIWORD(_item.mouse.flags) == XBUTTON2) button_select = 5;
		button_state = (_item.mouse.flags >> 7) & 0x03;
	}

	SendDlgItemMessage (IDC_COMBO_BUTTON_SELECT, CB_SETCURSEL, button_select);

	CheckDlgButton (IDC_RADIO_BUTTON_CLICK, (button_state == 3) ? BST_CHECKED : BST_UNCHECKED);	// 마우스 버튼 클릭
	CheckDlgButton (IDC_RADIO_BUTTON_DOWN,  (button_state == 1) ? BST_CHECKED : BST_UNCHECKED);	// 마우스 버튼 누르기
	CheckDlgButton (IDC_RADIO_BUTTON_UP,    (button_state == 2) ? BST_CHECKED : BST_UNCHECKED); // 마우스 버튼 떼기

	OnBnClickedCheckAbspos();
	OnBnClickedCheckWheel();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogMouse::OnKeyEvent (int vk)
{
	if (vk == g_ini.keyMousePosCapture) {
		int x = GetDlgItemInt (IDC_EDIT_CURPOS_X, NULL, TRUE);
		int y = GetDlgItemInt (IDC_EDIT_CURPOS_Y, NULL, TRUE);

		SetDlgItemInt (IDC_EDIT_ABSPOS_X, x, TRUE);
		SetDlgItemInt (IDC_EDIT_ABSPOS_Y, y, TRUE);
	}
}

void CDialogMouse::OnMouseEvent (int mx, int my)
{
	SetDlgItemInt (IDC_EDIT_CURPOS_X, mx);
	SetDlgItemInt (IDC_EDIT_CURPOS_Y, my);
}

void CDialogMouse::OnBnClickedOk()
{
	_flags = 0;

	if (IsDlgButtonChecked (IDC_CHECK_ABSPOS))   _flags |= MOUSEEVENTF_MOVE;
	if (IsDlgButtonChecked (IDC_CHECK_WHEEL))    _flags |= MOUSEEVENTF_WHEEL;

	_x = GetDlgItemInt (IDC_EDIT_ABSPOS_X);
	_y = GetDlgItemInt (IDC_EDIT_ABSPOS_Y);

	int button_select = SendDlgItemMessage (IDC_COMBO_BUTTON_SELECT, CB_GETCURSEL, 0, 0);
	int button_state = 0;

	if (IsDlgButtonChecked (IDC_RADIO_BUTTON_CLICK))   button_state = 3;	// 마우스 버튼 클릭
	if (IsDlgButtonChecked (IDC_RADIO_BUTTON_DOWN))    button_state = 1;	// 마우스 버튼 누르기
	if (IsDlgButtonChecked (IDC_RADIO_BUTTON_UP))      button_state = 2;	// 마우스 버튼 떼기

	if (button_select == 1 && button_state == 3) _flags |= MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP;
	if (button_select == 1 && button_state == 1) _flags |= MOUSEEVENTF_LEFTDOWN;
	if (button_select == 1 && button_state == 2) _flags |= MOUSEEVENTF_LEFTUP;

	if (button_select == 2 && button_state == 3) _flags |= MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP;
	if (button_select == 2 && button_state == 1) _flags |= MOUSEEVENTF_RIGHTDOWN;
	if (button_select == 2 && button_state == 2) _flags |= MOUSEEVENTF_RIGHTUP;

	if (button_select == 3 && button_state == 3) _flags |= MOUSEEVENTF_MIDDLEDOWN|MOUSEEVENTF_MIDDLEUP;
	if (button_select == 3 && button_state == 1) _flags |= MOUSEEVENTF_MIDDLEDOWN;
	if (button_select == 3 && button_state == 2) _flags |= MOUSEEVENTF_MIDDLEUP;

	// 마우스의 휠 이벤트와 X1, X2 버튼은 서로 변수를 공유하기 때문에 같이 사용할 수 없다.
	if (_flags&MOUSEEVENTF_WHEEL) {
		_flags |= MAKELONG(0, GetDlgItemInt (IDC_EDIT_WHEEL));
	}
	else {
		if (button_select == 4 && button_state == 3) _flags |= MAKELONG(MOUSEEVENTF_XDOWN|MOUSEEVENTF_XUP, XBUTTON1);
		if (button_select == 4 && button_state == 1) _flags |= MAKELONG(MOUSEEVENTF_XDOWN                , XBUTTON1);
		if (button_select == 4 && button_state == 2) _flags |= MAKELONG(MOUSEEVENTF_XUP                  , XBUTTON1);

		if (button_select == 5 && button_state == 3) _flags |= MAKELONG(MOUSEEVENTF_XDOWN|MOUSEEVENTF_XUP, XBUTTON2);
		if (button_select == 5 && button_state == 1) _flags |= MAKELONG(MOUSEEVENTF_XDOWN                , XBUTTON2);
		if (button_select == 5 && button_state == 2) _flags |= MAKELONG(MOUSEEVENTF_XUP                  , XBUTTON2);
	}

	_item.mouse.flags = _flags;
	_item.mouse.x = _x;
	_item.mouse.y = _y;

	if (!_flags) {
		AfxMessageBox ("마우스의 아무런 기능도 선택되지 않았습니다.");
	}
	else {
		OnOK();
	}
}

void CDialogMouse::OnBnClickedCheckAbspos()
{
	BOOL enable = (IsDlgButtonChecked (IDC_CHECK_ABSPOS) == BST_CHECKED) ? TRUE : FALSE;

	GetDlgItem (IDC_EDIT_ABSPOS_X)->EnableWindow (enable);
	GetDlgItem (IDC_EDIT_ABSPOS_Y)->EnableWindow (enable);
}

void CDialogMouse::OnBnClickedCheckWheel()
{
	BOOL enable = (IsDlgButtonChecked (IDC_CHECK_WHEEL) == BST_CHECKED) ? TRUE : FALSE;

	GetDlgItem (IDC_EDIT_WHEEL)->EnableWindow (enable);
}

void CDialogMouse::OnCbnSelchangeComboKey()
{
	int index = SendDlgItemMessage (IDC_COMBO_KEY, CB_GETCURSEL, 0, 0);
	if (index != -1) {
		g_ini.keyMousePosCapture = GetVirtualKeyCode(index);
	}
}
