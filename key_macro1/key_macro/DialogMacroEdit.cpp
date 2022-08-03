#include "stdafx.h"
#include "key_macro.h"
#include "DialogMacroEdit.h"
#include "DialogDelay.h"
#include "DialogKeyboard.h"
#include "DialogMouse.h"
#include "virtual_key.h"
#include "key_hook.h"
#include "AppIni.h"
#include "Common.h"


extern const char *GetItemDescription (const sMacroItem &item);

// 프로그램이 실행되는 동안 대화상자 아이템에 
// 설정된 값을 저장하고 있는 변수들을 static으로 선언
int _macro_name_ID = 0;
static long _macro_start_key = VK_F2;
static long _macro_stop_key  = VK_F3;
static long _macro_repeat_cnt= 1;


IMPLEMENT_DYNAMIC(CDialogMacroEdit, CDialog)

CDialogMacroEdit::CDialogMacroEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMacroEdit::IDD, pParent)
{
}

CDialogMacroEdit::~CDialogMacroEdit()
{
}

void CDialogMacroEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ITEMS, _listItems);
}


BEGIN_MESSAGE_MAP(CDialogMacroEdit, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CDialogMacroEdit::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK_START_OPTION, &CDialogMacroEdit::OnBnClickedCheckStartOption)
	ON_BN_CLICKED(IDC_CHECK_STOP_OPTION, &CDialogMacroEdit::OnBnClickedCheckStopOption)
	ON_BN_CLICKED(IDC_BUTTON_ADD_KEY, &CDialogMacroEdit::OnBnClickedButtonAddKey)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MOUSE, &CDialogMacroEdit::OnBnClickedButtonAddMouse)
	ON_BN_CLICKED(IDC_BUTTON_ADD_DELAY, &CDialogMacroEdit::OnBnClickedButtonAddDelay)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CDialogMacroEdit::OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CDialogMacroEdit::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_UP, &CDialogMacroEdit::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &CDialogMacroEdit::OnBnClickedButtonDown)
	ON_LBN_DBLCLK(IDC_LIST_ITEMS, &CDialogMacroEdit::OnLbnDblclkListItems)
END_MESSAGE_MAP()


BOOL CDialogMacroEdit::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	if (!_macro->name[0]) {
		SetWindowText ("매크로 추가");
		sprintf (_macro->name, "Macro %d", ++_macro_name_ID);
		_macro->start_key	= _macro_start_key;
		_macro->stop_key	= _macro_stop_key;
		_macro->repeat_cnt	= _macro_repeat_cnt;

		// 제일 첫줄에 아무것도 아닌 항목을 삽입해 둔다.
		// 이유는, 선택한 항목 뒤에다가 새로운 항목을 추가할 수 있기때문에,
		// 이 NONE이 제일 처음에 없으면 첫줄에 새로운 항목을 추가할 수 없다.
		_macro->_item.resize(1);
		_macro->_item[0].type = sMacroItem::NONE;
	}
	else {
		SetWindowText ("매크로 편집");
	}

	SetDlgItemText (IDC_EDIT_MACRO_NAME, _macro->name);

	SendDlgItemMessage (IDC_COMBO_MACRO_START, CB_INITSTORAGE, 256, 100);
	SendDlgItemMessage (IDC_COMBO_MACRO_STOP,  CB_INITSTORAGE, 256, 100);

	SendDlgItemMessage (IDC_COMBO_MACRO_START, WM_SETREDRAW, 0, 0);
	SendDlgItemMessage (IDC_COMBO_MACRO_STOP,  WM_SETREDRAW, 0, 0);
	
	for (int i=0; i<255 && g_vk_list[i].vk != -1; ++i) {
		SendDlgItemMessage (IDC_COMBO_MACRO_START, CB_INSERTSTRING, i, (LPARAM)GetVirtualKeyDesc(i));
		SendDlgItemMessage (IDC_COMBO_MACRO_STOP,  CB_INSERTSTRING, i, (LPARAM)GetVirtualKeyDesc(i));
	}
	SendDlgItemMessage (IDC_COMBO_MACRO_START, CB_SETCURSEL, getVkIndex (_macro->start_key & 0xFF));
	SendDlgItemMessage (IDC_COMBO_MACRO_STOP,  CB_SETCURSEL, getVkIndex (_macro->stop_key  & 0xFF));

	SendDlgItemMessage (IDC_COMBO_MACRO_START, WM_SETREDRAW, 1, 0);
	SendDlgItemMessage (IDC_COMBO_MACRO_STOP,  WM_SETREDRAW, 1, 0);

	CheckDlgButton (IDC_CHECK_START_OPTION,	  (_macro->start_key & 0x10000) ? BST_UNCHECKED : BST_CHECKED);
	CheckDlgButton (IDC_CHECK_STOP_OPTION,    (_macro->stop_key  & 0x10000) ? BST_UNCHECKED : BST_CHECKED);

	SetDlgItemInt (IDC_EDIT_MACRO_REPEAT_COUNT, (int)_macro->repeat_cnt);

	OnBnClickedCheckStartOption();
	OnBnClickedCheckStopOption();

	_listItems.SetMacroItems (&_macro->_item);
	for (unsigned int i=0; i<_macro->_item.size(); ++i) {
	   _listItems.InsertString (i, GetItemDescription (_macro->_item[i]));
	}
	_listItems.SetSel (0, TRUE);

	SetTextRecCount();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogMacroEdit::SetTextRecCount()
{
	char text[256];

	sprintf (text, "%d개 항목이 기록됨.", _macro->_item.size()-1);

	SetDlgItemText (IDC_STATIC_REC_COUNT, text);
}

