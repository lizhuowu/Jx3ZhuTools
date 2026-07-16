#include "stdafx.h"
#include "CLua.h"


CCLua::CCLua(void)
{
	LuaInit();
}


CCLua::~CCLua(void)
{
}
void CCLua::LuaInit()
{
	//_lua_Status = luaL_newstate();
	_lua_Status = luaL_newstate();
	//luaL_openlibs(_lua_Status);//打开一些lua 的库文件
	luaopen_string(_lua_Status);

	luaL_openlibs(_lua_Status); 
	luaopen_base(_lua_Status);

	Lua_RegisterFun();
	LuaRegisterClass();
}
//LUA 注册类
void CCLua::LuaRegisterClass()
{
	RgisterCCUserInfo::RegisterInterface(_lua_Status);
	RegisterCCTest::RegisterInterface(_lua_Status);
	RgisterMonsterInformation::RegisterInterface(_lua_Status);
	RgisterMonsterTree::RegisterInterface(_lua_Status);
	RgisterGroundInfo::RegisterInterface(_lua_Status);
	RgisterCCGroundTree::RegisterInterface(_lua_Status);
	RgisterCCPickupInfo::RegisterInterface(_lua_Status);
	RgisterCCDoodPickups::RegisterInterface(_lua_Status);
	RgisterCCTaskHasIDs::RegisterInterface(_lua_Status);
	RgisterCCTaskJujmentObject::RegisterInterface(_lua_Status);
	RgisterCCTaskJujimentArray::RegisterInterface(_lua_Status);
	RgisterCCAllTaskTree::RegisterInterface(_lua_Status);
	RgisterCCAllTaskObject::RegisterInterface(_lua_Status);
	RgisterCCShopTreeObject::RegisterInterface(_lua_Status);
	RgisterCCShopTree::RegisterInterface(_lua_Status);
	RgisterCCShopGoodObject::RegisterInterface(_lua_Status);
	RgisterCCShopGoodArray::RegisterInterface(_lua_Status);
	RgisterCCShopGoodPriceTree::RegisterInterface(_lua_Status);
	RgisterCCShopGoodPriceObject::RegisterInterface(_lua_Status);
	RgisterCCPackPercelArray::RegisterInterface(_lua_Status);
	RgisterCCPackArray::RegisterInterface(_lua_Status);
	RgisterCCPackObject::RegisterInterface(_lua_Status);
	RgisterCCPlayerTree::RegisterInterface(_lua_Status);
	RgisterCCPlayerInfomation::RegisterInterface(_lua_Status);
	RgisterSkillTree::RegisterInterface(_lua_Status);
	RgisterCCSkillObject::RegisterInterface(_lua_Status);
	RgisterCCSkillXiuWeiTree::RegisterInterface(_lua_Status);
	RgisterCCSkillXiuWeiObject::RegisterInterface(_lua_Status);
}

