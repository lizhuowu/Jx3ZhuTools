
// Jx3ZhuToolsDlg.h : 头文件
//

#pragma once
#include "resource.h"
#include "ui_capture.h"

// CJx3ZhuToolsDlg 对话框
class CJx3ZhuToolsDlg : public CDialogEx
{
// 构造
public:
	CJx3ZhuToolsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JX3ZHUTOOLS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	// 安装全局钩子（可以在 OnInitDialog 中调用）
	void StartGlobalMouseHook();
	// 卸载钩子（在 OnCancel 或析构函数中调用）
	void StopGlobalMouseHook();
private:
	static HHOOK m_hMouseHook;
	static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);


public:
	// 辅助函数 1：获取真实的顶层窗口
	HWND GetRealTopWindow(HWND hWnd);
	// 辅助函数 2：绘制/擦除窗口高亮虚线框 (Spy++ 灵魂功能)
	void DrawWindowFrame(HWND hWnd, BOOL bDraw);
	void DrawHighlightRect(const RECT* pNewRect);

	HWND GetRealWindowUnderCursor(CPoint pt);
	void DrawXORFrame(HWND hWnd);

// 实现
protected:
	HICON		m_hIcon;

	ui_capture  ui_capture_;

	bool hideXspyWhenCapture_;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

//  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnSpyStart(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSpy(WPARAM wParam, LPARAM lParam);

};