void CDialogMacroEdit::AddItem (int sel, sMacroItem &_item)
{
	_macro->_item.insert (_macro->_item.begin() + sel, _item);

	_listItems.InsertString (sel, GetItemDescription (_item));
}

void CDialogMacroEdit::EditItem (int sel, sMacroItem &_item)
{
	_macro->_item[sel] = _item;

	_listItems.DeleteString (sel);
	_listItems.InsertString (sel, GetItemDescription (_item));
	
	_listItems.SetSel (sel, TRUE);
}

void CDialogMacroEdit::OnBnClickedButtonAddKey()
{
	int sel = _listItems.GetCurSel ();

	// 만일 선택된 경우, 선택된 항목 뒤에다 추가하려고 1 증가
	if (0 <= sel) sel++; 
	else sel = _listItems.GetCount ();

	if (0 <= sel) {
		CDialogKeyboard dlg;

		if (dlg.DoModal () == IDOK){
			AddItem (sel, dlg._item);
			_listItems.SetSel (sel-1, FALSE);
			_listItems.SetSel (sel, TRUE);
		}
	}

	SetTextRecCount();
	_listItems.SetFocus ();
}

void CDialogMacroEdit::OnBnClickedButtonAddMouse()
{
	int sel = _listItems.GetCurSel ();

	// 만일 선택된 경우, 선택된 항목 뒤에다 추가하려고 1 증가
	if (0 <= sel) sel++; 
	else sel = _listItems.GetCount ();

	if (0 <= sel) {
		CDialogMouse dlg;

		if (dlg.DoModal () == IDOK) {
			AddItem (sel, dlg._item);
			_listItems.SetSel (sel-1, FALSE);
			_listItems.SetSel (sel, TRUE);
		}
	}

	SetTextRecCount();
	_listItems.SetFocus ();
}

void CDialogMacroEdit::OnBnClickedButtonAddDelay()
{
	int sel = _listItems.GetCurSel ();

	// 만일 선택된 경우, 선택된 항목 뒤에다 추가하려고 1 증가
	if ( 0 <= sel) sel++; 
	else sel = _listItems.GetCount ();

	if (0 <= sel) {
		CDialogDelay dlg;

		if (dlg.DoModal () == IDOK) {
			AddItem (sel, dlg._item);
			_listItems.SetSel (sel-1, FALSE);
			_listItems.SetSel (sel, TRUE);
		}
	}

	SetTextRecCount();
	_listItems.SetFocus ();
}

