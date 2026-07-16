#include "stdafx.h"
#include "CPlayerTree.h"


CCPlayerTree::CCPlayerTree(void)
{
	//初始化清空
	vector <CCPlayerInfomation>().swap(vecPlayerInfo);
	CountPlayer = 0;
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
					BASE_SECOND_OFFSET_VALUE = *(int*)(BASE_FIRST_OFFSET_VALUE + PLAYER_TREEF_SECOND_OFFSET);
					InitVect();
				}
			}
		}
		__CATCH("初始化怪物二叉树对象出错!")
}
//暴露给LUA使用
CCPlayerTree::CCPlayerTree(int type)
{
	//初始化清空
	vector <int>().swap(vecPlayerTreeBASE);
	CountPlayer = 0;
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
					BASE_SECOND_OFFSET_VALUE = *(int*)(BASE_FIRST_OFFSET_VALUE + PLAYER_TREEF_SECOND_OFFSET);
					LuaInitVect();
				}
			}
		}
		__CATCH("LUA初始化怪物二叉树对象出错!")
}

CCPlayerTree::~CCPlayerTree(void)
{
}
void CCPlayerTree::InitVect()
{
	int START_ADDR = *(int *)(BASE_SECOND_OFFSET_VALUE + 4);
	MonsterTree(START_ADDR);
}
//LUA使用
void CCPlayerTree::LuaInitVect()
{
	int START_ADDR = *(int *)(BASE_SECOND_OFFSET_VALUE + 4);
	LuaMonsterTree(START_ADDR);
}
//遍历二叉树函数
void CCPlayerTree::MonsterTree(int StartTreeAddr)
{
	__TRY
		if(StartTreeAddr && IsReadAddrInt((PVOID)StartTreeAddr))
		{
			CCPlayerInfomation _CCPlayerInfomation(StartTreeAddr);
			if(_CCPlayerInfomation.getTreeFlag() == 0)
			{
				vecPlayerInfo.push_back(_CCPlayerInfomation);
				int BaseTreeAddr = _CCPlayerInfomation.getTreeAddr();
				if(BaseTreeAddr && IsReadAddrInt((PVOID)BaseTreeAddr))
				{
					int TreeLeft =  *(int *)(BaseTreeAddr);
					MonsterTree(TreeLeft);
					int TreeRight =  *(int *)(BaseTreeAddr + 0x8);
					MonsterTree(TreeRight);
				}
			}

		}
	__CATCH("初始化玩家二叉树列表出错!")
}
//LUA遍历二叉树函数
void CCPlayerTree::LuaMonsterTree(int StartTreeAddr)
{
	__TRY
		if(StartTreeAddr && IsReadAddrInt((PVOID)StartTreeAddr))
		{
			int TREE_FLAG = 0;
			TREE_FLAG = *(BYTE *)(StartTreeAddr + PLAYER_TREE_FLAG_OFFSET);
			if(TREE_FLAG==0)
			{
				vecPlayerTreeBASE.push_back(StartTreeAddr);
				int TreeLeft =  *(int *)(StartTreeAddr);
				LuaMonsterTree(TreeLeft);
				int TreeRight =  *(int *)(StartTreeAddr + 0x8);
				LuaMonsterTree(TreeRight);
			}
		}
		__CATCH("LUA初始化玩家二叉树列表出错!")
}

//获取列表数量
int CCPlayerTree::Size()
{
	return vecPlayerInfo.size();
}
//LUA获取列表数量
int CCPlayerTree::LuaSize()
{
	return vecPlayerTreeBASE.size();
}
//根据索引获取对象
CCPlayerInfomation CCPlayerTree::GetPlayerInformation(int _index)
{
	if(vecPlayerInfo.size() > 0)
	{
		return vecPlayerInfo.at(_index);
	}else
	{
		CCPlayerInfomation _CCPlayerInfomation;
		return _CCPlayerInfomation; 
	}
}
//LUA根据索引获取对象
int CCPlayerTree::LuaGetPlayerInformation(int _index)
{
	if(vecPlayerTreeBASE.size() > 0)
	{
		return vecPlayerTreeBASE.at(_index);
	}else
	{
		return 0; 
	}
}