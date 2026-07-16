#pragma once

#define  THOUSANDS_SMALL_OFFSRT__1_PACK 0x18 //小偏移1
#define  THOUSANDS_SMALL_OFFSRT__2_PACK 0x94 //小偏移2
#define	 THOUSANDS_PACK_INDEX 0x11 //千机背包标号

class CCThousands
{
private:
	int BASE_VALUE;//基址值
	int BASE_BIG_OFFSET;//大偏移值
	int START_ADDR;//千机开始地址
public:
	CCThousands(void);
	~CCThousands(void);
	//获取开始地址
	int getAddr()
	{
		return START_ADDR;
	} 
};

