// CGAME_FISH.cpp : 实现文件
//

#include "stdafx.h"
#include "Jx3ZhuToolsCode.h"
#include "CGAME_FISH.h"
#include "afxdialogex.h"


// CCGAME_FISH 对话框

IMPLEMENT_DYNAMIC(CCGAME_FISH, CDialogEx)

CCGAME_FISH::CCGAME_FISH(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCGAME_FISH::IDD, pParent)
{

}

CCGAME_FISH::~CCGAME_FISH()
{
}

void CCGAME_FISH::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCGAME_FISH, CDialogEx)
END_MESSAGE_MAP()


// CCGAME_FISH 消息处理程序


BOOL CCGAME_FISH::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;
}
