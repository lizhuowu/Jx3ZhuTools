#include "stdafx.h"
#include "CMonsterTree.h"


CCMonsterTree::CCMonsterTree(void)
{
	//初始化清空
	vector <CCMonsterInformation>().swap(vecMonsterInfo);
	CountMonster = 0;
	__TRY
		BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + MONSTER_TERR_BASE_OFFSET;
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			BASE_VALUE = *(int*)(BASE_ADDR);
			if(BASE_VALUE && IsReadAddrInt((PVOID)BASE_VALUE))
			{
				BASE_FIRST_OFFSET_VALUE = *(int*)(BASE_VALUE + MONSTER_TERR_OFFSET);
				if(BASE_FIRST_OFFSET_VALUE && IsReadAddrInt((PVOID)BASE_FIRST_OFFSET_VALUE))
				{
					BASE_SECOND_OFFSET_VALUE = *(int*)(BASE_FIRST_OFFSET_VALUE + MONSTER_TREEF_SECOND_OFFSET);
					InitVect();
				}
			}
		}
	__CATCH("初始化怪物二叉树对象出错!")
}
//暴露给LUA使用
CCMonsterTree::CCMonsterTree(int type)
{
	//初始化清空
	vector <int>().swap(vecMonsterTreeBASE);
	CountMonster = 0;
	BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + MONSTER_TERR_BASE_OFFSET;
	__TRY
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			BASE_VALUE = *(int*)(BASE_ADDR);
			if(BASE_VALUE && IsReadAddrInt((PVOID)BASE_VALUE))
			{
				BASE_FIRST_OFFSET_VALUE = *(int*)(BASE_VALUE + MONSTER_TERR_OFFSET);
				if(BASE_FIRST_OFFSET_VALUE && IsReadAddrInt((PVOID)BASE_FIRST_OFFSET_VALUE))
				{
					BASE_SECOND_OFFSET_VALUE = *(int*)(BASE_FIRST_OFFSET_VALUE + MONSTER_TREEF_SECOND_OFFSET);
					LuaInitVect();
				}
			}
		}
		__CATCH("LUA初始化怪物二叉树对象出错!")
}

void CCMonsterTree::InitVect()
{
	int START_ADDR = *(int *)(BASE_SECOND_OFFSET_VALUE + 4);
	MonsterTree(START_ADDR);
}
//LUA使用
void CCMonsterTree::LuaInitVect()
{
	int START_ADDR = *(int *)(BASE_SECOND_OFFSET_VALUE + 4);
	LuaMonsterTree(START_ADDR);
}
//遍历二叉树函数
void CCMonsterTree::MonsterTree(int StartTreeAddr)
{
	__TRY
		if(StartTreeAddr && IsReadAddrInt((PVOID)StartTreeAddr))
		{
			CCMonsterInformation _CCMonsterInformation(StartTreeAddr);
			if(_CCMonsterInformation.getTreeFlag() == 0)
			{
				vecMonsterInfo.push_back(_CCMonsterInformation);
				int BaseTreeAddr = _CCMonsterInformation.getTreeAddr();
				if(BaseTreeAddr && IsReadAddrInt((PVOID)BaseTreeAddr))
				{
					int TreeLeft =  *(int *)(BaseTreeAddr);
					MonsterTree(TreeLeft);
					int TreeRight =  *(int *)(BaseTreeAddr + 0x8);
					MonsterTree(TreeRight);
				}
			}
			
		}
	__CATCH("初始化怪物二叉树列表出错!")
}
//LUA遍历二叉树函数
void CCMonsterTree::LuaMonsterTree(int StartTreeAddr)
{
	__TRY
		if(StartTreeAddr && IsReadAddrInt((PVOID)StartTreeAddr))
		{
			int TREE_FLAG = 0;
			TREE_FLAG = *(BYTE *)(StartTreeAddr + MONSTER_TREE_FLAG_OFFSET);
			if(TREE_FLAG==0)
			{
				vecMonsterTreeBASE.push_back(StartTreeAddr);
				int TreeLeft =  *(int *)(StartTreeAddr);
				LuaMonsterTree(TreeLeft);
				int TreeRight =  *(int *)(StartTreeAddr + 0x8);
				LuaMonsterTree(TreeRight);
			}
		}
		__CATCH("LUA初始化怪物二叉树列表出错!")
}
//获取列表数量
int CCMonsterTree::Size()
{
	return vecMonsterInfo.size();
}
//LUA获取列表数量
int CCMonsterTree::LuaSize()
{
	return vecMonsterTreeBASE.size();
}
//根据索引获取对象
CCMonsterInformation CCMonsterTree::GetMonsterInformation(int _index)
{
	if(vecMonsterInfo.size() > 0)
	{
		return vecMonsterInfo.at(_index);
	}else
	{
		CCMonsterInformation _CCMonsterInformation;
		return _CCMonsterInformation; 
	}
}
//LUA根据索引获取对象
int CCMonsterTree::LuaGetMonsterInformation(int _index)
{
	if(vecMonsterTreeBASE.size() > 0)
	{
		return vecMonsterTreeBASE.at(_index);
	}else
	{
		return 0; 
	}
}


CCMonsterTree::~CCMonsterTree(void)
{
}
