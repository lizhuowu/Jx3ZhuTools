#include "stdafx.h"
#include "CSkillTree.h"


CCSkillTree::CCSkillTree(void)
{
	BASE_ADDR = 0;//基地址
	BASE_ADDR_VALUE = 0;//基地址值
	SECOND_OFFSET = 0;//二级偏移
	START_ADDR = 0;//开始地址
	vector <int>().swap(SKILL_ARRAY);//技能地址集合
	__TRY
		BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_BASE_OFFSET;
		if (BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			BASE_ADDR_VALUE = *(int *)BASE_ADDR;
			if (BASE_ADDR_VALUE && IsReadAddrInt((PVOID)(BASE_ADDR_VALUE+SKILL_TERR_OFFSET)))
			{
				SECOND_OFFSET = *(int *)(BASE_ADDR_VALUE+SKILL_TERR_OFFSET);
				if (SECOND_OFFSET && IsReadAddrInt((PVOID)SECOND_OFFSET))
				{
					START_ADDR = *(int *)(SECOND_OFFSET + 4);
					LuaSkillTree(START_ADDR);
				}
			}
		}
	__CATCH("初始化技能二叉树对象出错!")
}

CCSkillTree::~CCSkillTree(void)
{
}
//遍历技能二叉
void CCSkillTree::LuaSkillTree(int StartAddr)
{
	__TRY
		if(StartAddr && IsReadAddrInt((PVOID)StartAddr))
		{
			int TREE_FLAG = 0;
			TREE_FLAG = *(BYTE *)(StartAddr + FLAG_OFFSET);
			if(TREE_FLAG==0)
			{
				SKILL_ARRAY.push_back(StartAddr);
				int TreeLeft =  *(int *)(StartAddr);
				LuaSkillTree(TreeLeft);
				int TreeRight =  *(int *)(StartAddr + 0x8);
				LuaSkillTree(TreeRight);
			}
		}
	__CATCH("LUA初始化技能二叉树列表出错!")
}
//LUA获取列表数量
int CCSkillTree::LuaSize()
{
	return SKILL_ARRAY.size();
}
//LUA根据索引获取对象
int CCSkillTree::LuaGetSkillAddr(int _index)
{
	if(SKILL_ARRAY.size() > 0)
	{
		return SKILL_ARRAY.at(_index);
	}else
	{
		return 0; 
	}
}