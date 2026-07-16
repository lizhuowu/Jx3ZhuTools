#pragma once


// CCGAME_FISH 对话框

class CCGAME_FISH : public CDialogEx
{
	DECLARE_DYNAMIC(CCGAME_FISH)

public:
	CCGAME_FISH(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCGAME_FISH();

// 对话框数据
	enum { IDD = IDD_DIALOG_FISH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
