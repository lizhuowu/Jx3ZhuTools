#include "stdafx.h"
#include "CShopTreeObject.h"


CCShopTreeObject::CCShopTreeObject(void)
{
}
CCShopTreeObject::CCShopTreeObject(int Addr)
{
	if(Addr && IsReadAddrInt((PVOID)Addr))
	{
		BASE_ADDR = Addr;
		SHOP_ID = *(int *)(BASE_ADDR + TREE_ID_SHOP_TREE);
		SHOP_ADDR = *(int *)(BASE_ADDR + TREE_ADDR_SHOP_TREE);
	}
}

CCShopTreeObject::~CCShopTreeObject(void)
{
}
