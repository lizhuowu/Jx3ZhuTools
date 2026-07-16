#pragma once
#include "CUserInfo.h"
#include "CCall.h"
class CCCommon
{
private:
	//判断是否寻路到
	BOOLEAN IsRunOver(int MoveX,int MoveY,int RoleX,int RoleY);
public:
	CCCommon(void);
	~CCCommon(void);
	//取运行目录
	CString GetLuaRootPath ();
	//堵塞寻路
	BOOLEAN MoveTo(int MoveX,int MoveY);
	void HOOK_DODGE_1();
	void HOOK_DODGE_2();
	int GetShopAddr(int ShopID);
	//修理全部装备
	void RepairWear();
	void OrganMoveSucess();
};

