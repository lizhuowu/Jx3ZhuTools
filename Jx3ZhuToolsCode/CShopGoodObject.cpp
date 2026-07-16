#include "stdafx.h"
#include "CShopGoodObject.h"


CCShopGoodObject::CCShopGoodObject(void)
{
}
CCShopGoodObject::CCShopGoodObject(int addr)
{
	BASE_ADDR = 0;
	BASE_ADDR_VALUE = 0;
	SHOP_FLAG = 0;
	SHOP_GOOD_OBJECT = 0;
	SHOP_GOOD_NAME = "";
	SHOP_GOOD_ID = 0;
	__TRY
		if(addr && IsReadAddrInt((PVOID)addr))
		{
			BASE_ADDR = addr;
			BASE_ADDR_VALUE = BASE_ADDR;
			if(BASE_ADDR_VALUE && IsReadAddrInt((PVOID)BASE_ADDR_VALUE))
			{
				SHOP_FLAG = *(int *)(BASE_ADDR_VALUE + SHOP_GOOD_FLAG_OFFSET);
				SHOP_GOOD_START_ADDR = *(int *)(BASE_ADDR_VALUE);

				if(SHOP_GOOD_START_ADDR && IsReadAddrInt((PVOID)SHOP_GOOD_START_ADDR))
				{
					SHOP_GOOD_ID = *(int *)(SHOP_GOOD_START_ADDR + SHOP_GOOD_ID_OFFSET);
					SHOP_GOOD_OBJECT = *(int *)(SHOP_GOOD_START_ADDR + SHOP_GOOD_OBJECT_OFFSET);
					if(SHOP_GOOD_OBJECT && IsReadAddrInt((PVOID)SHOP_GOOD_OBJECT))
					{
						char GoodName[255] = {0};
						strcpy_s(GoodName,(char *)(SHOP_GOOD_OBJECT + SHOP_GOOD_NAME_OFFSET));
						char * U2GStr =  U2G(GoodName);
						memset(GoodName,0,255);
						strcpy_s(GoodName,U2GStr);
						if(U2GStr) delete[] U2GStr;
						SHOP_GOOD_NAME = GoodName;	
					}
				}
			}
			
		}
	__CATCH("初始化商店物品对象出错")
}

CCShopGoodObject::~CCShopGoodObject(void)
{
}
