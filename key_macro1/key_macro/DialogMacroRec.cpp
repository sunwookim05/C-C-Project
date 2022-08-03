#include "stdafx.h"
#include <math.h>
#include "key_macro.h"
#include "DialogMacroRec.h"
#include "virtual_key.h"
#include "key_hook.h"
#include "AppIni.h"
#include "Common.h"

extern int _macro_name_ID;
extern const char *GetItemDescription (const sMacroItem &item);
CDialogMacroRec *g_recDlg = NULL;


IMPLEMENT_DYNAMIC(CDialogMacroRec, CDialog)


CDialogMacroRec::CDialogMacroRec(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMacroRec::IDD, pParent)
{
	g_recDlg = this;
}

CDialogMacroRec::~CDialogMacroRec()
{
	g_recDlg = NULL;
}

void CDialogMacroRec::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ITEMS, _listItems);
}


BEGIN_MESSAGE_MAP(CDialogMacroRec, CDialog)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_KEY, &CDialogMacroRec::OnCbnSelchangeComboKey)
	ON_BN_CLICKED(IDOK, &CDialogMacroRec::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialogMacroRec::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_CHECK_REC_STAT, &CDialogMacroRec::OnBnClickedCheckRecStat)
	ON_BN_CLICKED(IDC_CHECK_REC_KEY, &CDialogMacroRec::OnBnClickedCheckRecKey)
	ON_BN_CLICKED(IDC_CHECK_REC_MOUSE, &CDialogMacroRec::OnBnClickedCheckRecMouse)
	ON_BN_CLICKED(IDC_CHECK_REC_MOUSE_POS, &CDialogMacroRec::OnBnClickedCheckRecMousePos)
	ON_BN_CLICKED(IDC_CHECK_REC_MOUSE_WHEEL, &CDialogMacroRec::OnBnClickedCheckRecMouseWheel)
	ON_BN_CLICKED(IDC_CHECK_TIME, &CDialogMacroRec::OnBnClickedCheckTime)
	ON_BN_CLICKED(IDC_CHECK_MERGE, &CDialogMacroRec::OnBnClickedCheckMerge)
END_MESSAGE_MAP()