void CCLua::Lua_RegisterFun()
{
	lua_register(_lua_Status,"输出信息",LuaPrint);
	lua_register(_lua_Status,"超级延时",LuaSleep);
	lua_register(_lua_Status,"取当前血",LuaGetUserBlood);
	lua_register(_lua_Status,"取血百分比",LuaGetUserBloodPercent);
	lua_register(_lua_Status,"取等级",LuaGetUserLevel);
	lua_register(_lua_Status,"取角色X坐标",LuaGetUserX);
	lua_register(_lua_Status,"取角色Y坐标",LuaGetUserY);
	lua_register(_lua_Status,"堵塞寻路",LuaMoveTo);
	lua_register(_lua_Status,"寻路",LuaMove);
	lua_register(_lua_Status,"取运行目录",LuaGetRootPath);
	lua_register(_lua_Status,"选怪",LuaSelectMonster);
	lua_register(_lua_Status,"使用技能",LuaSkill);
	lua_register(_lua_Status,"采集",LuaAcquitst);
	lua_register(_lua_Status,"拾取物品",LuaPickUpGood);
	lua_register(_lua_Status,"接任务",LuaAccpetTask);
	lua_register(_lua_Status,"交任务",LuaFinshTask);
	lua_register(_lua_Status,"打开NPC",LuaOpenNPC);
	lua_register(_lua_Status,"买物品",LuaBuyGood);
	lua_register(_lua_Status,"打开商店",LuaOpenShop);
	lua_register(_lua_Status,"取商品编号",LuaGetShopIndex);
	lua_register(_lua_Status,"任务二级对话",LuaNpcTaskSubTalk);
	lua_register(_lua_Status,"使用物品",LuaUseGood);
	lua_register(_lua_Status,"穿戴物品",LuaWearGood);
	lua_register(_lua_Status,"装备马匹",LuaWearHorse);
	lua_register(_lua_Status,"拾取金币",LuaPickGlod);
	lua_register(_lua_Status,"人物起跳",LuaRoleJmp);
	lua_register(_lua_Status,"人物轻功",LuaRoleDodge);
	lua_register(_lua_Status,"取消打坐",LuaCancelSetDwon);
	lua_register(_lua_Status,"按键按下F",LuaKey_F_DownCall);
	lua_register(_lua_Status,"按键抬起F",LuaKey_F_UpCall);
	lua_register(_lua_Status,"按键按下ESC",LuaKey_ESC_DownCall);
	lua_register(_lua_Status,"按键抬起ESC",LuaKey_ESC_UpCall);
	lua_register(_lua_Status,"按键按下SPACE",LuaKey_SPACE_DownCall);
	lua_register(_lua_Status,"按键抬起SPACE",LuaKey_SPACE_UpCall);
	lua_register(_lua_Status,"取转向角度",LuaGetTran);
	lua_register(_lua_Status,"转向",LuaTranCall);
	lua_register(_lua_Status,"销毁物品",LuDistoryCall);
	lua_register(_lua_Status,"退出组队",LuaQuitTeam);
	lua_register(_lua_Status,"发起组队",LuaRequsetTeam);
	lua_register(_lua_Status,"接受组队",LuaRsponseTeam);
	lua_register(_lua_Status,"接受最新组队",LuaRsponseNewTeam);
	lua_register(_lua_Status,"图内马车",LuaMapInRunTo);
	lua_register(_lua_Status,"切换内功",LuaChangeKungFu);
	lua_register(_lua_Status,"交互",LuaInterActive);
	lua_register(_lua_Status,"修理全部装备",LuaRepairWear);
	lua_register(_lua_Status,"技能升级",LuaSkillLevelUp);
	lua_register(_lua_Status,"定点释放技能",LuaSkillMakePoint);
	lua_register(_lua_Status,"奇穴设置",LuaSpecilSet);
	lua_register(_lua_Status,"机关任务",LuaOrganMove);
	lua_register(_lua_Status,"取消息文本",LuaGetHookTxt);
	lua_register(_lua_Status,"怪物视野值",LuaMonsterView);
	lua_register(_lua_Status,"取对象类型",LuaObjectType);
	lua_register(_lua_Status,"取千机地址",LuaGetThousands);
	lua_register(_lua_Status,"装备千机装备",LuaWearThousands);
	lua_register(_lua_Status,"放弃任务",LuaDelTask);
	lua_register(_lua_Status,"神行千里",LuaShenXingQianLi);
	lua_register(_lua_Status,"取商店地址DLL",LuaGetShopAddr);
	lua_register(_lua_Status,"使用礼包",LuaUsePacket);
	lua_register(_lua_Status,"获取物品价格",LuaGetGoodPrice);
	lua_register(_lua_Status,"卖物品",LuaSellGood);
	lua_register(_lua_Status,"交任务选物品",LuaFinshTaskEx);
	lua_register(_lua_Status,"刷木童",LuaShuMuTong);
	lua_register(_lua_Status,"登高",LuaDengGao);
	lua_register(_lua_Status,"过图",LuaPassMap);
}
//执行脚本
void CCLua::Lua_DoFile(CString luaScriptPath)
{
	luaL_dofile(_lua_Status,luaScriptPath.GetBuffer());
}

//日志消息
int CCLua::LuaPrint(lua_State *L)
{
	int inNumber = lua_gettop(L);
	if (inNumber == 1) {
		const char *msgContent = lua_tostring(L,1);
		OutputDebugString(msgContent);
	}
	return 0;
}
//延时
int CCLua::LuaSleep(lua_State *L)
{
	int inNumber = lua_gettop(L);
	if (inNumber == 1) {
		int numSleep = (int)lua_tointeger(L,1);
		Sleep(numSleep);
	}
	return 0;
}
//获取人物血
int CCLua::LuaGetUserBlood(lua_State *L)
{
	CCUserInfo _CCUserInfo;
	lua_pushnumber(L,_CCUserInfo.getObjectCurrentBlood());
	return 1;
}
//获取人物血百分比
int CCLua::LuaGetUserBloodPercent(lua_State *L)
{
	CCUserInfo _CCUserInfo;
	lua_pushnumber(L,_CCUserInfo.getObjectBloodPercent());
	return 1;
}
//获取人物等级
int CCLua::LuaGetUserLevel(lua_State *L)
{
	CCUserInfo _CCUserInfo;
	lua_pushnumber(L,_CCUserInfo.getObjectLevel());
	return 1;
}
//取人物X坐标
int CCLua::LuaGetUserX(lua_State *L)
{
	CCUserInfo _CCUserInfo;
	lua_pushnumber(L,_CCUserInfo.getObjectPointX());
	return 1;
}
//取人物Y坐标
int CCLua::LuaGetUserY(lua_State *L)
{
	CCUserInfo _CCUserInfo;
	lua_pushnumber(L,_CCUserInfo.getObjectPointY());
	return 1;
}
//获取运行根目录
int CCLua::LuaGetRootPath(lua_State *L)
{
	CCCommon  _CCCommon;
	lua_pushstring(L,_CCCommon.GetLuaRootPath().GetBuffer());
	return 1;
}
//获取HOOK到的文本
int CCLua::LuaGetHookTxt(lua_State *L)
{
	lua_pushstring(L,HOOKText.c_str());
	return 1;
}
//堵塞寻路
int CCLua::LuaMoveTo(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm==2)
	{
		int MoveToX = (int)lua_tointeger(L, 1);
		int MoveToY = (int)lua_tointeger(L, 2);
		CCCommon _CCCommon;
		_CCCommon.MoveTo(MoveToX,MoveToY);
	}else
	{
		OutputDebugString("寻路参数出错!");
	}
	return 0;
}
//非堵塞寻路
int CCLua::LuaMove(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm==2)
	{
		int MoveToX = (int)lua_tointeger(L, 1);
		int MoveToY = (int)lua_tointeger(L, 2);
		MOTO moto;
		moto.fMoveToX = (float)MoveToX;
		moto.fMoveToY = (float)MoveToY;
		moto.MoveToZ = 0;
		SendMessageA (g_hGameHandle,MOVETO, 0, (LPARAM)&moto);
	}else
	{
		OutputDebugString("寻路参数出错!");
	}
	return 0;
}
//选怪
int CCLua::LuaSelectMonster(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm==1)
	{
		int MonsterID = (int)lua_tointeger(L, 1);
		if(MonsterID > 0)
		{
			SendMessageA (g_hGameHandle,SELECT_MONSTER, 0, (LPARAM)MonsterID);
		}else
		{
			OutputDebugString("选怪出错,怪物ID非法!");
		}
		
	}else
	{
		OutputDebugString("选怪出错!");
	}
	return 0;
}

