// Jx3ZhuToolsCode.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Jx3ZhuToolsCode.h"
#include "CJx3ZhuTools.h"
#include "CGAME_MAIN.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CJx3ZhuToolsCodeApp

BEGIN_MESSAGE_MAP(CJx3ZhuToolsCodeApp, CWinApp)
END_MESSAGE_MAP()



// CJx3ZhuToolsCodeApp 构造

CJx3ZhuToolsCodeApp::CJx3ZhuToolsCodeApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CJx3ZhuToolsCodeApp 对象

CJx3ZhuToolsCodeApp theApp;
CCJx3ZhuTools *_CCJx3ZhuTools;
CCGAME_MAIN *_CCGAME_MAIN;

// CJx3ZhuToolsCodeApp 初始化
DWORD WINAPI ThreadProc (PVOID pParam)
{
	_CCJx3ZhuTools = new CCJx3ZhuTools;
	_CCJx3ZhuTools->DoModal();
	delete _CCJx3ZhuTools;
	FreeLibraryAndExitThread(theApp.m_hInstance,1);
	return TRUE;
}

DWORD WINAPI ThreadProcGame (PVOID pParam)
{
	_CCGAME_MAIN = new CCGAME_MAIN;
	_CCGAME_MAIN->DoModal();
	delete _CCJx3ZhuTools;
	FreeLibraryAndExitThread(theApp.m_hInstance,1);
	return TRUE;
}
BOOL CJx3ZhuToolsCodeApp::InitInstance()
{
	CWinApp::InitInstance();

	//初始化LUA信息
	//_HOOK.HOOKCall();
	//注册热键，注册游戏窗口的热键
	//http://blog.csdn.net/whatday/article/details/8001966

	//::CreateThread(NULL,0,ThreadProc,NULL,0,0);
	::CreateThread(NULL,0,ThreadProcGame,NULL,0,0);
	//HOOK 轻功
	//_CCCommon.HOOK_DODGE_1();
	//_CCCommon.HOOK_DODGE_2();

	//开启Socket通讯
	_CCSocketCmd.InitSocketAll();
	return TRUE;
}
int CJx3ZhuToolsCodeApp::ExitInstance()
{
	SetWindowLong(g_hGameHandle,GWL_WNDPROC,(LONG)lwndProc);
	return CWinApp::ExitInstance();
}
