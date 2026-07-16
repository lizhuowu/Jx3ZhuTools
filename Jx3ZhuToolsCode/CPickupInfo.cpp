#include "stdafx.h"
#include "CPickupInfo.h"


CCPickupInfo::CCPickupInfo(void)
{
}
CCPickupInfo::CCPickupInfo(int BASE_ADDR)
{
	BASE_PICKUP = 0;
	PICKUP_ID = 0;
	BASE_PICKUP_OBJECT = 0;
	PICKUP_GOOD_ID = 0;
	PICKUP_NAME = "";
	__TRY
		if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			BASE_PICKUP = BASE_ADDR;
			PICKUP_ID = *(int *)(BASE_PICKUP + PICKUP_ID_OFFSET);
			BASE_PICKUP_OBJECT = *(int *)(BASE_PICKUP + PICKUP_OBJECT_OFFSET);
			if(BASE_PICKUP_OBJECT && IsReadAddrInt((PVOID)BASE_PICKUP_OBJECT))
			{
				PICKUP_GOOD_ID = *(int *)(BASE_PICKUP_OBJECT + PICKUP_GOOD_ID_OFFSET);
				char GoodName[255] = {0};
				strcpy_s(GoodName,(char *)(BASE_PICKUP_OBJECT + PICKUP_NAME_OFFSET));
				char * U2GStr =  U2G(GoodName);
				memset(GoodName,0,255);
				strcpy_s(GoodName,U2GStr);
				if(U2GStr) delete[] U2GStr;
				PICKUP_NAME = GoodName;
			}
		}
	__CATCH("初始化捡取包裹对象出错")
}

CCPickupInfo::~CCPickupInfo(void)
{

}
