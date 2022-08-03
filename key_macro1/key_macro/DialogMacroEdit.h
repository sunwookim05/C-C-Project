#pragma once
#include "macro_def.h"
#include "ListBoxEx.h"

class CDialogMacroEdit : public CDialog
{
	DECLARE_DYNAMIC(CDialogMacroEdit)

public:
	CDialogMacroEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogMacroEdit();

	enum { IDD = IDD_DIALOG_MACRO_EDIT };

	sMacro *_macro;

private:
	DWORD _tp;

	void SetTextRecCount();
	void AddItem (int sel, sMacroItem &_item);
	void EditItem (int sel, sMacroItem &_item);
	void EnableWindowItem(BOOL enable);
	void ReadStartStopVk();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	CListBoxEx _listItems;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheckStartOption();
	afx_msg void OnBnClickedCheckStopOption();
	afx_msg void OnBnClickedButtonAddKey();
	afx_msg void OnBnClickedButtonAddMouse();
	afx_msg void OnBnClickedButtonAddDelay();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnLbnDblclkListItems();
};
