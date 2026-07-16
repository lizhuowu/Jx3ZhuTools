#pragma once
//#include <Windows.h>
#include <vector>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <WinUser.h>
#include "CCall.h"
#include "CJx3ZhuTools.h"

//HHOOK hMsgHook;
BOOL CALLBACK EnumWindowsProc(_In_  HWND hwnd, _In_  LPARAM lParam);
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

///////更改信息操作功能/////

class CCGameWndProc
{
private:
	
	CCGameWndProc(void)
	{
		//数据的初始化
		SetGameWndProc();
	}
public:
	static CCGameWndProc *Instantialize()
	{
		static CCGameWndProc instance;
		return &instance;
	}
	//内联函数，HOOK游戏窗口消息
	void SetGameWndProc()
	{
		HWND hTopWnd = NULL;
		::EnumWindows(EnumWindowsProc, (LPARAM)&hTopWnd);
		g_hGameHandle = hTopWnd;
		if(NULL !=hTopWnd)
		{
			 lwndProc = GetWindowLong(hTopWnd, GWL_WNDPROC);  
			 SetWindowLong(hTopWnd,GWL_WNDPROC,(LONG)WndProc);
			 OutputDebugString("HOOK窗口消息成功!");
		}else
		{
			OutputDebugString("HOOK窗口消息失败!");
		}
	}
	//获取游戏模块地址
	HWND GetGameModuleAddr()
	{
		return (HWND)GetModuleHandle("JX3Client.exe");
	}
	//获取游戏UI模块地址
	int GetGameUIModuleAddr()
	{
		return (int)GetModuleHandle("JX3UI.dll");
	}
	//获取游戏KGUI模块地址
	int GetGameKGUIModuleAddr()
	{
		return (int)GetModuleHandle("KGUI.dll");
	}
	//获取游戏JX3Represent模块地址
	int GetGameJX3RepresentModuleAddr()
	{
		return (int)GetModuleHandle("JX3Represent.dll");
	}
};