//使用技能
int CCLua::LuaSkill(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm==2)
	{
		int SkillID = (int)lua_tointeger(L, 1);
		int SkillLevel = (int)lua_tointeger(L, 2);
		if(SkillID > 0 && SkillLevel > 0)
		{
			AL_STRUCT _AL_STRUCT;
			_AL_STRUCT.Param1 = SkillID;
			_AL_STRUCT.Param2 = SkillLevel;
			SendMessageA (g_hGameHandle,SKILL, 0, (LPARAM)&_AL_STRUCT);
		}else
		{
			OutputDebugString("使用技能出错，技能ID非法!");
		}
	}else
	{
		OutputDebugString("使用技能出错!");
	}
	return 0;
}
//采集
int CCLua::LuaAcquitst(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm==1)
	{
		int DoorID = (int)lua_tointeger(L, 1);
		if(DoorID > 0)
		{
			SendMessageA (g_hGameHandle,ACQUITST, 0, (LPARAM)DoorID);
		}else
		{
			OutputDebugString("采集出错,ID非法!");
		}

	}else
	{
		OutputDebugString("采集出错!");
	}
	return 0;
}
//拾取物品
int CCLua::LuaPickUpGood(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm==2)
	{
		int pickID = (int)lua_tointeger(L, 1);//包裹ID
		int pickUpGoodID = (int)lua_tointeger(L, 2);//拾取对象的ID
		if(pickID > 0 && pickUpGoodID > 0 )
		{
			PickCall_Struct _pickUpGoodID;
			_pickUpGoodID.pickID = pickID;
			_pickUpGoodID.pickUpGoodID = pickUpGoodID;
			SendMessageA (g_hGameHandle,PICKUPGOOD, 0, (LPARAM)&_pickUpGoodID);
		}else
		{
			OutputDebugString("拾取出错,ID非法!");
		}

	}else
	{
		OutputDebugString("拾取出错!");
	}
	return 0;
}
//封包接任务
int CCLua::LuaAccpetTask(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 2)
	{
		int TaskId = (int)lua_tointeger(L, 1);//任务ID
		int NpcId = (int)lua_tointeger(L, 2);//NPCID
		if(TaskId > 0 && NpcId > 0)
		{
			AL_STRUCT _AL_STRUCT;
			_AL_STRUCT.Param1 = TaskId;
			_AL_STRUCT.Param2 = NpcId;
			SendMessageA (g_hGameHandle,ACCPET_TASK_BUFFER, 0, (LPARAM)&_AL_STRUCT);
		}else
		{
			OutputDebugString("封包接任务出错!");
		}
	}else
	{
		OutputDebugString("封包接任务出错,ID非法!");
	}
	return 0;
}
//封包交任务
int CCLua::LuaFinshTask(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 2)
	{
		int TaskId = (int)lua_tointeger(L, 1);//任务ID
		int NpcId = (int)lua_tointeger(L, 2);//NPCID
		if(TaskId > 0 && NpcId > 0)
		{
			AL_STRUCT _AL_STRUCT;
			_AL_STRUCT.Param1 = TaskId;
			_AL_STRUCT.Param2 = NpcId;
			SendMessageA (g_hGameHandle,FINSH_TASK_BUFFER, 0, (LPARAM)&_AL_STRUCT);
		}else
		{
			OutputDebugString("封包交任务出错!");
		}
	}else
	{
		OutputDebugString("封包交任务出错,ID非法!");
	}
	return 0;
}
//封包交任务,选物品
int CCLua::LuaFinshTaskEx(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 3)
	{
		int TaskId = (int)lua_tointeger(L, 1);//任务ID
		int NpcId = (int)lua_tointeger(L, 2);//NPCID
		int SelectIndex = (int)lua_tointeger(L, 3);//NPCID
		if(TaskId > 0 && NpcId > 0)
		{
			AL_STRUCT_THREAD _AL_STRUCT_THREAD;
			_AL_STRUCT_THREAD.Param1 = TaskId;
			_AL_STRUCT_THREAD.Param2 = NpcId;
			_AL_STRUCT_THREAD.Param3 = SelectIndex;
			SendMessageA (g_hGameHandle,FINSH_TASK_BUFFER_EX, 0, (LPARAM)&_AL_STRUCT_THREAD);
		}else
		{
			OutputDebugString("封包交任务出错!");
		}
	}else
	{
		OutputDebugString("封包交任务出错,ID非法!");
	}
	return 0;
}
//打开NPC
int CCLua::LuaOpenNPC(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		int NpcId = (int)lua_tointeger(L,1);//NPCID
		if(NpcId > 0)
		{
			
			SendMessageA (g_hGameHandle,OPEN_NPC, 0, (LPARAM)NpcId);
		}else
		{
			OutputDebugString("打开NPC出错!");
		}
	}else
	{
		OutputDebugString("打开NPC出错,ID非法!");
	}
	return 0;
}
//买物品
int CCLua::LuaBuyGood(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 5)
	{
		int price = (int)lua_tointeger(L,1);
		int countBuy = (int)lua_tointeger(L,2);
		int GoodID = (int)lua_tointeger(L,3);
		int GoodIndex = (int)lua_tointeger(L,4);
		int ShopIndex = (int)lua_tointeger(L,5);
		Buy_Good_Struct _Buy_Good_Struct;
		_Buy_Good_Struct.Count = countBuy;
		_Buy_Good_Struct.Price = price;
		_Buy_Good_Struct.Good_Index = GoodIndex;
		_Buy_Good_Struct.GoodID = GoodID;
		_Buy_Good_Struct.Shop_Index = ShopIndex;
		SendMessageA (g_hGameHandle,BUY_GOOD, 0, (LPARAM)&_Buy_Good_Struct);
	}else
	{
		OutputDebugString("买物品出错,参数非法!");
	}
	return 0;
}
//打开商店
int CCLua::LuaOpenShop(lua_State *L)
{
	int shopNum =0;
	SendMessageA (g_hGameHandle,OPEN_SHOP, 0, (LPARAM)shopNum);
	return 0;
}
//获取HOOK到的商店编号
int CCLua::LuaGetShopIndex(lua_State *L)
{
	int SHOP_NUM = -1;
	int iPos = 0, iPos2 = 0;
	iPos = HOOKText.find ("M ");
	iPos2 = HOOKText.find (" ", iPos + 2);
	string currentStr = HOOKText.substr (iPos + 2, iPos2 - (iPos + 2));
	SHOP_NUM = _ttoi(currentStr.c_str());
	lua_pushnumber(L,SHOP_NUM);
	return 1;
}
//任务二级对话
int CCLua::LuaNpcTaskSubTalk(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		int talkID =TALK_ID;
		int talkIndex = (int)lua_tointeger(L, 1);//对话索引
		AL_STRUCT _AL_STRUCT;
		_AL_STRUCT.Param1 = talkIndex;
		_AL_STRUCT.Param2 = talkID;
		SendMessageA (g_hGameHandle,NPC_TASK_TALK_SUB, 0, (LPARAM)&_AL_STRUCT);
	}
	
	return 0;
}
//使用物品
int CCLua::LuaUseGood(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 2)
	{
		int percelIndex = (int)lua_tointeger(L,1);//包裹索引
		int packIndex = (int)lua_tointeger(L,2);//格子索引
		struct USE_GOOD_PARAM_STRUCT _USE_GOOD_PARAM_STRUCT;
		_USE_GOOD_PARAM_STRUCT.PercelIndex = percelIndex;
		_USE_GOOD_PARAM_STRUCT.PackIndex = packIndex;
		SendMessageA (g_hGameHandle,USE_GOOD, 0, (LPARAM)&_USE_GOOD_PARAM_STRUCT);
	}else
	{
		OutputDebugString("使用物品出错,参数非法!");
	}
	return 0;
}
//穿戴物品
int CCLua::LuaWearGood(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 3)
	{
		int wearIndex =  (int)lua_tointeger(L,1);//穿戴位置
		int percelIndex = (int)lua_tointeger(L,2);//包裹索引
		int packIndex = (int)lua_tointeger(L,3);//格子索引
		struct USE_GOOD_PARAM_STRUCT _USE_GOOD_PARAM_STRUCT;
		_USE_GOOD_PARAM_STRUCT.GoodID = wearIndex;
		_USE_GOOD_PARAM_STRUCT.PercelIndex = percelIndex;
		_USE_GOOD_PARAM_STRUCT.PackIndex = packIndex;
		SendMessageA (g_hGameHandle,WEAR_GOOD, 0, (LPARAM)&_USE_GOOD_PARAM_STRUCT);
	}else
	{
		OutputDebugString("穿戴物品出错,参数非法!");
	}
	return 0;
}
//穿戴马匹
int CCLua::LuaWearHorse(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 3)
	{
		int wearIndex =  (int)lua_tointeger(L,1);//穿戴位置
		int percelIndex = (int)lua_tointeger(L,2);//包裹索引
		int packIndex = (int)lua_tointeger(L,3);//格子索引
		struct USE_GOOD_PARAM_STRUCT _USE_GOOD_PARAM_STRUCT;
		_USE_GOOD_PARAM_STRUCT.GoodID = wearIndex;
		_USE_GOOD_PARAM_STRUCT.PercelIndex = percelIndex;
		_USE_GOOD_PARAM_STRUCT.PackIndex = packIndex;
		SendMessageA (g_hGameHandle,WEAR_HORSE, 0, (LPARAM)&_USE_GOOD_PARAM_STRUCT);
	}else
	{
		OutputDebugString("使用马匹出错,参数非法!");
	}
	return 0;
}
//拾取金币
int CCLua::LuaPickGlod(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		int pickID =  (int)lua_tointeger(L,1);//拾取ID
		SendMessageA (g_hGameHandle,PICKUPGLOD, 0, (LPARAM)pickID);
	}else
	{
		OutputDebugString("拾取金币出错,参数非法!");
	}
	return 0;
}
//跳CALL
int CCLua::LuaRoleJmp(lua_State *L)
{
	SendMessageA (g_hGameHandle,ROLEJMP, 0, (LPARAM)0);
	return 0;
}
//轻功
int CCLua::LuaRoleDodge(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		int OffOrOn =  (int)lua_tointeger(L,1);//开/关
		SendMessageA (g_hGameHandle,ROLEDODGE, 0, (LPARAM)OffOrOn);
	}else
	{
		OutputDebugString("使用轻功出错,参数非法!");
	}
	return 0;
}
//取消打坐
int CCLua::LuaCancelSetDwon(lua_State *L)
{
	SendMessageA (g_hGameHandle,CANCEL_SET_DOWN, 0, (LPARAM)0);
	return 0;
}
//按键CALL
int CCLua::LuaKey_F_DownCall(lua_State *L)
{
	SendMessageA (g_hGameHandle,KEY_ACTION_F_DOWN, 0, (LPARAM)0);
	return 0;
}
//按键CALL
int CCLua::LuaKey_F_UpCall(lua_State *L)
{
	SendMessageA (g_hGameHandle,KEY_ACTION_F_UP, 0, (LPARAM)0);
	return 0;
}

