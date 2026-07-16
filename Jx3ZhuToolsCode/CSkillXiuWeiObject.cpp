#include "stdafx.h"
#include "CSkillXiuWeiObject.h"


CCSkillXiuWeiObject::CCSkillXiuWeiObject(void)
{
}
CCSkillXiuWeiObject::CCSkillXiuWeiObject(int Addr)
{
	BASE_START = 0;//技能开始地址
	SKILL_XIUWEI = 0;//技能修为
	SKILL_ID = 0;//技能ID
	__TRY
		if(Addr && IsReadAddrInt((PVOID)Addr))
		{
			BASE_START = Addr;
		}else
		{
			OutputDebugString("--初始化技能修为对象出错");
		}
		__CATCH("初始化技能修为对象出错!")
}

CCSkillXiuWeiObject::~CCSkillXiuWeiObject(void)
{
}
