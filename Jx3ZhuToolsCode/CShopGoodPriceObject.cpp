#include "stdafx.h"
#include "CShopGoodPriceObject.h"


CCShopGoodPriceObject::CCShopGoodPriceObject(void)
{
}
CCShopGoodPriceObject::CCShopGoodPriceObject(int addr)
{
	BASE_ADDR = 0;
	PRICE_ADDR = 0;
	__TRY
	if(addr && IsReadAddrInt((PVOID)addr))
	{
		BASE_ADDR = addr;
		PRICE_ADDR = BASE_ADDR + PRICE_OBJECT_OFFSET_LEA + GOOD_PRICE_ADDR_OFFSET;
		if(PRICE_ADDR && IsReadAddrInt((PVOID)PRICE_ADDR))
		{
			PRICE_ADDR = *(int *)PRICE_ADDR;
		}
	}
	__CATCH("初始化商店物品单价结构对象出错!")
}

CCShopGoodPriceObject::~CCShopGoodPriceObject(void)
{
}
