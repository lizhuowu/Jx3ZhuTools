#include "stdafx.h"
#include "CShopGoodArray.h"


CCShopGoodArray::CCShopGoodArray(void)
{
}
CCShopGoodArray::CCShopGoodArray(int addr)
{
	BASE_ADDR = 0;
	COUNT = 0;
	__TRY
	vector<int>().swap(vecAllShopArrayAddr);
	if(addr && IsReadAddrInt((PVOID)addr))
	{
		BASE_ADDR = addr;
		COUNT = *(int *)(BASE_ADDR + SHOP_LIST_COUNT_OFFSET);
		if(COUNT > 0)
		{
			shopArrayID = *(int *)(BASE_ADDR);
			int CurrentBaseAddr = *(int *)(BASE_ADDR + SHOP_LIST_OFFSET);
			if(CurrentBaseAddr && IsReadAddrInt((PVOID)CurrentBaseAddr))
			{
				for (int i = 0;i < COUNT; i++)
				{
					int CurrentAddr = CurrentBaseAddr + i * PER_OFFSET_SHOP_GOOD_ARRAY;
					vecAllShopArrayAddr.push_back(CurrentAddr);
				}
			}
			
		}
	}
	__CATCH("初始化商店物品数组对象出错!")
}

CCShopGoodArray::~CCShopGoodArray(void)
{
}
