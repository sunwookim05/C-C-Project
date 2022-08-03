#pragma once
#include "macro_def.h"

class CDialogMacroRec : public CDialog
{
	DECLARE_DYNAMIC(CDialogMacroRec)

public:
	CDialogMacroRec(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogMacroRec();

	enum { IDD = IDD_DIALOG_MACRO_REC };

	sMacro *_macro;

	void OnKeyboardEvent (int vk, WPARAM wParam, KBDLLHOOKSTRUCT *keyStat);
	void OnMouseEvent (int vk, WPARAM wParam, MSLLHOOKSTRUCT *mouseStat);

private:
	bool _macro_rec;
	DWORD _rec_time;

	void SetTextRecCount();

	void MacroRecStateChange (bool rec);
	void MacroRecOptionChanged ();

	void AddKey (long vk, long flags);
	void AddMouse (long x, long y, long flags);
	void AddTimeDelay (long delay);
	void AddTimeDelayIf ();

	void EnableWindowItem(BOOL enable);
	double GetDlgItemDouble (int nIDDlgItem);
	void SetDlgItemDouble (int nIDDlgItem, double value);

	void UpdateLastItem();
	int MouseDistance (POINT *pt);
	bool LastIsSameKeyDown (int vk);
	bool LastIsSameMouseDown (long x, long y, long flags);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CListBox _listItems;

	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeComboKey();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedCheckRecStat();
	afx_msg void OnBnClickedCheckRecKey();
	afx_msg void OnBnClickedCheckRecMouse();
	afx_msg void OnBnClickedCheckRecMousePos();
	afx_msg void OnBnClickedCheckRecMouseWheel();
	afx_msg void OnBnClickedCheckTime();
	afx_msg void OnBnClickedCheckMerge();
};
