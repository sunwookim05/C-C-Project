#include "stdafx.h"
#include "key_macro.h"
#include "key_macroDlg.h"
#include "DialogMacroEdit.h"
#include "DialogMacroRec.h"
#include "macro_def.h"
#include "key_hook.h"
#include "virtual_key.h"
#include "AppIni.h"
#include "common.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static bool _macro_changed = false;
Ckey_macroDlg *g_macroDlg = NULL;


// Ckey_macroDlg ��ȭ ����
Ckey_macroDlg::Ckey_macroDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Ckey_macroDlg::IDD, pParent)
{
	_tp = 0;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	g_macroDlg = this;
}

Ckey_macroDlg::~Ckey_macroDlg()
{
	g_macroDlg = NULL;
}

void Ckey_macroDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MACROS, _listMacros);
	DDX_Control(pDX, IDC_LIST_MACROS2, _listMacros2);
	DDX_Control(pDX, IDC_STATIC_HOMEPAGE, _staticHomepage);
}

BEGIN_MESSAGE_MAP(Ckey_macroDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &Ckey_macroDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Ckey_macroDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_RADIO_MACRO_RUN, &Ckey_macroDlg::OnBnClickedRadioRun)
	ON_BN_CLICKED(IDC_RADIO_MACRO_EDIT, &Ckey_macroDlg::OnBnClickedRadioEdit)
	ON_BN_CLICKED(IDC_BUTTON_ADD_MACRO, &Ckey_macroDlg::OnBnClickedButtonAddMacro)
	ON_BN_CLICKED(IDC_BUTTON_COPY_MACRO, &Ckey_macroDlg::OnBnClickedButtonCopyMacro)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_MACRO, &Ckey_macroDlg::OnBnClickedButtonDeleteMacro)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_MACRO, &Ckey_macroDlg::OnBnClickedButtonEditMacro)
	ON_BN_CLICKED(IDC_BUTTON_MACRO_FILE, &Ckey_macroDlg::OnBnClickedButtonMacroFile)
	ON_BN_CLICKED(IDC_BUTTON_REC_MACRO, &Ckey_macroDlg::OnBnClickedButtonRecMacro)
	ON_BN_CLICKED(IDC_BUTTON_UP, &Ckey_macroDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &Ckey_macroDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &Ckey_macroDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &Ckey_macroDlg::OnBnClickedButtonQuit)
	ON_LBN_DBLCLK(IDC_LIST_MACROS, &Ckey_macroDlg::OnLbnDblclkListMacros)
	ON_CBN_SELCHANGE(IDC_COMBO_KEY, &Ckey_macroDlg::OnCbnSelchangeComboKey)
END_MESSAGE_MAP()


void Ckey_macroDlg::DlgInScreen ()
{
	// ���� �����찡 ���۵� ��, ȭ���� ��� ������ ȭ�� ������ �ű��.
	RECT rect;
	GetWindowRect (&rect);

	int cxscreen = GetSystemMetrics(SM_CXSCREEN) - (rect.right - rect.left) - 1;
	int cyscreen = GetSystemMetrics(SM_CYSCREEN) - (rect.bottom - rect.top) - 1;

	if (g_ini.windowSX < 0) g_ini.windowSX = 0;
	if (g_ini.windowSX > cxscreen) g_ini.windowSX = cxscreen;

	if (g_ini.windowSY < 0) g_ini.windowSY = 0;
	if (g_ini.windowSY > cyscreen) g_ini.windowSY = cyscreen;
}