//按键CALL
int CCLua::LuaKey_ESC_DownCall(lua_State *L)
{
	SendMessageA (g_hGameHandle,KEY_ACTION_ESC_DOWN, 0, (LPARAM)0);
	return 0;
}
//按键CALL
int CCLua::LuaKey_ESC_UpCall(lua_State *L)
{
	SendMessageA (g_hGameHandle,KEY_ACTION_ESC_UP, 0, (LPARAM)0);
	return 0;
}

//按键CALL
int CCLua::LuaKey_SPACE_DownCall(lua_State *L)
{
	SendMessageA (g_hGameHandle,KEY_ACTION_SPACE_DOWN, 0, (LPARAM)0);
	return 0;
}
//按键CALL
int CCLua::LuaKey_SPACE_UpCall(lua_State *L)
{
	SendMessageA (g_hGameHandle,KEY_ACTION_SPACE_UP, 0, (LPARAM)0);
	return 0;
}

//获取转向角度
int CCLua::LuaGetTran(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 2)
	{
		double retTran = 0;
		double OtherX2 = lua_tonumber(L,1);//X
		double OtherY2 = lua_tonumber(L,2);//Y
		CCUserInfo _CCUserInfo;
		double RoleX1 = _CCUserInfo.getObjectPointX() * 1.0;
		double RoleY1 = _CCUserInfo.getObjectPointY() * 1.0;
		if(OtherX2 > RoleX1 && OtherY2 > RoleY1){//第一象限 
			OutputDebugString("第一象限");
			retTran = atan((OtherX2-RoleX1)/(OtherY2-RoleY1)); 
		} 
		if(OtherX2 < RoleX1 && OtherY2 > RoleY1){//第二象限 
			OutputDebugString("第二象限");
			retTran = (2*3.1415926535897932384-atan((RoleX1-OtherX2)/(OtherY2-RoleY1))); 
		} 
		if(OtherX2 < RoleX1 && OtherY2 < RoleY1){//第三象限 
			OutputDebugString("第三象限");
			retTran = (3*3.1415926535897932384/2-atan((RoleY1-OtherY2)/(RoleX1-OtherX2))); 
		} 
		if(OtherX2 > RoleX1 && OtherY2 < RoleY1){//第四象限 
			OutputDebugString("第四象限");
			retTran = (3.1415926535897932384-atan((OtherX2-RoleX1)/(RoleY1-OtherY2))); 
		} 
		if(OtherX2 > RoleX1 && OtherY2 == RoleY1){//X轴正方向 
			OutputDebugString("X轴正方向");
			retTran = 3.1415926535897932384/2; 
		} 
		if(OtherX2 < RoleX1 && OtherY2 == RoleY1){//X轴负方向 
			OutputDebugString("X轴负方向");
			retTran = 3.1415926535897932384*3/2; 
		} 
		if(OtherX2 == RoleX1 && OtherY2 > RoleY1){//Y轴正方向
			OutputDebugString("Y轴正方向");
			retTran = 0; 
		} 
		if(OtherX2 == RoleX1 && OtherY2 < RoleY1){//Y轴负方向 
			OutputDebugString("Y轴负方向");
			retTran = 3.1415926535897932384; 
		} 
		if(OtherX2 == RoleX1 && OtherY2 == RoleY1){//原点 
			OutputDebugString("原点");
			retTran = 0; 
		} 
		lua_pushnumber(L,retTran);
	}else
	{
		OutputDebugString("获取转向角度非法!");
	}
	return 1;
}

