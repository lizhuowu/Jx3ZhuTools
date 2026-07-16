// CGAME_TASK.cpp : 实现文件
//

#include "stdafx.h"
#include "Jx3ZhuToolsCode.h"
#include "CGAME_TASK.h"
#include "afxdialogex.h"


// CCGAME_TASK 对话框

IMPLEMENT_DYNAMIC(CCGAME_TASK, CDialogEx)

CCGAME_TASK::CCGAME_TASK(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCGAME_TASK::IDD, pParent)
{

}

CCGAME_TASK::~CCGAME_TASK()
{
}

void CCGAME_TASK::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCGAME_TASK, CDialogEx)
END_MESSAGE_MAP()


// CCGAME_TASK 消息处理程序

/*
 *初始化
 */
BOOL CCGAME_TASK::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
}
