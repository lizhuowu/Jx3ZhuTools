#include "stdafx.h"
#include "CPlayerInfomation.h"


CCPlayerInfomation::CCPlayerInfomation(void)
{
}

CCPlayerInfomation::CCPlayerInfomation(int addr)
{
	TREE_ADDR = 0;
	PLAYER_ID = 0;
	PLAYER_OBJECT_ADDR = 0;
	PLAYER_POINT_X = 0;
	PLAYER_POINT_Y = 0;//玩家Y坐标
	PLAYER_POINT_Z = 0;//玩家Z坐标
	PLAYER_NAME = "";//玩家名称
	__TRY
		if(addr && IsReadAddrInt((PVOID)addr))
		{
			TREE_ADDR = addr;
			PLAYER_OBJECT_ADDR = *(int *)(TREE_ADDR + PLAYER_OBJECT_OFFSET);
		}else
		{
			OutputDebugString("--初始化玩家对象出错");
		}
		__CATCH("初始化玩家对象出错!")
}

CCPlayerInfomation::~CCPlayerInfomation(void)
{
}
