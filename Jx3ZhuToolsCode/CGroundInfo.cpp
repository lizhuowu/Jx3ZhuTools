#include "stdafx.h"
#include "CGroundInfo.h"


CCGroundInfo::CCGroundInfo(void)
{
}


CCGroundInfo::CCGroundInfo(int addr)
{
	TREE_ADDR = 0;
	GROUND_ID = 0;
	GROUND_OBJECT_ADDR = 0;
	GROUND_POINT_X = 0;
	GROUND_POINT_Y = 0;//怪物Y坐标
	GROUND_POINT_Z = 0;//怪物Z坐标
	GROUND_NAME = "";//怪物名称
	__TRY
		if(addr && IsReadAddrInt((PVOID)addr))
		{
			TREE_ADDR = addr;
			GROUND_OBJECT_ADDR = *(int *)(TREE_ADDR + GROUND_OBJECT_OFFSET);
		}else
		{
			OutputDebugString("--初始化怪物对象出错");
		}
		__CATCH("初始化怪物对象出错!")
}
CCGroundInfo::~CCGroundInfo(void)
{
}
