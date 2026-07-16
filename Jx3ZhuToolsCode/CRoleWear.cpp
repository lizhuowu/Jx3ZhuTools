#include "stdafx.h"
#include "CRoleWear.h"


CCRoleWear::CCRoleWear(void)
{
	BASE_VALUE = 0;//基址值
	BASE_BIG_OFFSET = 0;//偏移值
	START_ADDR = 0;
	__TRY
	int PACK_ALL_BASE = (int)_CCGameWndProc->GetGameModuleAddr() + PACK_PERCEL_ARRAY_BASE_OFFSET;
	if(PACK_ALL_BASE && IsReadAddrInt((PVOID)PACK_ALL_BASE))
	{
		BASE_VALUE = *(int *)(PACK_ALL_BASE);
		BASE_BIG_OFFSET = (BASE_VALUE + PACL_PERCEL_ARRAY_BIG_OFFSET + WEAR_SMALL_OFFSRT__1_PACK);
		int BASE_PERCEL_ADDR = BASE_BIG_OFFSET + 0*WEAR_SMALL_OFFSRT__2_PACK;
		if(BASE_PERCEL_ADDR && IsReadAddrInt((PVOID)BASE_PERCEL_ADDR))
		{
			START_ADDR = BASE_PERCEL_ADDR;
		}
	}
	__CATCH("初始化穿戴对象出错")
}


CCRoleWear::~CCRoleWear(void)
{
}
