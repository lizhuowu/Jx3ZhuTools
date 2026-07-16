#include "stdafx.h"
#include "CGroundTree.h"


CCGroundTree::CCGroundTree(void)
{
	//初始化清空
	vector <CCGroundInfo>().swap(vecGround);
	CountGround = 0;
	BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + DOOD_TERR_BASE_OFFSET;
	__TRY
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			BASE_VALUE = *(int*)(BASE_ADDR);
			if(BASE_VALUE && IsReadAddrInt((PVOID)BASE_VALUE))
			{
				BASE_FIRST_OFFSET_VALUE = *(int*)(BASE_VALUE + DOOD_TERR_OFFSET);
				if(BASE_FIRST_OFFSET_VALUE && IsReadAddrInt((PVOID)BASE_FIRST_OFFSET_VALUE))
				{
					BASE_SECOND_OFFSET_VALUE = *(int*)(BASE_FIRST_OFFSET_VALUE + GROUND_TREEF_SECOND_OFFSET);
					InitVect();
				}
			}
		}
		__CATCH("初始化地面二叉树对象出错!")
}

void CCGroundTree::InitVect()
{
	int START_ADDR = *(int *)(BASE_SECOND_OFFSET_VALUE + 4);
	GroundTree(START_ADDR);
}

//遍历二叉树函数
void CCGroundTree::GroundTree(int StartTreeAddr)
{
	__TRY
		if(StartTreeAddr && IsReadAddrInt((PVOID)StartTreeAddr))
		{
			CCGroundInfo _CCGroundInfo(StartTreeAddr);
			if(_CCGroundInfo.getTreeFlag() == 0)
			{
				vecGround.push_back(_CCGroundInfo);
				int BaseTreeAddr = _CCGroundInfo.getTreeAddr();
				if(BaseTreeAddr && IsReadAddrInt((PVOID)BaseTreeAddr))
				{
					int TreeLeft =  *(int *)(BaseTreeAddr);
					GroundTree(TreeLeft);
					int TreeRight =  *(int *)(BaseTreeAddr + 0x8);
					GroundTree(TreeRight);
				}
			}

		}
	__CATCH("初始化地面二叉树列表出错!")
}
//获取列表数量
int CCGroundTree::Size()
{
	return vecGround.size();
}

//根据索引获取对象
CCGroundInfo CCGroundTree::GetGroundInformation(int _index)
{
	if(vecGround.size() > 0)
	{
		return vecGround.at(_index);
	}else
	{
		CCGroundInfo _CCGroundInfo;
		return _CCGroundInfo; 
	}
}
//LUA使用函数
//////////////////////////////////////////////////////////////////////////
//暴露给LUA使用
CCGroundTree::CCGroundTree(int type)
{
	//初始化清空
	vector <int>().swap(vecGroundTreeBASE);
	CountGround = 0;
	BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + DOOD_TERR_BASE_OFFSET;
	__TRY
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			BASE_VALUE = *(int*)(BASE_ADDR);
			if(BASE_VALUE && IsReadAddrInt((PVOID)BASE_VALUE))
			{
				BASE_FIRST_OFFSET_VALUE = *(int*)(BASE_VALUE + DOOD_TERR_OFFSET);
				if(BASE_FIRST_OFFSET_VALUE && IsReadAddrInt((PVOID)BASE_FIRST_OFFSET_VALUE))
				{
					BASE_SECOND_OFFSET_VALUE = *(int*)(BASE_FIRST_OFFSET_VALUE + GROUND_TREEF_SECOND_OFFSET);
					LuaInitVect();
				}
			}
		}
		__CATCH("初始化地面二叉树对象出错!")
}

//LUA使用
void CCGroundTree::LuaInitVect()
{
	int START_ADDR = *(int *)(BASE_SECOND_OFFSET_VALUE + 4);
	LuaGroundTree(START_ADDR);
}

//LUA遍历二叉树函数
void CCGroundTree::LuaGroundTree(int StartTreeAddr)
{
	__TRY
		if(StartTreeAddr && IsReadAddrInt((PVOID)StartTreeAddr))
		{
			int TREE_FLAG = 0;
			TREE_FLAG = *(BYTE *)(StartTreeAddr + MONSTER_TREE_FLAG_OFFSET);
			if(TREE_FLAG==0)
			{
				vecGroundTreeBASE.push_back(StartTreeAddr);
				int TreeLeft =  *(int *)(StartTreeAddr);
				LuaGroundTree(TreeLeft);
				int TreeRight =  *(int *)(StartTreeAddr + 0x8);
				LuaGroundTree(TreeRight);
			}
		}
		__CATCH("LUA初始化地面二叉树列表出错!")
}

//LUA获取列表数量
int CCGroundTree::LuaSize()
{
	return vecGroundTreeBASE.size();
}
//LUA根据索引获取对象
int CCGroundTree::LuaGetGroundInfo(int _index)
{
	if(vecGroundTreeBASE.size() > 0)
	{
		return vecGroundTreeBASE.at(_index);
	}else
	{
		return 0; 
	}
}

CCGroundTree::~CCGroundTree(void)
{
}
