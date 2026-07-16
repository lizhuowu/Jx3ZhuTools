#include "stdafx.h"
#include "CPackPercelArray.h"


CCPackPercelArray::CCPackPercelArray(void)
{
	BASE_VALUE = 0;//基址值
	BASE_BIG_OFFSET = 0;//偏移值
	vector<int>().swap(PACK_PERCEL_VECT_ARRAY);
	__TRY
	int PACK_ALL_BASE = (int)_CCGameWndProc->GetGameModuleAddr() + PACK_PERCEL_ARRAY_BASE_OFFSET;
	if(PACK_ALL_BASE && IsReadAddrInt((PVOID)PACK_ALL_BASE))
	{
		BASE_VALUE = *(int *)(PACK_ALL_BASE);
		BASE_BIG_OFFSET = (BASE_VALUE + PACL_PERCEL_ARRAY_BIG_OFFSET + SMALL_OFFSRT__1_PACK);
		for (int i = 1;i<6;i++)
		{
			int BASE_PERCEL_ADDR = BASE_BIG_OFFSET + i*SMALL_OFFSRT__2_PACK;
			if(BASE_PERCEL_ADDR && IsReadAddrInt((PVOID)BASE_PERCEL_ADDR))
			{
				int BaseValue = *(int*)BASE_PERCEL_ADDR;
				PACK_PERCEL_VECT_ARRAY.push_back(BASE_PERCEL_ADDR);
			}
		}
	}
	__CATCH("初始化背包包裹数组对象出错")
}


CCPackPercelArray::~CCPackPercelArray(void)
{
}
