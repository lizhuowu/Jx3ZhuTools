#include "stdafx.h"
#include "CPackArray.h"


CCPackArray::CCPackArray(void)
{
}

CCPackArray::CCPackArray(int BaseAddr)
{
	BASE_ADDR = 0;//基址值
	PACKET_COUNT = 0;//偏移值
	vector<int>().swap(PACK_VECT_ARRAY);
	__TRY
	if(BaseAddr && IsReadAddrInt((PVOID)BaseAddr))
	{
		BASE_ADDR =BaseAddr;
		PACKET_COUNT = *(int*)(BASE_ADDR);
		for (int i = 1;i<=PACKET_COUNT;i++)
		{
			if((BASE_ADDR + i * 4) && IsReadAddrInt((PVOID)(BASE_ADDR + i * 4)))
			{
				int CurrentAddr = *(int *)(BASE_ADDR + i * 4);
				PACK_VECT_ARRAY.push_back(CurrentAddr);
			}
		}
	}
	__CATCH("初始化背包数组对象出错")
}

CCPackArray::~CCPackArray(void)
{
}