BOOL CDialogMacroRec::OnInitDialog()
{
	CDialog::OnInitDialog();

	SendDlgItemMessage (IDC_COMBO_KEY, CB_INITSTORAGE, 256, 100);
	SendDlgItemMessage (IDC_COMBO_KEY, WM_SETREDRAW, 0, 0);
	for (int i=0; i<255 && g_vk_list[i].vk != -1; ++i) {
		SendDlgItemMessage (IDC_COMBO_KEY, CB_INSERTSTRING, i, (LPARAM)GetVirtualKeyDesc(i));
	}
	SendDlgItemMessage (IDC_COMBO_KEY, CB_SETCURSEL, getVkIndex (g_ini.keyMacroRecord));
	SendDlgItemMessage (IDC_COMBO_KEY, WM_SETREDRAW, 1, 0);

	if (!_macro->name[0]) {
		sprintf (_macro->name, "Macro Rec. %d", ++_macro_name_ID);
		_macro->start_key	= VK_F2;
		_macro->stop_key	= VK_F3;
		_macro->repeat_cnt	= 1;

		// 제일 첫줄에 아무것도 아닌 항목을 삽입해 둔다.
		// 이유는, 선택한 항목 뒤에다가 새로운 항목을 추가할 수 있기때문에,
		// 이 NONE이 제일 처음에 없으면 첫줄에 새로운 항목을 추가할 수 없다.
		_macro->_item.resize(1);
		_macro->_item[0].type = sMacroItem::NONE;
	}

	for (unsigned int i=0; i<_macro->_item.size(); ++i) {
	   _listItems.InsertString (i, GetItemDescription (_macro->_item[i]));
	}
	_listItems.SetSel(0, TRUE);

	SetTextRecCount();

	CheckDlgButton (IDC_CHECK_REC_KEY,			(g_ini.recOptions.KEYBOARD_KEY_REC)		? BST_CHECKED : BST_UNCHECKED);	// Keyboard 입력 기록
	CheckDlgButton (IDC_CHECK_REC_MOUSE,		(g_ini.recOptions.MOUSE_BUTTON_REC)		? BST_CHECKED : BST_UNCHECKED);	// Mouse Button 입력 기록
	CheckDlgButton (IDC_CHECK_REC_MOUSE_POS,	(g_ini.recOptions.MOUSE_POSITION_REC)	? BST_CHECKED : BST_UNCHECKED);	// Mouse 위치 변화 기록
	CheckDlgButton (IDC_CHECK_REC_MOUSE_WHEEL,	(g_ini.recOptions.MOUSE_WHEEL_REC)		? BST_CHECKED : BST_UNCHECKED);	// Mouse 휠 변화 기록
	CheckDlgButton (IDC_CHECK_TIME,				(g_ini.recOptions.EVENT_DELAY)			? BST_CHECKED : BST_UNCHECKED);	// Keyboard나 Mouse 이벤트간 시간 간격 기록
	CheckDlgButton (IDC_CHECK_MERGE,			(g_ini.recOptions.MERGE_UP_DOWN)		? BST_CHECKED : BST_UNCHECKED);	// Button Up/Down 이벤트 합치기 허용

	SetDlgItemInt (IDC_EDIT_MOVE, g_ini.recMouseDistance);
	SetDlgItemDouble (IDC_EDIT_TIME, (double)g_ini.recEventTimeInterval/1000.);

	_macro_rec = false;
	_rec_time = 0;

	OnBnClickedCheckRecStat();

	SetTimer (1000, 33, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogMacroRec::OnCbnSelchangeComboKey()
{
	int index = SendDlgItemMessage (IDC_COMBO_KEY, CB_GETCURSEL, 0, 0);
	if (index != -1) {
		g_ini.keyMacroRecord = GetVirtualKeyCode(index);
	}
}

void CDialogMacroRec::SetTextRecCount()
{
	char text[256];

	sprintf (text, "%d개 항목이 기록됨.", _macro->_item.size()-1);

	SetDlgItemText (IDC_STATIC_REC_COUNT, text);
}

void CDialogMacroRec::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1000) {
		if (_listItems.GetCount() < (int)_macro->_item.size()) {
			for (unsigned int i=_listItems.GetCount(); i<_macro->_item.size(); ++i) {
			   _listItems.InsertString (i, GetItemDescription (_macro->_item[i]));
			}
			_listItems.SetCurSel(_macro->_item.size()-1);
			_listItems.ShowCaret ();

			SetTextRecCount();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CDialogMacroRec::OnKeyboardEvent (int vk, WPARAM wParam, KBDLLHOOKSTRUCT *keyStat)
{
	if (vk == g_ini.keyMacroRecord) {
		MacroRecStateChange (!_macro_rec);
	}

	if (_macro_rec) {
		if (g_ini.recOptions.KEYBOARD_KEY_REC) {	// 0x01 - Keyboard 입력 기록
			if      (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) AddKey (keyStat->vkCode, 1);
			else if (wParam == WM_KEYUP   || wParam == WM_SYSKEYUP)   AddKey (keyStat->vkCode, 2);
		}
	}
}

void CDialogMacroRec::OnMouseEvent (int vk, WPARAM wParam, MSLLHOOKSTRUCT *mouseStat)
{
	if (vk == g_ini.keyMacroRecord) {
		MacroRecStateChange (!_macro_rec);
	}

	if (_macro_rec) {
		int mx = mouseStat->pt.x;
		int my = mouseStat->pt.y;
		int flags = MOUSEEVENTF_MOVE;

		if (g_ini.recOptions.MOUSE_BUTTON_REC) {	// 0x02 - Mouse Button 입력 기록
			if (wParam == WM_LBUTTONDOWN)      AddMouse (mx, my, flags|MOUSEEVENTF_LEFTDOWN);
			else if (wParam == WM_LBUTTONUP)   AddMouse (mx, my, flags|MOUSEEVENTF_LEFTUP);
			else if (wParam == WM_RBUTTONDOWN) AddMouse (mx, my, flags|MOUSEEVENTF_RIGHTDOWN);
			else if (wParam == WM_RBUTTONUP)   AddMouse (mx, my, flags|MOUSEEVENTF_RIGHTUP);
			else if (wParam == WM_MBUTTONDOWN) AddMouse (mx, my, flags|MOUSEEVENTF_MIDDLEDOWN);
			else if (wParam == WM_MBUTTONUP)   AddMouse (mx, my, flags|MOUSEEVENTF_MIDDLEUP);
			else if (wParam == WM_XBUTTONDOWN) AddMouse (mx, my, MAKELONG(flags|MOUSEEVENTF_XDOWN, HIWORD(mouseStat->mouseData)));
			else if (wParam == WM_XBUTTONUP)   AddMouse (mx, my, MAKELONG(flags|MOUSEEVENTF_XUP,   HIWORD(mouseStat->mouseData)));
		}
		if (g_ini.recOptions.MOUSE_POSITION_REC) {	// 0x04 - Mouse 위치 변화 기록
			if (wParam == WM_MOUSEMOVE) { 
				if (MouseDistance(&mouseStat->pt) >= g_ini.recMouseDistance) {
					AddMouse (mx, my, flags);
				}
			}
		}
		if (g_ini.recOptions.MOUSE_WHEEL_REC) {	// 0x08 - Mouse 휠 변화 기록
			if (wParam == WM_MOUSEWHEEL) {
				flags = MOUSEEVENTF_WHEEL;
				AddMouse (mx, my, MAKELONG(flags, HIWORD(mouseStat->mouseData)));
			}
		}
	}
}

int CDialogMacroRec::MouseDistance (POINT *pt)
{
	if (_macro->_item.size() > 0) {
		sMacroItem &_item = _macro->_item[_macro->_item.size()-1];
		if (_item.type == sMacroItem::MOUSE && (_item.mouse.flags&MOUSEEVENTF_MOVE)) {
			int mx = _item.mouse.x;
			int my = _item.mouse.y;

			int dx = mx - pt->x;
			int dy = my - pt->y;

			return (int)sqrt((double)dx*dx + dy*dy);
		}
	}
	return 1000000;
}

void CDialogMacroRec::AddTimeDelayIf ()
{
	if (g_ini.recOptions.EVENT_DELAY) {	// 0x10 - Keyboard나 Mouse 이벤트간 시간 간격 기록
		DWORD cur_time = GetTickCount ();

		if ((int)(cur_time - _rec_time) >= g_ini.recEventTimeInterval) {
			AddTimeDelay (cur_time - _rec_time);
		}
		_rec_time = cur_time;
	}
}

bool CDialogMacroRec::LastIsSameKeyDown (int vk)
{
	if (_macro->_item.size() > 0) {
		sMacroItem &_item = _macro->_item[_macro->_item.size() - 1];

		if (_item.type == sMacroItem::KEY &&
			_item.key.vk == vk &&
			_item.key.flags == 1) return true;
	}
	return false;
}

void CDialogMacroRec::AddKey (long vk, long flags)
{
	AddTimeDelayIf ();

	if ((g_ini.recOptions.MERGE_UP_DOWN) && flags==2 && LastIsSameKeyDown(vk)) {	// 0x20 - Button Up/Down 이벤트 합치기 허용
		// 이전 키가 눌린 상태라서 누르고 떼기 상태로 바꾼다.
		_macro->_item[_macro->_item.size()-1].key.flags = 3;

		_listItems.DeleteString (_macro->_item.size()-1);
	}
	else {
		sMacroItem _item;

		_item.type = sMacroItem::KEY;
		_item.key.vk = vk;
		_item.key.flags = flags;

		_macro->_item.push_back (_item);
	}
}

bool CDialogMacroRec::LastIsSameMouseDown (long x, long y, long flags)
{
	const int MOUSEEVENTF_DOWN = MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_MIDDLEDOWN|MOUSEEVENTF_XDOWN;

	if (_macro->_item.size() > 0) {
		sMacroItem &_item = _macro->_item[_macro->_item.size() - 1];

		if (_item.type == sMacroItem::MOUSE) {
			if ((_item.mouse.flags&MOUSEEVENTF_LEFTDOWN && flags&MOUSEEVENTF_LEFTUP) ||
				(_item.mouse.flags&MOUSEEVENTF_RIGHTDOWN && flags&MOUSEEVENTF_RIGHTUP) ||
				(_item.mouse.flags&MOUSEEVENTF_MIDDLEDOWN && flags&MOUSEEVENTF_MIDDLEUP) ||
				(_item.mouse.flags&MOUSEEVENTF_XDOWN && flags&MOUSEEVENTF_XUP) ){

				if (_item.mouse.x == x && _item.mouse.y == y) return true;
			}
		}
	}
	return false;
}

void CDialogMacroRec::AddMouse (long mx, long my, long flags)
{
	AddTimeDelayIf ();

	const int MOUSEEVENTF_UP = MOUSEEVENTF_LEFTUP|MOUSEEVENTF_RIGHTUP|MOUSEEVENTF_MIDDLEUP|MOUSEEVENTF_XUP;

	if ((g_ini.recOptions.MERGE_UP_DOWN) && (flags&MOUSEEVENTF_UP) && LastIsSameMouseDown(mx, my, flags)) {	// 0x20 - Button Up/Down 이벤트 합치기 허용
		// 이전 마우스 버튼이 눌린 상태라서 클릭 상태로 바꾼다.
		_macro->_item[_macro->_item.size()-1].mouse.flags |= flags;

		_listItems.DeleteString (_macro->_item.size()-1);
	}
	else {
		sMacroItem _item;

		_item.type = sMacroItem::MOUSE;
		_item.mouse.flags = flags;
		_item.mouse.x = mx;
		_item.mouse.y = my;

		_macro->_item.push_back (_item);
	}
}

void CDialogMacroRec::AddTimeDelay (long delay)
{
	sMacroItem _item;

	_item.type = sMacroItem::DELAY;
	_item.time.delay = delay;

	_macro->_item.push_back (_item);
}

void CDialogMacroRec::EnableWindowItem(BOOL enable)
{
	GetDlgItem(IDC_COMBO_KEY)->EnableWindow (enable);
	GetDlgItem(IDC_CHECK_REC_KEY)->EnableWindow (enable);
	GetDlgItem(IDC_CHECK_REC_MOUSE)->EnableWindow (enable);
	GetDlgItem(IDC_CHECK_REC_MOUSE_POS)->EnableWindow (enable);
	GetDlgItem(IDC_CHECK_REC_MOUSE_WHEEL)->EnableWindow (enable);
	GetDlgItem(IDC_CHECK_TIME)->EnableWindow (enable);
	GetDlgItem(IDC_CHECK_MERGE)->EnableWindow (enable);
	GetDlgItem(IDC_EDIT_MOVE)->EnableWindow (enable);
	GetDlgItem(IDC_EDIT_TIME)->EnableWindow (enable);
}

double CDialogMacroRec::GetDlgItemDouble (int nIDDlgItem)
{
	char text[256];

	GetDlgItemText (nIDDlgItem, text, 255);
	text[255] = 0;

	return strtod (text, NULL);
}

void CDialogMacroRec::SetDlgItemDouble (int nIDDlgItem, double value)
{
	char text[256];

	sprintf (text, "%0.3f", value);
	SetDlgItemText (nIDDlgItem, text);
}

void CDialogMacroRec::MacroRecStateChange(bool rec)
{
	g_ini.recMouseDistance = GetDlgItemInt (IDC_EDIT_MOVE);
	g_ini.recEventTimeInterval = (int)(1000*GetDlgItemDouble (IDC_EDIT_TIME));

	if (rec) {
		CheckDlgButton (IDC_CHECK_REC_STAT, BST_CHECKED);
		SetDlgItemText (IDC_CHECK_REC_STAT, "매크로 기록 중");

		EnableWindowItem (FALSE);

		_macro_rec = true;
		_rec_time = GetTickCount ();
	}
	else {
		_macro_rec = false;

		CheckDlgButton (IDC_CHECK_REC_STAT, BST_UNCHECKED);
		SetDlgItemText (IDC_CHECK_REC_STAT, "기록 대기 중");

		EnableWindowItem (TRUE);
	}
}

void CDialogMacroRec::MacroRecOptionChanged()
{
	g_ini.recOptions.KEYBOARD_KEY_REC	= (IsDlgButtonChecked (IDC_CHECK_REC_KEY)			== BST_CHECKED) ? 1 : 0;	// Keyboard 입력 기록
	g_ini.recOptions.MOUSE_BUTTON_REC	= (IsDlgButtonChecked (IDC_CHECK_REC_MOUSE)			== BST_CHECKED) ? 1 : 0;	// Mouse Button 입력 기록
	g_ini.recOptions.MOUSE_POSITION_REC = (IsDlgButtonChecked (IDC_CHECK_REC_MOUSE_POS)		== BST_CHECKED) ? 1 : 0;	// Mouse 위치 변화 기록
	g_ini.recOptions.MOUSE_WHEEL_REC	= (IsDlgButtonChecked (IDC_CHECK_REC_MOUSE_WHEEL)	== BST_CHECKED) ? 1 : 0;	// Mouse 휠 변화 기록
	g_ini.recOptions.EVENT_DELAY		= (IsDlgButtonChecked (IDC_CHECK_TIME)				== BST_CHECKED) ? 1 : 0;	// Keyboard나 Mouse 이벤트간 시간 간격 기록
	g_ini.recOptions.MERGE_UP_DOWN		= (IsDlgButtonChecked (IDC_CHECK_MERGE)				== BST_CHECKED) ? 1 : 0;	// Button Up/Down 이벤트 합치기 허용
}

void CDialogMacroRec::OnBnClickedCheckRecStat()
{
	MacroRecStateChange (IsDlgButtonChecked (IDC_CHECK_REC_STAT) == BST_CHECKED);

	GetDlgItem (IDC_LIST_ITEMS)->SetFocus ();
}

void CDialogMacroRec::OnBnClickedCheckRecKey()
{
	MacroRecOptionChanged();
}

void CDialogMacroRec::OnBnClickedCheckRecMouse()
{
	MacroRecOptionChanged();
}

void CDialogMacroRec::OnBnClickedCheckRecMousePos()
{
	MacroRecOptionChanged();
}

void CDialogMacroRec::OnBnClickedCheckRecMouseWheel()
{
	MacroRecOptionChanged();
}

void CDialogMacroRec::OnBnClickedCheckTime()
{
	MacroRecOptionChanged();
}

void CDialogMacroRec::OnBnClickedCheckMerge()
{
	MacroRecOptionChanged();
}

void CDialogMacroRec::OnBnClickedOk()
{
	MacroRecStateChange (false);

	OnOK();
}

void CDialogMacroRec::OnBnClickedCancel()
{
	MacroRecStateChange (false);

	OnCancel();
}

