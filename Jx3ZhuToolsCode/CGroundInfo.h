#pragma once

//怪物对象信息
enum GROUND_OFFSET
{
	GROUND_ID_OFFSET = 0x10,//地面物品ID偏移
	GROUND_OBJECT_OFFSET = 0x14,//地面物品对象地址偏移
	GROUND_POINT_X_OFFSET = 0x8,//地面物品X坐标偏移
	GROUND_POINT_Y_OFFSET = 0xC,//地面物品Y坐标偏移
	GROUND_POINT_Z_OFFSET = 0x10,//地面物品Z坐标偏移
	GROUND_NAME_OFFSET = 0x5C,//地面物品名称偏移
	GROUND_TREE_FLAG_OFFSET = 0xD//二叉标识偏移
};


class CCGroundInfo
{
private:
	int TREE_ADDR;//树地址
	int GROUND_ID;//地面物品ID
	int GROUND_OBJECT_ADDR;//地面物品对象地址
	int GROUND_POINT_X;//地面物品X坐标
	int GROUND_POINT_Y;//地面物品Y坐标
	int GROUND_POINT_Z;//地面物品Z坐标
	string GROUND_NAME;//地面物品名称
	int TREE_FLAG;//地面物品二叉标识
public:
	CCGroundInfo(void);
	CCGroundInfo(int addr);
	~CCGroundInfo(void);
	//内联
	//获取Tree地址
	int getTreeAddr()
	{
		return TREE_ADDR;
	}
	//获取Object地址
	int getObjectAddr()
	{
		return GROUND_OBJECT_ADDR;
	}
	//获取Flag
	int getTreeFlag()
	{
		TREE_FLAG = 0;
		__TRY
			if(TREE_ADDR && IsReadAddrInt((PVOID)TREE_ADDR))
			{
				TREE_FLAG = *(BYTE *)(TREE_ADDR + GROUND_TREE_FLAG_OFFSET);
			}
			__CATCH("获取二叉树标识出错!")
				return TREE_FLAG;
	}
	//获取地面物品ID
	int getGroundGoodID()
	{
		GROUND_ID = 0;
		__TRY
			if(TREE_ADDR && IsReadAddrInt((PVOID)TREE_ADDR))
			{
				GROUND_ID = *(int *)(TREE_ADDR + GROUND_ID_OFFSET);
			}
			__CATCH("获取怪物对象ID出错!")
				return GROUND_ID;
	}
	//获取地面物品坐标X
	int getGroundGoodX()
	{
		GROUND_POINT_X = 0;
		__TRY
			if(GROUND_OBJECT_ADDR && IsReadAddrInt((PVOID)GROUND_OBJECT_ADDR))
			{
				GROUND_POINT_X = *(int *)(GROUND_OBJECT_ADDR + GROUND_POINT_X_OFFSET);
			}
			__CATCH("获取地面物品坐标X出错!")
				return GROUND_POINT_X;
	}
	//获取地面物品坐标Y
	int getGroundGoodY()
	{
		GROUND_POINT_Y = 0;
		__TRY
			if(GROUND_OBJECT_ADDR && IsReadAddrInt((PVOID)GROUND_OBJECT_ADDR))
			{
				GROUND_POINT_Y = *(int *)(GROUND_OBJECT_ADDR + GROUND_POINT_Y_OFFSET);
			}
			__CATCH("获取地面物品坐标Y出错!")
				return GROUND_POINT_Y;
	}
	//获取地面物品坐标Z
	int getGroundGoodZ()
	{
		GROUND_POINT_Z = 0;
		__TRY
			if(GROUND_OBJECT_ADDR && IsReadAddrInt((PVOID)GROUND_OBJECT_ADDR))
			{
				GROUND_POINT_Z = *(int *)(GROUND_OBJECT_ADDR + GROUND_POINT_Z_OFFSET);
			}
			__CATCH("获取地面物品坐标Z出错!")
				return GROUND_POINT_Z;
	}
	//获取地面物品距离
	int getGroundDsc()
	{
		int DESC = 9999;
		__TRY
		CCUserInfo _CCUserInfo;
		int GroundPX = getGroundGoodX();
		int GroundPY = getGroundGoodY();
		int RoleX = _CCUserInfo.getObjectPointX();
		int RoleY = _CCUserInfo.getObjectPointY();
		DESC = (int)sqrt((GroundPX - RoleX)*(GroundPX-RoleX)+ (GroundPY - RoleY)*(GroundPY-RoleY));
		__CATCH("获取地面物品距离出错!")
			return DESC;
	}
	//获取地面物品名称
	const char * getGroundName()
	{
		GROUND_NAME = "";
		__TRY
			if(GROUND_OBJECT_ADDR && IsReadAddrInt((PVOID)GROUND_OBJECT_ADDR))
			{
				char GroundName[255] = {0};
				strcpy_s(GroundName,(char *)(GROUND_OBJECT_ADDR + GROUND_NAME_OFFSET));
				char * U2GStr =  U2G(GroundName);
				memset(GroundName,0,255);
				strcpy_s(GroundName,U2GStr);
				if(U2GStr) delete[] U2GStr;
				GROUND_NAME = GroundName;
			}
		__CATCH("获取地面物品名称出错!")
		return GROUND_NAME.c_str();
	}
};

