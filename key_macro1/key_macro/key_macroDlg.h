#pragma once
#include "afxwin.h"
#include "HyperLink.h"

class Ckey_macroDlg : public CDialog
{
public:
	Ckey_macroDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	~Ckey_macroDlg();

	enum { IDD = IDD_KEY_MACRO_DIALOG };

	void OnKeyMouseEvent (int vk, bool key);

private:
	DWORD _tp;
	
	void DlgInScreen ();
	void SetTextRecCount();
	void EnableDlgItem(BOOL enable);
	double GetDlgItemDouble (int nIDDlgItem);
	void SetDlgItemDouble (int nIDDlgItem, double value);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

	HICON m_hIcon;
	CListBox _listMacros;
	CListBox _listMacros2;
	CHyperLink	_staticHomepage;

	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeComboKey();
	afx_msg void OnBnClickedRadioRun();
	afx_msg void OnBnClickedRadioEdit();
	afx_msg void OnBnClickedButtonAddMacro();
	afx_msg void OnBnClickedButtonDeleteMacro();
	afx_msg void OnBnClickedButtonCopyMacro();
	afx_msg void OnBnClickedButtonEditMacro();
	afx_msg void OnBnClickedButtonMacroFile();
	afx_msg void OnBnClickedButtonRecMacro();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnLbnDblclkListMacros();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonQuit();
};
