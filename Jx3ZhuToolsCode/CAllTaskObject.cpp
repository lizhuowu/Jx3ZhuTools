#include "stdafx.h"
#include "CAllTaskObject.h"


CCAllTaskObject::CCAllTaskObject(void)
{
}
CCAllTaskObject::CCAllTaskObject(int BASE_START)
{
	BASE_TREE_ADDR = 0;
	TASK_ID = 0;
	BASE_OBJECT_ADDR = 0;
	__TRY
		if(BASE_START && IsReadAddrInt(PVOID(BASE_START)))
		{
			BASE_TREE_ADDR = BASE_START;
			TASK_ID = *(int *)(BASE_TREE_ADDR + ID_OFFSET);
			BASE_OBJECT_ADDR = BASE_TREE_ADDR + ID_OBJECT_OFFSET;
		}
	__CATCH("初始化所有任务单个对象出错")
}



CCAllTaskObject::~CCAllTaskObject(void)
{
}
