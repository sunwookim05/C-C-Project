#pragma once
#include "macro_def.h"

class CDialogDelay : public CDialog
{
	DECLARE_DYNAMIC(CDialogDelay)

public:
	CDialogDelay(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogDelay();

	enum { IDD = IDD_DIALOG_ADD_DELAY };

	sMacroItem _item;

private:
	double GetDlgItemDouble (int nIDDlgItem);
	void SetDlgItemDouble (int nIDDlgItem, double value);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
