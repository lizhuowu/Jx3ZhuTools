#include "stdafx.h"
#include "CTaskJujimentArray.h"

#define  CURRENT_TASK_JUJMENT_COUNT 8 //查找的数量
#define  PER_TASK_JUJMENT 0x44 //每个任务判断条件的大小
#define  TASK_JUJMETN_OBJECT 0x8//任务属性偏移

CCTaskJujimentArray::CCTaskJujimentArray(void)
{
	BASE_VALUE = 0;//基址值
	BASE_OFFSET_1_VALUE = 0;//第一偏移值
	BASE_OFFSET_2_VALUE = 0;//第二偏移值
	vector<int>().swap(vecJujmentObjects);
	__TRY
		int TASK_BASE = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_BASE_OFFSET;
		if(TASK_BASE && IsReadAddrInt((PVOID)TASK_BASE))
		{
			BASE_VALUE = *(int *)TASK_BASE;
			BASE_OFFSET_1_VALUE = BASE_VALUE + TASK_JUDJMENT_ARRAY_OFFSET_1;
			BASE_OFFSET_2_VALUE = BASE_OFFSET_1_VALUE + TASK_JUDJMENT_ARRAY_OFFSET_2;
			for (int i = 0;i<CURRENT_TASK_JUJMENT_COUNT;i++)
			{
				int CurrentAddr = BASE_OFFSET_2_VALUE + i * PER_TASK_JUJMENT;
				if(CurrentAddr && IsReadAddrInt((PVOID)CurrentAddr))
				{
					int FlagJujMent = *(int *)(CurrentAddr + TASK_JUJMETN_OBJECT);
					if(FlagJujMent > 0)
					{
						vecJujmentObjects.push_back(CurrentAddr);
					}
				}
			}
		}
	__CATCH("初始化任务条件判断数组对象失败!")
}


CCTaskJujimentArray::~CCTaskJujimentArray(void)
{
}