//转向CALL
int CCLua::LuaTranCall(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		double KeyValue =  lua_tonumber(L,1);//转向角度
		double *pointDouble = &KeyValue;
		SendMessageA (g_hGameHandle,TRAN_ACTION, 0, (LPARAM)pointDouble);
	}else
	{
		OutputDebugString("转向出错,参数非法!");
	}
	return 0;
}

//销毁物品
int CCLua::LuDistoryCall(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 2)
	{
		int percelIndex = (int)lua_tointeger(L, 1);//包裹
		int packIndex = (int)lua_tointeger(L, 2);//格子
		if(percelIndex >= 0 && packIndex >= 0)
		{
			AL_STRUCT _AL_STRUCT;
			_AL_STRUCT.Param1 = packIndex;
			_AL_STRUCT.Param2 = percelIndex;
			SendMessageA (g_hGameHandle,DISTORY_GOOD, 0, (LPARAM)&_AL_STRUCT);
		}else
		{
			OutputDebugString("销毁物品出错!");
		}
	}else
	{
		OutputDebugString("销毁物品出错,ID非法!");
	}
	return 0;
}
//退出组队
int CCLua::LuaQuitTeam(lua_State *L)
{
	SendMessageA (g_hGameHandle,QUIT_TEAM_MESSAGE, 0, (LPARAM)0);
	return 0;
}

