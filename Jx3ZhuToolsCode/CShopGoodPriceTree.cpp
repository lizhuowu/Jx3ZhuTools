#include "stdafx.h"
#include "CShopGoodPriceTree.h"


CCShopGoodPriceTree::CCShopGoodPriceTree(void)
{
	BASE_VALUE = 0;//基址值
	BASE_OFFSET = 0;//偏移值
	START_ADDR = 0;//二叉树开始地址值
	vector<int>().swap(vecAllShopAddr);
	__TRY
		int SHOP_ALL_BASE = (int)_CCGameWndProc->GetGameModuleAddr() + GET_SHOP_ADDR_BY_SHOPID_TREE_ECX_OFFSET;
	if(SHOP_ALL_BASE && IsReadAddrInt((PVOID)SHOP_ALL_BASE))
	{
		BASE_VALUE = *(int *)(SHOP_ALL_BASE);
		BASE_OFFSET = *(int *)(BASE_VALUE + GET_SHOP_ADDR_BY_SHOPID_TREE_BIG_OFFSET);
		if(BASE_OFFSET && IsReadAddrInt((PVOID)BASE_OFFSET))
		{
			START_ADDR = *(int *)(BASE_OFFSET + 0x4);//二叉树开始地址
			TreeList(START_ADDR);
		}
	}
	__CATCH("初始化所有商店单价二叉对象出错")
}
//遍历二叉树
void CCShopGoodPriceTree::TreeList(int StartAddr)
{
	if(StartAddr && IsReadAddrInt((PVOID)StartAddr))
	{
		int Flag = *(byte*)(StartAddr + TREE_SHOP_FALG_OFFSET);
		if(Flag == 0)
		{
			vecAllShopAddr.push_back(StartAddr);
			int LeftAddr = *(int *)(StartAddr);
			TreeList(LeftAddr);
			int RightAddr = *(int *)(StartAddr + 8);
			TreeList(RightAddr);
		}
	}
}

CCShopGoodPriceTree::~CCShopGoodPriceTree(void)
{
}
