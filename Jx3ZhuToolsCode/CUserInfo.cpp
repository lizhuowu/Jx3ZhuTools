#include "stdafx.h"
#include "CUserInfo.h"



//构造函数
//可以优化，懒获取，使用时再读取
CCUserInfo::CCUserInfo()
{
	BASE_ADDR = 0;
	ObjectID = 0;
	ObjectPointX = 0;
	ObjectPointY = 0;
	ObjectPointZ = 0;
	ObjectName = "";
	ObjectTitle = "";
	ObjectMap = "";
	ObjectLevel = 0;
	ObjectCurrentBlood = -1;
	ObjectMaxBlood = -1;
	ObjectCurrentMagic = -1;
	ObjectMaxMagic = -1;
	ObjectSelectFlag = 0;
	ObjectDeiection = 0;
	ObjectBellte = 0;
	ObjectGold = 0;
	ObjectXiuWei = 0;
	if(ROLE_BASE_OFFSET)
	{
		BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_BASE_OFFSET;
		BASE_ADDR = *(unsigned int *)(BASE_ADDR);
		/*if(BASE_ADDR && IsReadAddrInt((PVOID)BASE_ADDR))
		{
			ObjectID = *(unsigned int *)(BASE_ADDR + USER_ID_OFFSET);
			ObjectPointX = *(unsigned int *)(BASE_ADDR + USER_POINT_X_OFFSET);
			ObjectPointY = *(unsigned int *)(BASE_ADDR + USER_POINT_Y_OFFSET);
			ObjectPointZ = *(unsigned int *)(BASE_ADDR + USER_POINT_Z_OFFSET);
			char charStr[255] = {0};
			strcpy_s(charStr,(char *)(BASE_ADDR + USER_NAME_OFFSET));
			ObjectName = charStr;
			memset(charStr,0,255);
			strcpy_s(charStr,(char *)(BASE_ADDR + USER_TITLE_OFFSET));
			ObjectTitle = charStr;
			ObjectLevel = *(unsigned int *)(BASE_ADDR + USER_LEVEL_OFFSET);
			ObjectCurrentBlood = *(unsigned int *)(BASE_ADDR + ROLE_CURRENT_BLOOD_OFFSET);
			ObjectMaxBlood = *(unsigned int *)(BASE_ADDR + ROLE_CURRENT_BLOOD_OFFSET + 4);
			ObjectCurrentMagic = *(unsigned int *)(BASE_ADDR + ROLE_CURRENT_MAGIC_OFFSET);
			ObjectMaxMagic = *(unsigned int *)(BASE_ADDR + ROLE_CURRENT_MAGIC_OFFSET + 4);
			ObjectSelectFlag =  *(unsigned int *)(BASE_ADDR + USER_SELECT_FLAG_OFFSET);
		}*/
	}
}
CCUserInfo::~CCUserInfo(void)
{
}