void CDialogMacroEdit::OnBnClickedButtonEdit()
{
	int sel = _listItems.GetCurSel ();
	if (1 <= sel && _listItems.GetSel (sel)) { // 처음 아이템은 편집하지 못하도록!
		switch (_macro->_item[sel].type) {
		case sMacroItem::KEY: {
			CDialogKeyboard dlg;
			dlg._item = _macro->_item[sel];

			if (dlg.DoModal () == IDOK) {
				EditItem (sel, dlg._item);
			}
			break; }
		case sMacroItem::MOUSE: {
			CDialogMouse dlg;
			dlg._item = _macro->_item[sel];

			if (dlg.DoModal () == IDOK) {
				EditItem (sel, dlg._item);
			}
			break; }
		case sMacroItem::DELAY: {
			CDialogDelay dlg;
			dlg._item = _macro->_item[sel];

			if (dlg.DoModal () == IDOK) {
				EditItem (sel, dlg._item);
			}
			break; }
		}
	}
}

void CDialogMacroEdit::OnBnClickedButtonDelete()
{
	int count = _listItems.GetSelCount();
	CArray<int,int> arr;

	arr.SetSize(count);
	_listItems.GetSelItems(count, arr.GetData()); 

	// 지울 때는 마지막 선택 항목부터 거꾸로 지운다.
	for (int i=arr.GetSize()-1; i>=0; i--) {
		int sel = arr.GetAt(i);
		if (1 <= sel) { // 처음 아이템은 지우지 못하도록!
			_listItems.DeleteString (sel);

			_macro->_item.erase (_macro->_item.begin() + sel);
		}
	}

	SetTextRecCount();
	_listItems.SetFocus ();
}

void CDialogMacroEdit::OnBnClickedButtonUp()
{
	int count = _listItems.GetSelCount();
	CArray<int,int> arr;

	arr.SetSize(count);
	_listItems.GetSelItems(count, arr.GetData()); 

	// 세 번째 아이템부터 위로 올릴 수 있다.
	if (arr.GetSize() == 0) return;
	if (arr.GetAt(0) < 2) return;

	for (int i=0; i<arr.GetSize(); i++) {
		int sel = arr.GetAt(i);

		// sel-1과 sel item을 스왑 한다.
		int ss = _listItems.GetSel (sel-1);
		_listItems.DeleteString (sel);
		_listItems.InsertString (sel-1, GetItemDescription (_macro->_item[sel]));
		_listItems.SetSel (sel-1, TRUE);
		if (ss) _listItems.SetSel (sel, TRUE);

		std::swap (_macro->_item[sel], _macro->_item[sel-1]);
	}

	_listItems.SetFocus ();
}

void CDialogMacroEdit::OnBnClickedButtonDown()
{
	int count = _listItems.GetSelCount();
	CArray<int,int> arr;

	arr.SetSize(count);
	_listItems.GetSelItems(count, arr.GetData()); 

	// 처음 아이템과 마지막 아이템은 아래로 내릴 수 없다.
	if (arr.GetSize() == 0) return;
	if (arr.GetAt(0) == 0) return;
	if (arr.GetAt(arr.GetSize()-1) >= _listItems.GetCount ()-1) return;

	for (int i=arr.GetSize()-1; i>=0; i--) {
		int sel = arr.GetAt(i);

		// sel+1과 sel item을 스왑 한다.
		int ss = _listItems.GetSel (sel+1);
	   _listItems.DeleteString (sel);
	   _listItems.InsertString (sel+1, GetItemDescription (_macro->_item[sel]));
	   _listItems.SetSel (sel+1, TRUE);
		if (ss) _listItems.SetSel (sel, TRUE);

	   std::swap (_macro->_item[sel], _macro->_item[sel+1]);
	}

	_listItems.SetFocus ();
}

void CDialogMacroEdit::OnLbnDblclkListItems()
{
	OnBnClickedButtonEdit();
}

void CDialogMacroEdit::OnBnClickedCheckStartOption()
{
	if (IsDlgButtonChecked (IDC_CHECK_START_OPTION) == BST_CHECKED) {
		SetDlgItemText (IDC_CHECK_START_OPTION, "누를 때");
		_macro->start_key &= 0x0FFFF;
	}
	else {
		SetDlgItemText (IDC_CHECK_START_OPTION, "뗄 때");
		_macro->start_key |= 0x10000;
	}
}

