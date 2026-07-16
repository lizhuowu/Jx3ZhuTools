// CGAME_MAIN.cpp : 实现文件
//

#include "stdafx.h"
#include "Jx3ZhuToolsCode.h"
#include "CGAME_MAIN.h"
#include "afxdialogex.h"
#include "CGAME_TASK.h"
#include "CGAME_FISH.h"

// CCGAME_MAIN 对话框

IMPLEMENT_DYNAMIC(CCGAME_MAIN, CDialogEx)

CCGAME_MAIN::CCGAME_MAIN(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCGAME_MAIN::IDD, pParent)
{

}

CCGAME_MAIN::~CCGAME_MAIN()
{
}

void CCGAME_MAIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, tab_Main);
}


BEGIN_MESSAGE_MAP(CCGAME_MAIN, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CCGAME_MAIN::OnSelchangeTabMain)
END_MESSAGE_MAP()


// CCGAME_MAIN 消息处理程序
CCGAME_TASK _CCGAME_TASK;
CCGAME_FISH _CCGAME_FISH;

BOOL CCGAME_MAIN::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	tab_Main.InsertItem(1,"挂机");
	tab_Main.InsertItem(2,"钓鱼");
	//创建窗口
	_CCGAME_TASK.Create(IDD_DIALOG_TASK,0);
	_CCGAME_FISH.Create(IDD_DIALOG_FISH,0);

	//关联父窗体
	_CCGAME_TASK.SetParent(GetDlgItem(IDC_TAB_MAIN));
	_CCGAME_FISH.SetParent(GetDlgItem(IDC_TAB_MAIN));
	RECT r1;
	r1.left=3;
	r1.top=22;
	r1.bottom=390+22;
	r1.right=348;
	_CCGAME_TASK.MoveWindow(&r1);
	_CCGAME_FISH.MoveWindow(&r1);
	///始化显示
	_CCGAME_TASK.ShowWindow(SW_SHOW);
	return TRUE;
}

void CCGAME_MAIN::OnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	switch(tab_Main.GetCurSel())
	{
	case 0:{
		_CCGAME_TASK.ShowWindow(SW_SHOW);
		_CCGAME_FISH.ShowWindow(SW_HIDE);
		break;
		   }
	case 1:{
		_CCGAME_TASK.ShowWindow(SW_HIDE);
		_CCGAME_FISH.ShowWindow(SW_SHOW);
		break;
		   }
	}
	*pResult = 0;
}
