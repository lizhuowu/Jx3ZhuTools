#pragma once
#include "afxcmn.h"


// CCGAME_MAIN 对话框

class CCGAME_MAIN : public CDialogEx
{
	DECLARE_DYNAMIC(CCGAME_MAIN)

public:
	CCGAME_MAIN(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCGAME_MAIN();

// 对话框数据
	enum { IDD = IDD_DIALOG_GAME_TAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CTabCtrl tab_Main;
	afx_msg void OnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
};
