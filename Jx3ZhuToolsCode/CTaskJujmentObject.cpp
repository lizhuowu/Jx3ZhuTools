#include "stdafx.h"
#include "CTaskJujmentObject.h"


CCTaskJujmentObject::CCTaskJujmentObject(void)
{
}
//重载构造
CCTaskJujmentObject::CCTaskJujmentObject(int Base_Start_Addr)
{
	BASE_OBJECT = 0;//根地址
	TASK_OBJECT = 0;//任务对象地址
	TASK_ID = 0;//任务ID
	__TRY
		if(Base_Start_Addr && IsReadAddrInt((PVOID)Base_Start_Addr))
		{
			BASE_OBJECT = Base_Start_Addr;
			TASK_OBJECT = *(int *)(BASE_OBJECT + TASK_OBJECT_OFFSET);
			if(TASK_OBJECT && IsReadAddrInt((PVOID)TASK_OBJECT))
			{
				TASK_ID = *(int *)(TASK_OBJECT);
			}
		}
	__CATCH("初始化任务条件对象出错!")
}


CCTaskJujmentObject::~CCTaskJujmentObject(void)
{
}

//获取任务ID
int CCTaskJujmentObject::getTaskID()
{
	return TASK_ID;
}

//根据索引获取已打怪数量
int CCTaskJujmentObject::getTaskCurrentMonstByIndex(int _index)
{
	int ReadAddr = BASE_OBJECT + TASK_MONSTER_COUNT_START_OFFSET + _index * 4;
	if(ReadAddr && IsReadAddrInt((PVOID)ReadAddr))
	{
		int resultRet = *(WORD *)(ReadAddr);
		return resultRet;
	}else
	{
		return 0;
	}
}
//根据索引获取最大打怪数量
int CCTaskJujmentObject::getTaskMaxMonstByIndex(int _index)
{
	int ReadAddr = TASK_OBJECT + TASK_MAX_MONSTER_COUNT_START_OFFSET + _index * 2;
	if(ReadAddr && IsReadAddrInt((PVOID)ReadAddr))
	{
		int resultRet = *(WORD *)(ReadAddr);
		return resultRet;
	}else
	{
		return 0;
	}
}
//根据索引获取步骤当前数量
int CCTaskJujmentObject::getTaskStepByIndex(int _index)
{
	int ReadAddr = BASE_OBJECT + TASK_MAX_STEP_COUNT_START_OFFSET + _index * 4;
	if(ReadAddr && IsReadAddrInt((PVOID)ReadAddr))
	{
		int resultRet = *(int *)(ReadAddr);
		return resultRet;
	}else
	{
		return 0;
	}
}
//根据索引获取步骤打怪最大数量
//参数1.步骤索引
int CCTaskJujmentObject::getTaskStepMaxByIndex(int _index)
{
	int ReadAddr = TASK_OBJECT + TASK_STEP_COUNT_START_OFFSET + _index * 4;
	if(ReadAddr && IsReadAddrInt((PVOID)ReadAddr))
	{
		int resultRet = *(int *)(ReadAddr);
		return resultRet;
	}else
	{
		return 0;
	}
}

//根据索引获取采集最大数量
int CCTaskJujmentObject::getTaskAcquistMaxCountByIndex(int _index)
{
	int ReadAddr = TASK_OBJECT + TASK_MAX_ACQUIST_COUNT_START_OFFSET + _index * 2;
	if(ReadAddr && IsReadAddrInt((PVOID)ReadAddr))
	{
		int resultRet = *(int *)(ReadAddr);
		return resultRet;
	}else
	{
		return 0;
	}
}