// Ckey_macroDlg �޽��� ó����
BOOL Ckey_macroDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowText (g_ini.macroProgramTitle);

	// Ÿ��Ʋ ��(ĸ�ǹ�)���� �����ư�� ��Ȱ��ȭ
	CMenu *pMenu = GetSystemMenu(FALSE);
	pMenu->RemoveMenu(SC_CLOSE, MF_BYCOMMAND);

	// �������� ��ġ�� �����Ѵ�.
	SetWindowPos (NULL, g_ini.windowSX, g_ini.windowSY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	DlgInScreen ();

	SendDlgItemMessage (IDC_COMBO_KEY, CB_INITSTORAGE, 256, 100);
	SendDlgItemMessage (IDC_COMBO_KEY, WM_SETREDRAW, 0, 0);
	for (int i=0; i<255 && g_vk_list[i].vk != -1; ++i) {
		SendDlgItemMessage (IDC_COMBO_KEY, CB_INSERTSTRING, i, (LPARAM)GetVirtualKeyDesc(i));
	}
	SendDlgItemMessage (IDC_COMBO_KEY, CB_SETCURSEL, getVkIndex (g_ini.keyMacroRun));
	SendDlgItemMessage (IDC_COMBO_KEY, WM_SETREDRAW, 1, 0);

	// ���Ϸκ��� ��ũ�θ� �о����
	SetDlgItemText (IDC_EDIT_MACRO_FILE, g_ini.macroFileName);

	// ��ũ�ΰ� ó������ ���� ���°� �ǵ��� ���� ��ư ����
	CheckDlgButton (IDC_RADIO_MACRO_RUN,   BST_UNCHECKED);
	CheckDlgButton (IDC_RADIO_MACRO_EDIT,  BST_CHECKED);

	// ��ũ�� ���� �ɼ� 
	if (g_ini.eventDelay < 1) g_ini.eventDelay = 1;
	SetDlgItemDouble (IDC_EDIT_EVENT_MIN_DELAY, (double)g_ini.eventDelay/1000.);

	// ���Ͽ��� ��ũ�θ� �ҷ��� ����Ʈ ��Ʈ�ѿ� ǥ���Ѵ�.
	LoadMacros (g_ini.macroFileName);

	_listMacros.ResetContent();
	for (unsigned int i=0; i<g_macros.size(); ++i) {
		_listMacros.InsertString (i, g_macros[i].name);
	}
	if (0 < g_macros.size()) {
		_listMacros.SetCurSel (0);
	}

	SetTextRecCount();

	// ���� ������ Ȩ������ �����۸�ũ ǥ��
	SetDlgItemText (IDC_STATIC_VERSION, GetVersionInfo(NULL, "ProductVersion"));

	_staticHomepage.SetURL("http://blog.daum.net/pg365/236");
	_staticHomepage.SetToolTipText("Ű����/���콺 ��ũ�� ���α׷� V1 (���� ����)");
	_staticHomepage.SetLinkCursor(::LoadCursor(0, MAKEINTRESOURCE(IDC_HAND)));

	// Ű����/���콺 �̺�Ʈ �� ��ġ
	InstallHook ();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void Ckey_macroDlg::OnPaint()
{
	if (IsIconic()) {
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else {
		CDialog::OnPaint();
	}
}

HCURSOR Ckey_macroDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void Ckey_macroDlg::OnDestroy()
{
	UninstallHook ();

	// ���� ���࿡ ��ũ�� ���α׷��� ��ġ�� �����ϱ� ���� ���� ��ġ�� ������ �д�.
	RECT rectWnd;
	GetWindowRect (&rectWnd);
	g_ini.windowSX = rectWnd.left;
	g_ini.windowSY = rectWnd.top;

	CDialog::OnDestroy();
}

void Ckey_macroDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1000) {
		for (unsigned int i=0; i<g_macros.size(); ++i) {
			_listMacros2.SetSel (i, g_macros[i].is_running());
		}
	}
	else if (nIDEvent == 1001) {
		DWORD t = GetTickCount ();
		AllMacroStep (t - _tp);
		_tp = t;
	}

	CDialog::OnTimer(nIDEvent);
}

void Ckey_macroDlg::OnKeyMouseEvent (int vk, bool key)
{
	if (vk == g_ini.keyMacroRun) {
		if (IsDlgButtonChecked (IDC_RADIO_MACRO_EDIT)) {
			CheckDlgButton (IDC_RADIO_MACRO_RUN, BST_CHECKED);
			CheckDlgButton (IDC_RADIO_MACRO_EDIT, BST_UNCHECKED);

			OnBnClickedRadioRun();
		}
		else if (IsDlgButtonChecked (IDC_RADIO_MACRO_RUN)) {
			CheckDlgButton (IDC_RADIO_MACRO_RUN, BST_UNCHECKED);
			CheckDlgButton (IDC_RADIO_MACRO_EDIT, BST_CHECKED);

			OnBnClickedRadioEdit();
		}
	}
	else {
		MacroStartStop (vk);
	}
}