//lua 封装类
class RgisterGroundInfo
{
public:
	//注册构造函数  
	static int CreateClass(lua_State* L)  
	{  
		//取出构造函数参数  
		int nValue = (int)lua_tointeger(L,1);
		//这里注册无参数的构造函数就好了，直接赋值，全都赋值了
		*(CCGroundInfo**)lua_newuserdata(L,sizeof(CCGroundInfo*)) = new CCGroundInfo(nValue);
		luaL_getmetatable(L, "CCGroundInfo"); 
		lua_setmetatable(L,-2);
		return 1;  
	}
	//////////////////////////////////////////////////////////////////////////
	//注册函数
	//释放
	static int DestoryClass(lua_State* L)  
	{  
		//释放对象  
		delete *(CCGroundInfo**)lua_topointer(L,1);  
		return 0;  
	}
	//获取对象地址
	static int CallgetObjectAddr(lua_State* L)  
	{ 
		CCGroundInfo** pT = (CCGroundInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getObjectAddr());
		return 1;  
	}
	//获取X坐标
	//获取对象ID
	static int CallGetGroundGoodID(lua_State* L)  
	{ 
		CCGroundInfo** pT = (CCGroundInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getGroundGoodID());
		return 1;  
	}
	//获取X坐标
	static int CallGetGroundGoodX(lua_State* L)  
	{ 
		CCGroundInfo** pT = (CCGroundInfo**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getGroundGoodX());
		return 1;  
	}
	//获取Y坐标
	static int CallGetGroundGoodY(lua_State* L)  
	{ 
		CCGroundInfo** pT = (CCGroundInfo**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getGroundGoodY());
		return 1;  
	}
	//获取Z坐标
	static int CallGetGroundGoodZ(lua_State* L)  
	{ 
		CCGroundInfo** pT = (CCGroundInfo**)lua_topointer(L,1);  
		lua_pushnumber(L, (*pT)->getGroundGoodZ());
		return 1;  
	}
	//获取距离
	static int CallGetGroundGoodDESC(lua_State* L)  
	{ 
		CCGroundInfo** pT = (CCGroundInfo**)lua_topointer(L,1);
		lua_pushnumber(L, (*pT)->getGroundDsc());
		return 1;  
	}
	//获取名称
	static int CallGetGroundGoodName(lua_State* L)  
	{  
		CCGroundInfo** pT = (CCGroundInfo**)lua_topointer(L,1);
		lua_pushstring(L, (*pT)->getGroundName());  
		return 1;
	}
	static void RegisterInterface(lua_State* L)
	{
		//往lua中注册类  
		//注册用于创建类的全局函数
		lua_pushcfunction(L,&RgisterGroundInfo::CreateClass); 
		lua_setglobal(L,"CCGroundInfo");
		luaL_newmetatable(L,"CCGroundInfo"); 

		//__gc是lua默认的清理函数  
		lua_pushstring(L,"__gc");  
		lua_pushcfunction(L,&RgisterGroundInfo::DestoryClass);  
		lua_settable(L,-3);//公共函数调用的实现就在此啊  

		lua_pushstring(L,"__index");  
		//注意这一句，其实是将__index设置成元表自己  
		lua_pushvalue(L,-2);  
		lua_settable(L,-3);  

		//放元素中增加函数,这样所有基于该元素的Table就有Add方法了  

		lua_pushstring(L,"getObjectAddr");  
		lua_pushcfunction(L,CallgetObjectAddr);  
		lua_settable(L,-3);

		lua_pushstring(L,"getGroundGoodID");  
		lua_pushcfunction(L,CallGetGroundGoodID);  
		lua_settable(L,-3);

		lua_pushstring(L,"getGroundGoodX");  
		lua_pushcfunction(L,CallGetGroundGoodX);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getGroundGoodY");  
		lua_pushcfunction(L,CallGetGroundGoodY);  
		lua_settable(L,-3);  

		lua_pushstring(L,"getGroundGoodZ");  
		lua_pushcfunction(L,CallGetGroundGoodZ);
		lua_settable(L,-3);

		lua_pushstring(L,"getGroundDsc");  
		lua_pushcfunction(L,CallGetGroundGoodDESC);
		lua_settable(L,-3);

		lua_pushstring(L,"getGroundName");  
		lua_pushcfunction(L,CallGetGroundGoodName);
		lua_settable(L,-3);
		lua_pop(L,1);
	}
};