#ifndef _GAME_STRUCT
#define _GAME_STRUCT
//通用2参数结果
struct AL_STRUCT
{
	int Param1;
	int Param2;
};
//通用3参数结果
struct AL_STRUCT_THREAD
{
	int Param1;
	int Param2;
	int Param3;
};
//通用4参数结果
struct AL_STRUCT_FOUR
{
	int Param1;
	int Param2;
	int Param3;
	int Param4;
};

//通用5参数结果
struct AL_STRUCT_FIVE
{
	int Param1;
	int Param2;
	int Param3;
	int Param4;
	int Param5;
};

//寻路结构体
struct MOTO
{
	float fMoveToX;
	float fMoveToY;
	float MoveToZ;
};

//拾取物品结构体
struct PickCall_Struct
{
	int pickID;//包裹ID
	int pickUpGoodID;//尸体或者采集物品ID
};
#pragma pack (1)
//接任务封包结构
struct AccpetTaskBuffer
{
	byte buffer_1[7];
	WORD NPC_ID;//NPC ID
	WORD non1;
	WORD TASK_ID;//TASK ID
	WORD non2;
};
//交任务封包结构
struct FinshTaskBuffer
{
	byte buffer_1[6];
	WORD TASK_ID;//TASK ID
	byte buffer_2[6];
	WORD NPC_ID;//NPC ID
};
//交任务封包结构
struct FinshTaskBufferEx
{
	byte buffer_1[6];
	WORD TASK_ID;//TASK ID
	byte buffer_2[6];
	WORD NPC_ID;//NPC ID
	WORD non1;
	byte bufferIndex;
};
//放弃任务封包结构
struct DeleteTaskBuffer
{
	byte buffer_1[4];
	WORD Non1;
	byte TaskIndex;
	byte buffer_2[3];
};
//退出组队结构
struct QUIT_TEAM
{
	WORD Flag;
	int Zero;
	int RoleID;//退出组队使用
};
//组队结构体
struct REQUEST_TETHER_TEAM
{
	WORD Flag;
	int Zero1;
	int Zero2;
	int Zero3;
	char PlayName[32];
};
//接受组队结构体
struct RESPONE_TETHER_TEAM
{
	WORD Flag;
	int Zero1;
	char PlayName[36];
};
//交互结构体
struct INTERACTIVE_STRUCT
{
	//交互动作
	char ActiveItem[36];
	int Flag;
	int Flag2;
};
//交互结构体2
struct INTERACTIVE_STRUCT_2
{
	//交互动作
	char ActiveItem[36];
	byte ActionFlag[30];//交互动作
	int Flag2;
};
//联合体
union INT_BUFER
{
	int _VALUE;
	struct BUFFER
	{
		byte b1;
		byte b2;
		byte b3;
		byte b4;
	}BUF;
};

#pragma pack ()
//买物品结构
struct Buy_Good_Struct
{
	int Price;
	int Count;
	int GoodID;
	int Good_Index;
	int Shop_Index;
};

//使用物品CALL 结构
struct USE_GOOD_STRUCT
{
	int ConstData;
	int GoodID;
	int RoleAddr;
};
//使用物品CALL传参数结构
struct USE_GOOD_PARAM_STRUCT
{
	int PackIndex;
	int PercelIndex;
	int GoodID;
};
//根据CALL获取修理价格
struct GET_REPIR_PRICE_STRUCT
{
	int PackIndex;
	int PercelIndex;
	int Price;
	int _Ecx;//商店地址
};


#endif