//发起组队
int CCLua::LuaRequsetTeam(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		const char* PlayName= lua_tostring(L,1);//传进的参数
		struct REQUEST_TETHER_TEAM __REQUEST_TETHER_TEAM = {0};
		strcpy_s(__REQUEST_TETHER_TEAM.PlayName,PlayName);
		SendMessageA (g_hGameHandle,REQUEST_TEAM_MESSAGE, 0, (LPARAM)&__REQUEST_TETHER_TEAM);
	}else
	{
		OutputDebugString("发起组队,参数非法!");
	}
	return 0 ;
}
//接受组队
int CCLua::LuaRsponseTeam(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		const char* PlayName= lua_tostring(L,1);//传进的参数
		struct RESPONE_TETHER_TEAM __RESPONE_TETHER_TEAM = {0};
		strcpy_s(__RESPONE_TETHER_TEAM.PlayName,PlayName);
		SendMessageA (g_hGameHandle,RESPONSE_TEAM_MESSAGE, 0, (LPARAM)&__RESPONE_TETHER_TEAM);
	}else
	{
		OutputDebugString("接受组队,参数非法!");
	}
	return 0 ;
}
//接受最新组队
int CCLua::LuaRsponseNewTeam(lua_State *L)
{
	CCControlResponseTeam _CCControlResponseTeam;
	_CCControlResponseTeam.GetLastTeamerAndResponse();
	return 0 ;
}
//图内马车
int CCLua::LuaMapInRunTo(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 3)
	{
		int Param1 = (int)lua_tointeger(L, 1);//参数1
		int Param2 = (int)lua_tointeger(L, 2);//参数2
		int Param3 = (int)lua_tointeger(L, 3);//参数3
		AL_STRUCT_THREAD __AL_STRUCT_THREAD = {0};
		__AL_STRUCT_THREAD.Param1 = Param1;
		__AL_STRUCT_THREAD.Param2 = Param2;
		__AL_STRUCT_THREAD.Param3 = Param3;
		SendMessageA (g_hGameHandle,MAP_IN_RUN_TO, 0, (LPARAM)&__AL_STRUCT_THREAD);
	}else
	{
		OutputDebugString("图内马车,参数非法!");
	}
	return 0 ;
}
//切换内功
int CCLua::LuaChangeKungFu(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		int KungFuID = (int)lua_tointeger(L, 1);
		SendMessageA (g_hGameHandle,CHANGE_KUNG_FU, 0, (LPARAM)KungFuID);
	}else
	{
		OutputDebugString("切换内功,参数非法!");
	}
	return 0 ;
}
//交互
int CCLua::LuaInterActive(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 3)
	{
		int ActionFlag = (int)lua_tointeger(L, 1);
		int ActionFlag2 = (int)lua_tointeger(L, 2);
		const char* ActiveItem= lua_tostring(L,3);//传进的参数
		struct INTERACTIVE_STRUCT __INTERACTIVE_STRUCT = {0};
		strcpy_s(__INTERACTIVE_STRUCT.ActiveItem,ActiveItem);
		__INTERACTIVE_STRUCT.Flag = ActionFlag;
		__INTERACTIVE_STRUCT.Flag2 = ActionFlag2;
		SendMessageA (g_hGameHandle,INTERAVTIVE, 0, (LPARAM)&__INTERACTIVE_STRUCT);
	}else
	{
		OutputDebugString("交互,参数非法!");
	}
	return 0 ;
}
//修理装备
int CCLua::LuaRepairWear(lua_State *L)
{
	_CCCommon.RepairWear();
	return 0;
}