void CDialogMacroEdit::OnBnClickedCheckStopOption()
{
	if (IsDlgButtonChecked (IDC_CHECK_STOP_OPTION) == BST_CHECKED) {
		SetDlgItemText (IDC_CHECK_STOP_OPTION, "누를 때");
		_macro->stop_key &= 0x0FFFF;
	}
	else {
		SetDlgItemText (IDC_CHECK_STOP_OPTION, "뗄 때");
		_macro->stop_key |= 0x10000;
	}
}

void CDialogMacroEdit::ReadStartStopVk()
{
	int index = SendDlgItemMessage (IDC_COMBO_MACRO_START, CB_GETCURSEL, 0, 0);
	if (index != -1) {
		_macro_start_key = GetVirtualKeyCode(index);
	}
	if (IsDlgButtonChecked (IDC_CHECK_START_OPTION) == BST_UNCHECKED) {
		_macro_start_key |= 0x10000;
	}

	index = SendDlgItemMessage (IDC_COMBO_MACRO_STOP, CB_GETCURSEL, 0, 0);
	if (index != -1) {
		_macro_stop_key = GetVirtualKeyCode(index);
	}
	if (IsDlgButtonChecked (IDC_CHECK_STOP_OPTION) == BST_UNCHECKED) {
		_macro_stop_key |= 0x10000;
	}
}

void CDialogMacroEdit::OnBnClickedOk()
{
	GetDlgItemText (IDC_EDIT_MACRO_NAME, _macro->name, 255);
	_macro->name[255] = 0;

	_macro->repeat_cnt = BOUND((long)GetDlgItemInt (IDC_EDIT_MACRO_REPEAT_COUNT), 0L, 1000000L);

	int index = SendDlgItemMessage (IDC_COMBO_MACRO_START, CB_GETCURSEL, 0, 0);
	if (index != -1) {
		_macro->start_key = GetVirtualKeyCode(index);
	}
	if (IsDlgButtonChecked (IDC_CHECK_START_OPTION) == BST_UNCHECKED) {
		_macro->start_key |= 0x10000;
	}

	index = SendDlgItemMessage (IDC_COMBO_MACRO_STOP, CB_GETCURSEL, 0, 0);
	if (index != -1) {
		_macro->stop_key = GetVirtualKeyCode(index);
	}
	if (IsDlgButtonChecked (IDC_CHECK_STOP_OPTION) == BST_UNCHECKED) {
		_macro->stop_key |= 0x10000;
	}

	_macro_repeat_cnt	= _macro->repeat_cnt;
	_macro_start_key	= _macro->start_key;
	_macro_stop_key		= _macro->stop_key;

	if (!_macro->name[0]) {
		AfxMessageBox ("매크로 이름이 지정되지 않았습니다. 이름을 입력하시기 바랍니다.");
	}
	else {
		OnOK();
	}
}

void CDialogMacroEdit::EnableWindowItem(BOOL enable)
{
	GetDlgItem(IDC_EDIT_MACRO_NAME)->EnableWindow (enable);

	GetDlgItem(IDC_COMBO_MACRO_START) ->EnableWindow (enable);
	GetDlgItem(IDC_COMBO_MACRO_STOP)  ->EnableWindow (enable);
	GetDlgItem(IDC_CHECK_START_OPTION)->EnableWindow (enable);
	GetDlgItem(IDC_CHECK_STOP_OPTION) ->EnableWindow (enable);

	GetDlgItem(IDC_BUTTON_ADD_KEY)  ->EnableWindow (enable);
	GetDlgItem(IDC_BUTTON_ADD_MOUSE)->EnableWindow (enable);
	GetDlgItem(IDC_BUTTON_ADD_DELAY)->EnableWindow (enable);
	GetDlgItem(IDC_BUTTON_EDIT)     ->EnableWindow (enable);
	GetDlgItem(IDC_BUTTON_DELETE)   ->EnableWindow (enable);

	GetDlgItem(IDC_BUTTON_UP)  ->EnableWindow (enable);
	GetDlgItem(IDC_BUTTON_DOWN)->EnableWindow (enable);

	GetDlgItem(IDOK)    ->EnableWindow (enable);
	GetDlgItem(IDCANCEL)->EnableWindow (enable);
}

