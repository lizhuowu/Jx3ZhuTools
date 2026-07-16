#include "stdafx.h"
#include "CMonsterInformation.h"


CCMonsterInformation::CCMonsterInformation(void)
{
}
CCMonsterInformation::CCMonsterInformation(int addr)
{
	TREE_ADDR = 0;
	MONSTER_ID = 0;
	MONSTER_OBJECT_ADDR = 0;
	MONSTER_POINT_X = 0;
	MONSTER_POINT_Y = 0;//怪物Y坐标
	MONSTER_POINT_Z = 0;//怪物Z坐标
	MONSTER_NAME = "";//怪物名称
	MONSTER_TITLE = "";//怪物称号
	MONSTER_CURRENT_BLOOD = -1;//怪物当前血
	MONSTER_MAX_BLOOD = -1;//怪物最大血
	MONSTER_CURRENT_MAGIC = -1;//怪物当前魔法
	MONSTER_MAX_MAGIC = -1;//怪物最大魔法
	__TRY
		if(addr && IsReadAddrInt((PVOID)addr))
		{
			TREE_ADDR = addr;
			MONSTER_OBJECT_ADDR = *(int *)(TREE_ADDR + MONSTER_OBJECT_OFFSET);
		}else
		{
			OutputDebugString("--初始化怪物对象出错");
		}
	__CATCH("初始化怪物对象出错!")
}


CCMonsterInformation::~CCMonsterInformation(void)
{
}