//技能升级
int CCLua::LuaSkillLevelUp(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 3)
	{
		int Param1 = (int)lua_tointeger(L, 1);//参数1
		int Param2 = (int)lua_tointeger(L, 2);//参数2
		int Param3 = (int)lua_tointeger(L, 3);//参数3
		AL_STRUCT_THREAD __AL_STRUCT_THREAD = {0};
		__AL_STRUCT_THREAD.Param1 = Param1;
		__AL_STRUCT_THREAD.Param2 = Param2;
		__AL_STRUCT_THREAD.Param3 = Param3;
		SendMessageA (g_hGameHandle,SKILL_UP_LEVEL, 0, (LPARAM)&__AL_STRUCT_THREAD);
	}else
	{
		OutputDebugString("技能升级,参数非法!");
	}
	return 0 ;
}
//定点释放技能
int CCLua::LuaSkillMakePoint(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 5)
	{
		int Param1 = (int)lua_tointeger(L, 1);//参数1
		int Param2 = (int)lua_tointeger(L, 2);//参数2
		int Param3 = (int)lua_tointeger(L, 3);//参数3
		int Param4 = (int)lua_tointeger(L, 4);//参数4
		int Param5 = (int)lua_tointeger(L, 5);//参数5
		AL_STRUCT_FIVE __AL_STRUCT_FIVE = {0};
		__AL_STRUCT_FIVE.Param1 = Param1;
		__AL_STRUCT_FIVE.Param2 = Param2;
		__AL_STRUCT_FIVE.Param3 = Param3;
		__AL_STRUCT_FIVE.Param4 = Param4;
		__AL_STRUCT_FIVE.Param5 = Param5;
		SendMessageA (g_hGameHandle,SKILL_MAKE_POINT, 0, (LPARAM)&__AL_STRUCT_FIVE);
	}else
	{
		OutputDebugString("定点释放技能,参数非法!");
	}
	return 0 ;
}
//奇穴设置
int CCLua::LuaSpecilSet(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 2)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		int Param2 = (int)lua_tointeger(L, 2);
		AL_STRUCT _AL_STRUCT;
		_AL_STRUCT.Param1 = Param1;
		_AL_STRUCT.Param2 = Param2;
		SendMessageA (g_hGameHandle,SPECIL_SET, 0, (LPARAM)&_AL_STRUCT);
	}else
	{
		OutputDebugString("奇穴设置,ID非法!");
	}
	return 0;
}
//机关任务
int CCLua::LuaOrganMove(lua_State *L)
{
	_CCCommon.OrganMoveSucess();
	return 0;
}
//怪物视野
int CCLua::LuaMonsterView(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 3)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		int Param2 = (int)lua_tointeger(L, 2);
		int Param3 = (int)lua_tointeger(L, 3);
		AL_STRUCT_FOUR _AL_STRUCT_FOUR;
		_AL_STRUCT_FOUR.Param1 = Param1;
		_AL_STRUCT_FOUR.Param2 = Param2;
		_AL_STRUCT_FOUR.Param3 = Param3;
		_AL_STRUCT_FOUR.Param4 = 1;
		SendMessageA (g_hGameHandle,MONSTER_VIEW, 0, (LPARAM)&_AL_STRUCT_FOUR);
		lua_pushnumber(L,_AL_STRUCT_FOUR.Param4);
	}else
	{
		lua_pushnumber(L,-1);
		OutputDebugString("怪物视野,ID非法!");
	}
	return 1;
}
//对象类型
int CCLua::LuaObjectType(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		AL_STRUCT _AL_STRUCT;
		_AL_STRUCT.Param1 = Param1;
		_AL_STRUCT.Param2 = 0;
		SendMessageA (g_hGameHandle,OBJECT_TYPE_RET, 0, (LPARAM)&_AL_STRUCT);
		lua_pushnumber(L,_AL_STRUCT.Param2);
	}else
	{
		lua_pushnumber(L,0);
		OutputDebugString("类型出错,ID非法!");
	}
	return 1;
}
//取千机地址
int CCLua::LuaGetThousands(lua_State *L)
{
	CCThousands _CCThousands;
	lua_pushnumber(L,_CCThousands.getAddr());
	return 1;
}
//装备千机装备
int CCLua::LuaWearThousands(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 4)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		int Param2 = (int)lua_tointeger(L, 2);
		int Param3 = (int)lua_tointeger(L, 3);
		int Param4 = (int)lua_tointeger(L, 4);
		AL_STRUCT_FOUR _AL_STRUCT_FOUR;
		_AL_STRUCT_FOUR.Param1 = Param1;
		_AL_STRUCT_FOUR.Param2 = Param2;
		_AL_STRUCT_FOUR.Param3 = Param3;
		_AL_STRUCT_FOUR.Param4 = Param4;
		SendMessageA (g_hGameHandle,WEAR_THOUSANDS, 0, (LPARAM)&_AL_STRUCT_FOUR);
	}else
	{
		OutputDebugString("装备千机物品出错,ID非法!");
	}
	return 0;
}
//放弃任务
int CCLua::LuaDelTask(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		SendMessageA (g_hGameHandle,DELETE_TASK_BUFFER, 0, (LPARAM)Param1);
	}else
	{
		OutputDebugString("放弃任务出错,ID非法!");
	}
	return 0;
}
//对象类型
int CCLua::LuaShenXingQianLi(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 2)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		int Param2 = (int)lua_tointeger(L, 2);
		AL_STRUCT _AL_STRUCT;
		_AL_STRUCT.Param1 = Param1;
		_AL_STRUCT.Param2 = Param2;
		SendMessageA (g_hGameHandle,SHEN_XING_QIN_LI, 0, (LPARAM)&_AL_STRUCT);
	}else
	{
		OutputDebugString("神行千里出错,ID非法!");
	}
	return 0;
}
//使用礼包
int CCLua::LuaUsePacket(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 2)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		int Param2 = (int)lua_tointeger(L, 2);
		AL_STRUCT _AL_STRUCT;
		_AL_STRUCT.Param1 = Param1;
		_AL_STRUCT.Param2 = Param2;
		SendMessageA (g_hGameHandle,USE_PACKET, 0, (LPARAM)&_AL_STRUCT);
	}else
	{
		OutputDebugString("使用礼包出错,ID非法!");
	}
	return 0;
}
//取商店地址
int CCLua::LuaGetShopAddr(lua_State *L)
{
	//获取打开商店的ECX
	if (HOOKText == "HOOKTEXT")
	{
		OutputDebugString("修理装备失败，请先打开NPC对话!");
		lua_pushnumber(L,0);
		return 1;
	}
	int SHOP_NUM = -1;
	int iPos = 0, iPos2 = 0;
	iPos = HOOKText.find ("M ");
	iPos2 = HOOKText.find (" ", iPos + 2);
	string currentStr = HOOKText.substr (iPos + 2, iPos2 - (iPos + 2));
	SHOP_NUM = _ttoi(currentStr.c_str());
	int _ECX = _CCCommon.GetShopAddr(SHOP_NUM);
	lua_pushnumber(L,_ECX);
	return 1;
}

