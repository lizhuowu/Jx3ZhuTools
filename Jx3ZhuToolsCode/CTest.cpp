#include "stdafx.h"
#include "CTest.h"


CCTest::CCTest(void)
{
}


CCTest::~CCTest(void)
{
}

//传入文本，返回文本测试函数
char * CCTest::getStr(char * content)
{
	return "收到返回值";
}
int CCTest::retInt(int X,int Y)
{
	return X + Y;
}

