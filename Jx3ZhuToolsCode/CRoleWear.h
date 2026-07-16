#pragma once

#define  WEAR_SMALL_OFFSRT__1_PACK 0x18 //小偏移1
#define  WEAR_SMALL_OFFSRT__2_PACK 0x94 //小偏移2
class CCRoleWear
{
private:
	int BASE_VALUE;//基址值
	int BASE_BIG_OFFSET;//大偏移值
	int START_ADDR;//穿戴开始地址
public:
	CCRoleWear(void);
	~CCRoleWear(void);
	//获取开始地址
	int getAddr()
	{
		return START_ADDR;
	} 
};
