#include "stdafx.h"
#include "CAllTaskTree.h"

#define  TREE_FLAG 0xD // 二叉树判标志位

CCAllTaskTree::CCAllTaskTree(void)
{
	BASE_VALUE = 0;//基址值
	BASE_OFFSET = 0;//偏移值
	TREE_START_VALUE = 0;//二叉树开始地址值
	vector<int>().swap(vecAllTask);
	__TRY
		int TASK_ALL_BASE = (int)_CCGameWndProc->GetGameModuleAddr() + TASK_ALL_BASE_OFFSET;
		if(TASK_ALL_BASE && IsReadAddrInt((PVOID)TASK_ALL_BASE))
		{
			BASE_VALUE = *(int *)(TASK_ALL_BASE);
			BASE_OFFSET = *(int *)(BASE_VALUE + TASK_ALL_BASE_FIRST_OFFSET);
			if(BASE_OFFSET && IsReadAddrInt((PVOID)BASE_OFFSET))
			{
				TREE_START_VALUE = *(int *)(BASE_OFFSET + 0x4);//二叉树开始地址
				TreeList(TREE_START_VALUE);
			}
		}
	__CATCH("初始化所有任务二叉对象出错")
}
//遍历二叉树
void CCAllTaskTree::TreeList(int StartAddr)
{
	if(StartAddr && IsReadAddrInt((PVOID)StartAddr))
	{
		int Flag = *(byte*)(StartAddr + TREE_FLAG);
		if(Flag == 0)
		{
			vecAllTask.push_back(StartAddr);
			int LeftAddr = *(int *)(StartAddr);
			TreeList(LeftAddr);
			int RightAddr = *(int *)(StartAddr + 8);
			TreeList(RightAddr);
		}
	}
}

CCAllTaskTree::~CCAllTaskTree(void)
{
}
