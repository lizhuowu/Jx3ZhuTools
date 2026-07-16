#include "stdafx.h"
#include "CSkillObject.h"


CCSkillObject::CCSkillObject(void)
{
}
//带参数的构造
CCSkillObject::CCSkillObject(int Addr)
{
	BASE_START = 0;//技能开始地址
	SKILL_LEVEL = 0;//技能等级
	SKILL_ID = 0;//技能ID
	OBJECT_ADDR = 0;//对象地址
	SKILL_NAME = "";//怪物名称
	CURRENT_XIUWEI = 0;//当前修为
	__TRY
		if(Addr && IsReadAddrInt((PVOID)Addr))
		{
			BASE_START = Addr;
			if (IsReadAddrInt((PVOID)((BASE_START + SKILL_OBJECT_OFFSET))))
			{
				OBJECT_ADDR = *(int *)(BASE_START + SKILL_OBJECT_OFFSET);
			}
		}else
		{
			OutputDebugString("--初始化技能对象出错");
		}
		__CATCH("初始化技能对象出错!")
}

CCSkillObject::~CCSkillObject(void)
{
}
