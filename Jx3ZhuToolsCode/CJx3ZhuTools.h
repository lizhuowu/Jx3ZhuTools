#pragma once
#include "afxwin.h"
#include "resource.h"

// CCJx3ZhuTools 对话框

class CCJx3ZhuTools : public CDialogEx
{
	DECLARE_DYNAMIC(CCJx3ZhuTools)

public:
	CCJx3ZhuTools(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCJx3ZhuTools();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CComboBox M_COMBOX_LUA;
	virtual BOOL OnInitDialog();
	void CCJx3ZhuTools::LoadLuaScript();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	void SubControl(int BaseAddr,int Level);
	void ShowDetails(int	BaseAddr);
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	afx_msg void OnBnClickedButton18();

	afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);//(此行为加入的）
//	virtual void OnSetFont(CFont* pFont);
//	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL DestroyWindow();
//	afx_msg void OnPaint();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
};
