#include "stdafx.h"
#include "CDoodPickups.h"


CCDoodPickups::CCDoodPickups(void)
{
}

CCDoodPickups::CCDoodPickups(int addr)
{
	vector<int>().swap(PICKET_ADDRS);
	COUNT = 0;
	BASE_ADDR = 0;
	BASE_LIST = 0;
	BASE_PICK_ADDR = 0;
	__TRY
		if(addr && IsReadAddrInt((PVOID)addr))
		{
			BASE_ADDR = addr;
			BASE_PICK_ADDR = *(int *)(BASE_ADDR + DOOR_PICKUP_ADDR_OFFSET);
			if(BASE_PICK_ADDR > 0)
			{
				//计算数量
				BASE_LIST = *(int *)(BASE_PICK_ADDR + DOOR_PICKUP_LIST_OFFSET);
				int END_LIST = *(int *)(BASE_PICK_ADDR + DOOR_PICKUP_LIST_OFFSET + 4);
				int _EDX= END_LIST - BASE_LIST;
				int currenrCount = 0;
				_asm
				{
					MOV EAX,0x2AAAAAAB
					MOV EDX,_EDX
					IMUL EDX
					SAR EDX,1
					MOV currenrCount,EDX
				}
				COUNT = currenrCount;
				if(COUNT > 0 && COUNT<10)
				{
					for (int i = 0;i < COUNT;i++)
					{
						int PICKET_ADDR = *(int *)(BASE_LIST + i * 0xC);
						PICKET_ADDRS.push_back(PICKET_ADDR);
					}
				}else
				{
					if(COUNT > 10)
					{
						OutputDebugString("计算数量出错!");
					}
				}
			}
		}
	__CATCH("初始化包裹列表出错")
}
CCDoodPickups::~CCDoodPickups(void)
{
}
