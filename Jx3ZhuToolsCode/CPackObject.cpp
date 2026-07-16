#include "stdafx.h"
#include "CPackObject.h"


CCPackObject::CCPackObject(void)
{

}

CCPackObject::CCPackObject(int BaseAddr)
{
	BASE_ADDR = 0;
	GOOD_ID = 0;//物品ID
	GOOD_COUNT = 0;//物品数量
	SUB_OBJECT = 0;//子类
	GOOD_NAME = "";//物品名称
	GOOD_TYPE = 0;//类别
	ALL_PRICE = 0;//总价
	SELL_HADNLE = 0;//卖物句柄
	GOOD_MAKE_TYPE = 0;//物品使用类型
	__TRY
		if(BaseAddr && IsReadAddrInt((PVOID)BaseAddr))
		{
			BASE_ADDR = BaseAddr;
			//ID
			if((BASE_ADDR + ID_OFFSET_PACK) && IsReadAddrInt((PVOID)(BASE_ADDR + ID_OFFSET_PACK)))
			{
				GOOD_ID = *(int *)(BASE_ADDR + ID_OFFSET_PACK);
			}
			//卖物句柄
			if((BASE_ADDR + SELL_HANDLE_OFFSET) && IsReadAddrInt((PVOID)(BASE_ADDR + SELL_HANDLE_OFFSET)))
			{
				SELL_HADNLE = *(int *)(BASE_ADDR + SELL_HANDLE_OFFSET);
			}
			//子类
			if((BASE_ADDR + SUB_OBJECT_OFFSET_PACK) && IsReadAddrInt((PVOID)(BASE_ADDR + SUB_OBJECT_OFFSET_PACK)))
			{
				SUB_OBJECT = *(int *)(BASE_ADDR + SUB_OBJECT_OFFSET_PACK);
				if(SUB_OBJECT && IsReadAddrInt((PVOID)SUB_OBJECT))
				{
					//名称
					char GoodName[255] = {0};
					strcpy_s(GoodName,(char *)(SUB_OBJECT + GOOD_NAME_OFFSET_PACK));
					char * U2GStr =  U2G(GoodName);
					memset(GoodName,0,255);
					strcpy_s(GoodName,U2GStr);
					if(U2GStr) delete[] U2GStr;
					GOOD_NAME = GoodName;
					if((SUB_OBJECT + GOOD_MAKE_OFFSET_PACK) && IsReadAddrInt((PVOID)(SUB_OBJECT + GOOD_MAKE_OFFSET_PACK)))
					{
						//类型（装备或使用时）
						GOOD_MAKE_TYPE = *(int *)(SUB_OBJECT + GOOD_MAKE_OFFSET_PACK);
					}
					//总价
					ALL_PRICE = *(int *)(SUB_OBJECT + GOOD_PRICE_OFFSET_PACK);
				}

			}
			//类型
			if((BASE_ADDR + TYPE_OFFSET_PACK) && IsReadAddrInt((PVOID)(BASE_ADDR + TYPE_OFFSET_PACK)))
			{
				GOOD_TYPE = *(int *)(BASE_ADDR + TYPE_OFFSET_PACK);
				GOOD_COUNT = 1;
				if(GOOD_TYPE!=EQUIPMENT)
				{
					if((BASE_ADDR + GOOD_COUNT_OFFSET_PACK) && IsReadAddrInt((PVOID)(BASE_ADDR + GOOD_COUNT_OFFSET_PACK)))
					{
						//数量
						GOOD_COUNT = *(int *)(BASE_ADDR + GOOD_COUNT_OFFSET_PACK);
					}
				}
			}
		}

	__CATCH("初始化背包格子对象出错")
}


CCPackObject::~CCPackObject(void)
{
}