//取物品价格
int CCLua::LuaGetGoodPrice(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 3)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		int Param2 = (int)lua_tointeger(L, 2);
		int Param3 = (int)lua_tointeger(L, 3);
		int price = 0;
		GET_REPIR_PRICE_STRUCT _GET_REPIR_PRICE_STRUCT;
		_GET_REPIR_PRICE_STRUCT.PercelIndex = Param1;
		_GET_REPIR_PRICE_STRUCT.PackIndex = Param2;
		_GET_REPIR_PRICE_STRUCT._Ecx = Param3;
		SendMessageA (g_hGameHandle,GET_GOOD_PRICE, 0, (LPARAM)&_GET_REPIR_PRICE_STRUCT);
		if (_GET_REPIR_PRICE_STRUCT.Price > 0)
		{
			price =  _GET_REPIR_PRICE_STRUCT.Price;
		}
		lua_pushnumber(L,price);
	}else
	{
		lua_pushnumber(L,0);
		OutputDebugString("取价格出错,ID非法!");
	}
	return 1;
}
//卖物品
int CCLua::LuaSellGood(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 4)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		int Param2 = (int)lua_tointeger(L, 2);
		int Param3 = (int)lua_tointeger(L, 3);
		int Param4 = (int)lua_tointeger(L, 4);
		AL_STRUCT_FOUR _AL_STRUCT_FOUR;
		_AL_STRUCT_FOUR.Param1 = Param1;
		_AL_STRUCT_FOUR.Param2 = Param2;
		_AL_STRUCT_FOUR.Param3 = Param3;
		_AL_STRUCT_FOUR.Param4 = Param4;
		SendMessageA (g_hGameHandle,SELL_GOOD, 0, (LPARAM)&_AL_STRUCT_FOUR);
	}else
	{
		OutputDebugString("卖物出错,ID非法!");
	}
	return 0;
}
//刷木童
int CCLua::LuaShuMuTong(lua_State *L)
{
	SendMessageA (g_hGameHandle,INTERAVTIVE_SHUA_MUTONG, 0, (LPARAM)0);
	return 0;
}
//登高
int CCLua::LuaDengGao(lua_State *L)
{
	SendMessageA (g_hGameHandle,INTERAVTIVE_DENGGAO, 0, (LPARAM)0);
	return 0;
}
//过图CALL
int CCLua::LuaPassMap(lua_State *L)
{
	int prarm = lua_gettop(L);
	if(prarm == 1)
	{
		int Param1 = (int)lua_tointeger(L, 1);
		SendMessageA (g_hGameHandle,MAP_CHANGE_MOVE, 0, (LPARAM)Param1);
	}else
	{
		OutputDebugString("过图出错,ID非法!");
	}
	return 0;
}