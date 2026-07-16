#include "stdafx.h"
#include "CTaskHasIDs.h"

#define  CURRENT_TASK_COUNT 8

CCTaskHasIDs::CCTaskHasIDs(void)
{
	BASE_VALUE = 0;
	BASE_OFFSET_1 = 0;
	BASE_OFFSET_2 = 0;
	vector<int>().swap(vecTaskIDs);
	__TRY
		int TASK_BASE = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_BASE_OFFSET;
		if(TASK_BASE && IsReadAddrInt((PVOID)TASK_BASE))
		{
			BASE_VALUE = *(int *)TASK_BASE;
			BASE_OFFSET_1 = BASE_VALUE + CURRENT_TASK_ID_OFFSET_1;
			BASE_OFFSET_2 = BASE_OFFSET_1 + CURRENT_TASK_ID_OFFSET_2;
			if(BASE_OFFSET_2 && IsReadAddrInt((PVOID)BASE_OFFSET_2))
			{
				//遍历一定数量的IDs
				for (int i =0;i < CURRENT_TASK_COUNT; i++)
				{
					if((BASE_OFFSET_2 + i * 4) && IsReadAddrInt((PVOID)(BASE_OFFSET_2 + i * 4)))
					{
						int CurrentID = *(int *)(BASE_OFFSET_2 + i * 4);
						if(CurrentID > 0)
						{
							vecTaskIDs.push_back(CurrentID);
						}
					}
				}
			}
		}
	__CATCH("初始化已接任务ID数组对象出错")
}


CCTaskHasIDs::~CCTaskHasIDs(void)
{
}
