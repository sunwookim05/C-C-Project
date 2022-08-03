#pragma once
#include "macro_def.h"

class CDialogMouse : public CDialog
{
	DECLARE_DYNAMIC(CDialogMouse)

public:
	CDialogMouse(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogMouse();

	enum { IDD = IDD_DIALOG_ADD_MOUSE };

	sMacroItem _item;

	void OnKeyEvent (int vk);
	void OnMouseEvent (int x, int y);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
public:
	afx_msg void OnBnClickedCheckAbspos();
	afx_msg void OnBnClickedCheckWheel();
	afx_msg void OnCbnSelchangeComboKey();
};