void Ckey_macroDlg::OnBnClickedButtonMacroFile()
{
	if (_macro_changed) {
		int ret = AfxMessageBox ("��ũ�ΰ� ����Ǿ����ϴ�. �����ұ��?", MB_YESNO|MB_ICONQUESTION);
		if (ret == IDYES) {
			OnBnClickedButtonSave ();
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	char szFilter[] = "Macro file (*.m)|*.m|All Files(*.*)|*.*||";
	CFileDialog dlg(TRUE, NULL, g_ini.macroFileName, OFN_HIDEREADONLY, szFilter);
	
	if(IDOK == dlg.DoModal()) {
		char curPath[MAX_PATH+1] = "";
		GetCurrentDirectory (MAX_PATH, curPath);
		curPath[MAX_PATH] = '\0';

		CString fileNameNew = "";

		if (strnicmp(curPath, (LPCSTR)dlg.GetPathName (), strlen(curPath)) == 0) {
			fileNameNew = (LPCSTR)dlg.GetPathName () + strlen(curPath) + 1;
		}
		else {
			fileNameNew = dlg.GetPathName();
		}

		if (dlg.GetFileExt ().GetLength () == 0) {
			fileNameNew += ".m";
		}

		LoadMacros ((LPCSTR)fileNameNew);

		_listMacros.ResetContent();
		for (unsigned int i=0; i<g_macros.size(); ++i) {
			_listMacros.InsertString (i, g_macros[i].name);
		}
		_listMacros.SetCurSel(0);

		strncpy (g_ini.macroFileName, (LPCSTR)fileNameNew, MAX_PATH);
		g_ini.macroFileName[MAX_PATH] = '\0';
		SetDlgItemText (IDC_EDIT_MACRO_FILE, g_ini.macroFileName);
	}
}

void Ckey_macroDlg::EnableDlgItem(BOOL enable)
{
	GetDlgItem (IDC_COMBO_KEY)->EnableWindow (enable);
	GetDlgItem (IDC_BUTTON_REC_MACRO)->EnableWindow (enable);
	GetDlgItem (IDC_BUTTON_ADD_MACRO)->EnableWindow (enable);
	GetDlgItem (IDC_BUTTON_EDIT_MACRO)->EnableWindow (enable);
	GetDlgItem (IDC_BUTTON_COPY_MACRO)->EnableWindow (enable);
	GetDlgItem (IDC_BUTTON_DELETE_MACRO)->EnableWindow (enable);
	GetDlgItem (IDC_BUTTON_MACRO_FILE)->EnableWindow (enable);
	GetDlgItem (IDC_EDIT_EVENT_MIN_DELAY)->EnableWindow (enable);
	GetDlgItem (IDC_BUTTON_UP)->EnableWindow (enable);
	GetDlgItem (IDC_BUTTON_DOWN)->EnableWindow (enable);
}

double Ckey_macroDlg::GetDlgItemDouble (int nIDDlgItem)
{
	char text[256];

	GetDlgItemText (nIDDlgItem, text, 255);
	text[255] = 0;

	return strtod (text, NULL);
}

void Ckey_macroDlg::SetDlgItemDouble (int nIDDlgItem, double value)
{
	char text[256];

	sprintf (text, "%0.3f", value);
	SetDlgItemText (nIDDlgItem, text);
}

void Ckey_macroDlg::OnBnClickedOk()
{
	// Alt+F4, Esc Ű�� ���� ������ ����Ǵ� �� ����

	// OnOK();
}

void Ckey_macroDlg::OnBnClickedCancel()
{
	// Alt+F4, Esc Ű�� ���� ������ ����Ǵ� �� ����

	// OnCancel();
}

void Ckey_macroDlg::OnBnClickedRadioRun()
{
	if (g_macros.size() == 0) {
		AfxMessageBox ("��ϵ� ��ũ�ΰ� �����ϴ�.");
		return;
	}

	if (IsDlgButtonChecked (IDC_RADIO_MACRO_RUN)) {
		MacroInit ();
		EnableDlgItem (FALSE);
		
		_listMacros2.ResetContent();

		char buff[256+1];
		for (unsigned int i=0; i<g_macros.size(); ++i) {
			_snprintf (buff, 256, "%s (%s%s / %s%s)", 
				g_macros[i].name, 
				GetVirtualKeyNameFromVK (g_macros[i].start_key & 0xFF),  
				(g_macros[i].start_key & 0x10000) ? "��" : "����",
				GetVirtualKeyNameFromVK (g_macros[i].stop_key  & 0xFF),
				(g_macros[i].stop_key  & 0x10000) ? "��" : "����");
			buff[256] = '\0';

			_listMacros2.InsertString (i, buff);
		}

		_listMacros.ShowWindow (SW_HIDE);
		_listMacros2.ShowWindow (SW_SHOW);

		g_ini.eventDelay = BOUND ((int)(1000*GetDlgItemDouble (IDC_EDIT_EVENT_MIN_DELAY)), 33, 100000);

		// ��ũ�θ� �����ϵ��� Ÿ�̸� ����
		_tp = GetTickCount ();
		SetTimer (1001, g_ini.eventDelay, NULL);	// ��ũ�θ� �����ϱ� ���� Ÿ�̸�
		SetTimer (1000, 33, NULL);					// ����Ǵ� ��ũ�θ� ����Ʈ �ڽ��� ǥ���ϱ� ���� Ÿ�̸�
	}
}

void Ckey_macroDlg::OnBnClickedRadioEdit()
{
	if (IsDlgButtonChecked (IDC_RADIO_MACRO_EDIT)) {
		MacroTerm ();

		EnableDlgItem (TRUE);

		_listMacros.ShowWindow (SW_SHOW);
		_listMacros2.ShowWindow (SW_HIDE);

		KillTimer (1001);
		KillTimer (1000);
	}
}

void Ckey_macroDlg::OnCbnSelchangeComboKey()
{
	int index = SendDlgItemMessage (IDC_COMBO_KEY, CB_GETCURSEL, 0, 0);
	if (index != -1) {
		g_ini.keyMacroRun = GetVirtualKeyCode(index);
	}
}

void Ckey_macroDlg::SetTextRecCount()
{
	char text[256];

	sprintf (text, "%d�� ��ũ�ΰ� ��ϵ�.", g_macros.size());

	SetDlgItemText (IDC_STATIC_REC_COUNT, text);
}

void Ckey_macroDlg::OnBnClickedButtonAddMacro()
{
	CDialogMacroEdit dlg;

	// �߰��� ��ũ�θ� temp�� ����� �߰�(����) ��ȭ���ڿ� �Ѱ��ش�.
	// �߰� ��ȭ���ڿ��� OK ��ư�� ������ g_macros�� ������ ��ũ��(temp)�� �߰��Ѵ�.
	sMacro temp;
	dlg._macro = &temp;

	if (dlg.DoModal () == IDOK) {
		int count = _listMacros.GetCount ();

		_listMacros.InsertString (count, temp.name);
		_listMacros.SetCurSel (count);

		g_macros.push_back (temp);
		_macro_changed = true;
	}

	SetTextRecCount();
}

void Ckey_macroDlg::OnBnClickedButtonEditMacro()
{
	int sel = _listMacros.GetCurSel ();
	if (sel < 0) return;

	CDialogMacroEdit dlg;

	// ��ũ�θ� ������ ����, �����ϰ��� �ϴ� ��ũ�θ� temp�� �����Ͽ� ���� ��ȭ���ڷ� �Ѱ��ش�.
	// ���� ��ȭ���ڿ��� OK ��ư�� ������ ������ ��ũ��(temp)�� g_macros�� ��ϵ� ��ũ�ο� �����.
	sMacro temp = g_macros[sel];
	dlg._macro = &temp;

	if (dlg.DoModal () == IDOK) {
		_listMacros.DeleteString (sel);
		_listMacros.InsertString (sel, temp.name);
		_listMacros.SetCurSel (sel);

		g_macros[sel] = *dlg._macro;
		_macro_changed = true;
	}
}

void Ckey_macroDlg::OnBnClickedButtonRecMacro()
{
	CDialogMacroRec dlg;

	// ���� temp ��ũ�θ� �����, ����� ��ũ�θ� ����Ѵ�.
	// ��� ��ȭ���ڿ��� OK�� ������ temp�� ��ϵ� ��ũ�θ� g_macros�� �߰��Ѵ�.
	sMacro temp;
	dlg._macro = &temp;

	if (dlg.DoModal () == IDOK) {
		int count = _listMacros.GetCount ();

		_listMacros.InsertString (count, temp.name);
		_listMacros.SetCurSel (count);

		g_macros.push_back (temp);
		_macro_changed = true;
	}

	SetTextRecCount();
}

void Ckey_macroDlg::OnBnClickedButtonCopyMacro()
{
	int sel = _listMacros.GetCurSel ();
	if (sel < 0) return;

	int count = _listMacros.GetCount ();
	sMacro &macro = g_macros[sel];

	_listMacros.InsertString (count, macro.name);
	_listMacros.SetCurSel (count);

	g_macros.push_back (macro);
	_macro_changed = true;

	SetTextRecCount();
}

void Ckey_macroDlg::OnBnClickedButtonDeleteMacro()
{
	int sel = _listMacros.GetCurSel ();
	if (sel < 0) return;

	_listMacros.DeleteString (sel);
	_listMacros.SetCurSel (sel);

	g_macros.erase (g_macros.begin() + sel);
	_macro_changed = true;

	SetTextRecCount();
}

void Ckey_macroDlg::OnLbnDblclkListMacros()
{
	OnBnClickedButtonEditMacro();
}

void Ckey_macroDlg::OnBnClickedButtonUp()
{
	int sel = _listMacros.GetCurSel ();
	if (sel < 0) return;

	if (1 <= sel) {
	   _listMacros.DeleteString (sel);
	   _listMacros.InsertString (sel-1, g_macros[sel].name);
	   _listMacros.SetCurSel (sel-1);

	   std::swap (g_macros[sel], g_macros[sel-1]);
		_macro_changed = true;
	}
}

void Ckey_macroDlg::OnBnClickedButtonDown()
{
	int sel = _listMacros.GetCurSel ();
	if (sel < 0) return;

	if (sel < _listMacros.GetCount ()-1) { 
	   _listMacros.DeleteString (sel);
	   _listMacros.InsertString (sel+1, g_macros[sel].name);
	   _listMacros.SetCurSel (sel+1);

		std::swap (g_macros[sel], g_macros[sel+1]);
		_macro_changed = true;
	}
}

void Ckey_macroDlg::OnBnClickedButtonSave()
{
	// ��ũ�θ� ������ ���� �̸��� ��������, ��ũ�θ� �� ���� �̸����� �����Ѵ�.
	GetDlgItemText (IDC_EDIT_MACRO_FILE, g_ini.macroFileName, MAX_PATH);
	g_ini.macroFileName[MAX_PATH] = '\0';
	
	SaveMacro (g_ini.macroFileName);
	_macro_changed = false;
}


void Ckey_macroDlg::OnBnClickedButtonQuit()
{
	// �������� INI���Ͽ� �����ϱ� ���� ���̾�α׿� ������ ���� �����´�.
	g_ini.eventDelay = BOUND ((int)(1000*GetDlgItemDouble (IDC_EDIT_EVENT_MIN_DELAY)), 33, 100000);

	// ��ũ�ΰ� ����Ǿ����� ���� ���θ� ����� �����Ѵ�.
	if (_macro_changed) {
		int ret = AfxMessageBox ("��ũ�ΰ� ����Ǿ����ϴ�. �����ұ��?", MB_YESNO|MB_ICONQUESTION);
		if (ret == IDYES) {
			OnBnClickedButtonSave ();
		}
	}

	// ���⼭ ����
	OnOK ();
}
