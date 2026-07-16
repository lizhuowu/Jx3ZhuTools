#pragma once


// CCGAME_TASK 对话框

class CCGAME_TASK : public CDialogEx
{
	DECLARE_DYNAMIC(CCGAME_TASK)

public:
	CCGAME_TASK(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCGAME_TASK();

// 对话框数据
	enum { IDD = IDD_DIALOG_TASK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
