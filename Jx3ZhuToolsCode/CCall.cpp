#include "stdafx.h"
#include "CCall.h"


CCCall::CCCall(void)
{
}


CCCall::~CCCall(void)
{
}

//鼠标寻路
void CCCall::MoveTo(int MoveToX,int MoveToY)
{
	try {
		//寻路的结构构造
		CCUserInfo _CCUserInfo;
		struct MOTO _MOTOStruct = {(float)MoveToX,(float)MoveToY,(float)_CCUserInfo.getObjectPointZ()};
		int UIAddr = _CCGameWndProc->GetGameUIModuleAddr();
		int _ECX = UIAddr + MOUSE_MOVETO_CALL_ECX;
		int _CALL = UIAddr + MOUSE_MOVETO_CALL;
		int PointMoto = (int)&_MOTOStruct;

		//取最后一个参数
		int LastPrarm = 1;//默认为1
		//获取人物地址
		int BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_BASE_OFFSET;
		BASE_ADDR = *(unsigned int *)(BASE_ADDR);
		int ModData = *(unsigned int *)(BASE_ADDR + 0x44);
		LastPrarm = *(unsigned int *)(ModData + 4);
		if(_ECX && _CALL)
		{
			_asm
			{
				pushad
				push 0
				push 1
				push PointMoto
				push LastPrarm
				mov ecx,_ECX
				mov eax,_CALL
				call eax
				popad
			}
		}else
		{
			OutputDebugString("鼠标寻路CALL出错");
		}
	}
	catch (...) {
		OutputDebugString("鼠标寻路CALL出错");
	}
}

//技能CALL
void CCCall::CALL_SKILL(int SkillID,int SkillLevel)
{
	__TRY
		//获取人物地址
	int BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_BASE_OFFSET;
	BASE_ADDR = *(unsigned int *)(BASE_ADDR);
	//技能CALL地址
	int SKILL_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + SKILL_CALL_OFFSET;
	_asm
	{
		pushad
			push 0
			push 0
			push 0
			push SkillLevel
			push SkillID
			mov ecx,BASE_ADDR
			call SKILL_CALL
			popad
	}
	__CATCH("使用技能CALL出错!")
}
//选怪CALL
void CCCall::CALL_SELECT_MONSTGER(int MonsterID)
{
	__TRY
	//获取人物地址
	int BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_BASE_OFFSET;
	BASE_ADDR = *(unsigned int *)(BASE_ADDR);
	//选怪CALL地址
	int SELECT_MONSTER_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + SELECT_MONSTER_CALL_OFFSET;
	_asm
	{
		pushad
			push MonsterID;
			push 3
			mov ecx,BASE_ADDR
			call SELECT_MONSTER_CALL
			popad
	}
	__CATCH("使用选怪CALL出错!")
}
//采集CALL
void CCCall::CALL_ACQUIST(int DoorID)
{
	__TRY
	int Acquitst_Ecx = (int)_CCGameWndProc->GetGameModuleAddr() + ACQUIST_CALL_ECX_OFFSET;
	int Acquitst_Call = (int)_CCGameWndProc->GetGameModuleAddr() + ACQUIST_CALL_OFFSET;
	CString sas;
	sas.Format("采集 - ECX = %08X,Call = %08X",Acquitst_Ecx,Acquitst_Call);
	OutputDebugString(sas.GetBuffer());
	_asm
	{
		pushad
		push DoorID
		mov ecx,Acquitst_Ecx
		mov eax,Acquitst_Call
		call eax
		popad
	}
	OutputDebugString("调用采集CALL完毕!");
	__CATCH("使用采集CALL出错!")
}
//拾取CALL
//第一个参数，包裹ID，第二个参数拾取物品，或者尸体ID
void CCCall::CALL_PICKUP(int PackID,int PickUpID)
{
	__TRY
		int PickUp_Ecx = (int)_CCGameWndProc->GetGameModuleAddr() + PICKUP_GOOD_ECX_OFFSET;
		int PickUp_Call = (int)_CCGameWndProc->GetGameModuleAddr() + PICKUP_GOOD_CALL_OFFSET;
		_asm
		{
			pushad
				push PackID
				push PickUpID
				mov ecx,PickUp_Ecx
				mov eax,PickUp_Call
				call eax
			popad
				
		}
	__CATCH("使用拾取物品CALL出错")
}
//明文包接任务
//第一参数：任务ID，第二个参数：NPC ID
void CCCall::CALL_ACCPET_TASK(int TASK_ID,int NPC_ID)
{
	__TRY
		byte bufferAccpet[15] = {0x2E,0x00,0x2C,0x00,0x19,0x5F,0x03,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00};
		struct AccpetTaskBuffer *_AccpetTaskBuffer = (struct AccpetTaskBuffer *)bufferAccpet;
		_AccpetTaskBuffer->NPC_ID = NPC_ID;
		_AccpetTaskBuffer->TASK_ID = TASK_ID;
		int AccpetTask_Ecx = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_ECX_OFFSET;
		int AccpetTask_Call = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_OFFSET;
		int _resault = -1;
		_asm
		{
			pushad
			push 0xF
			push _AccpetTaskBuffer
			mov ecx,AccpetTask_Ecx
			mov eax,AccpetTask_Call
			call eax
			mov _resault,eax
			popad
		}
	__CATCH("明文包接任务出错")
}
//明文包交任务(不带奖励选择)
//第一参数：任务ID，第二个参数：NPC ID
void CCCall::CALL_FINSH_TASK(int TASK_ID,int NPC_ID)
{
	__TRY
		byte bufferFinsh[26] = {0x30,0x00,0x00,0x00,0xE4,0xF3,0x3F,0x2F,0x00,0x00,0x03,0x00,0x00,0x00,0x6E,0x04,0x00,0x40,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00};
	struct FinshTaskBuffer *_FinshTaskBuffer = (struct FinshTaskBuffer *)bufferFinsh;
	_FinshTaskBuffer->NPC_ID = NPC_ID;
	_FinshTaskBuffer->TASK_ID = TASK_ID;
	int AccpetTask_Ecx = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_ECX_OFFSET;
	int AccpetTask_Call = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_OFFSET;
	int _resault = -1;
	_asm
	{
		pushad
			push 0x1A
			push _FinshTaskBuffer
			mov ecx,AccpetTask_Ecx
			mov eax,AccpetTask_Call
			call eax
			mov _resault,eax
			popad
	}
	__CATCH("明文交接任务出错")
}
//明文包交任务(不带奖励选择)
//第一参数：任务ID，第二个参数：NPC ID，第三个参数：任务物品选项
void CCCall::CALL_FINSH_TASK_BY_SELECT(int TASK_ID,int NPC_ID,int SelectIndex)
{
	__TRY
		byte bufferFinsh[26] = {0x30,0x00,0x00,0x00,0xE4,0xF3,0x3F,0x2F,0x00,0x00,0x03,0x00,0x00,0x00,0x6E,0x04,0x00,0x40,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00};
	struct FinshTaskBufferEx *_FinshTaskBuffer = (struct FinshTaskBufferEx *)bufferFinsh;
	_FinshTaskBuffer->NPC_ID = NPC_ID;
	_FinshTaskBuffer->TASK_ID = TASK_ID;
	_FinshTaskBuffer->bufferIndex = SelectIndex;
	int AccpetTask_Ecx = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_ECX_OFFSET;
	int AccpetTask_Call = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_OFFSET;
	int _resault = -1;
	_asm
	{
		pushad
			push 0x1A
			push _FinshTaskBuffer
			mov ecx,AccpetTask_Ecx
			mov eax,AccpetTask_Call
			call eax
			mov _resault,eax
			popad
	}
	__CATCH("明文交接任务出错")
}
//放弃任务明文
//参数：任务索引
void CCCall::CALL_DELETE_TASK(int _Index)
{
	__TRY
	if (_Index <= 12)
	{
		byte bufferDelete[10] = {0x2F,0x00,0x4B,0x00,0x08,0x25,0x00,0x00,0x00,0x00};
		struct DeleteTaskBuffer *_DeleteTaskBuffer = (struct DeleteTaskBuffer *)bufferDelete;
		_DeleteTaskBuffer->TaskIndex = _Index;
		int AccpetTask_Ecx = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_ECX_OFFSET;
		int AccpetTask_Call = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_OFFSET;
		_asm
		{
			pushad
				push 0xA
				push _DeleteTaskBuffer
				mov ecx,AccpetTask_Ecx
				mov eax,AccpetTask_Call
				call eax
				popad
		}
	}else
	{
		
	}
	__CATCH("明文放弃任务出错")
}

//打开NPC 对话
//参数：NPCID
void CCCall::CALL_OPEN_NPC(int NPCID)
{
	__TRY
		int OPEN_NPC_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + OPEN_NPC_CALL_ECX_OFFSET;
		int OPEN_NPC_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + OPEN_NPC_CALL_OFFSET;
		_asm
		{
			pushad
			push 0
			push 0
			push 0
			push 0
			push 0
			push 0
			push 1
			push NPCID
			mov ecx,OPEN_NPC_ECX
			mov eax,OPEN_NPC_CALL
			call eax
			popad
		}
	__CATCH("NPC 对话CALL出错")
}
//买物品CALL
void CCCall::CALL_BUY_GOOD(struct Buy_Good_Struct *__Buy_Good_Struct)
{
	__TRY
	int BUY_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + BUY_GOOD_CALL_ECX_OFFSET;
	int BUY_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + BUY_GOOD_CALL_OFFSET;
	int AllPrice = __Buy_Good_Struct->Count * __Buy_Good_Struct->Price;
	int Count = __Buy_Good_Struct->Count;
	int GoodID = __Buy_Good_Struct->GoodID;
	int Good_Index = __Buy_Good_Struct->Good_Index;
	int Shop_Index = __Buy_Good_Struct->Shop_Index;
	_asm
	{
		pushad
			push 0
			push AllPrice
			push Count
			push GoodID
			push Good_Index
			push Shop_Index
			mov ecx,BUY_ECX
			mov eax,BUY_CALL
			call eax
			popad
	}
	__CATCH("买物品CALL出错")
}
//打开商店
//参数，商店编号
void CCCall::CALL_OPEN_SHOP(int ShopNum)
{
	__TRY
	int OPEN_SHOP_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + OPEN_SHOP_BY_INDEX_CALL_ECX_OFFSET;
	int OPEN_SHOP_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + OPEN_SHOP_BY_INDEX_CALL_OFFSET;
	if (HOOKText == "HOOKTEXT")
	{
		OutputDebugString("打开商店失败，请先打开NPC对话!");
		return;
	}
	int SHOP_NUM = -1;
	int iPos = 0, iPos2 = 0;
	iPos = HOOKText.find ("M ");
	iPos2 = HOOKText.find (" ", iPos + 2);
	string currentStr = HOOKText.substr (iPos + 2, iPos2 - (iPos + 2));
	SHOP_NUM = _ttoi(currentStr.c_str());
	if(SHOP_NUM==-1)
	{
		OutputDebugString("打开商店失败,编号获取错误");
		return;
	}
	_asm
	{
		pushad
			push SHOP_NUM
			mov ecx,OPEN_SHOP_ECX
			mov eax,OPEN_SHOP_CALL
			call eax
			popad
	}
	__CATCH("打开商店CALL出错")
}
//任务二级对话
//参数1.对话索引 2.对话产量
void CCCall::CALL_TASK_NPC_TALK(int talkIndex, int TalkID)
{
	__TRY
	int NPC_TALK_SUB_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + NPC_TALK_SUB_CALL_ECX_OFFSET;
	int NPC_TALK_SUB_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + NPC_TALK_SUB_CALL_OFFSET;
	int BASE_PARAM = (int)_CCGameWndProc->GetGameKGUIModuleAddr() + TASK_SUB_TALK_PRARTM_BASE_OFFSET;
	int LASTVALE = 0;
	if (BASE_PARAM && IsReadAddrInt((PVOID)BASE_PARAM))
	{
		int FIRST_VALUE = *(int *)BASE_PARAM;
		if (IsReadAddrInt((PVOID)(FIRST_VALUE+TASK_SUB_TALK_PRARTM_OFFSET_1+TASK_SUB_TALK_PRARTM_OFFSET_2)))
		{
			int SECOND_VALUE = *(int *)(FIRST_VALUE+TASK_SUB_TALK_PRARTM_OFFSET_1+TASK_SUB_TALK_PRARTM_OFFSET_2);
			INT_BUFER _INT_BUFER;
			_INT_BUFER._VALUE=SECOND_VALUE;
			_INT_BUFER.BUF.b1 = talkIndex;
			_INT_BUFER.BUF.b3 = 0x7F;
			_INT_BUFER.BUF.b4 = 0x00;
			LASTVALE = _INT_BUFER._VALUE;
		}else
		{
			OutputDebugString("任务二级对话CALL出错:取参数一表达式出错!");
			return;
		}
		
	}else
	{
		OutputDebugString("任务二级对话CALL出错:取参数一表达式出错!");
		return;
	}

	_asm
	{
			pushad
			push LASTVALE
			push TalkID
			mov ecx,NPC_TALK_SUB_CALL_ECX
			mov eax,NPC_TALK_SUB_CALL
			call eax
			popad
	}
	__CATCH("任务二级对话CALL出错")
}
//使用物品CALL
//参数1.包裹索引 2.背包格子索引
void CCCall::CALL_USE_GOOD(int PercelIndex,int PacktIndex)
{
	__TRY
	int CONST_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + USE_GOOD_CALL_STRUCT_CONST_OFFSET;
	if(CONST_ADDR && IsReadAddrInt((PVOID)CONST_ADDR))
	{
		CONST_ADDR = *(unsigned int *)CONST_ADDR;
	}else
	{
		return;
	}
	struct USE_GOOD_STRUCT _USE_GOOD_STRUCT;
	_USE_GOOD_STRUCT.ConstData  = 4;//默认值
	_USE_GOOD_STRUCT.GoodID = CONST_ADDR;
	int BASE_ADDR = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_BASE_OFFSET;
	BASE_ADDR = *(unsigned int *)(BASE_ADDR);
	_USE_GOOD_STRUCT.RoleAddr = BASE_ADDR;
	int PushAddr = (int)&_USE_GOOD_STRUCT;
	int USE_GOOD_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + USE_GOOD_CALL_ECX_OFFSET;
	int USE_GOOD_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + USE_GOOD_CALL_OFFSET;
	_asm
	{
		pushad
		push PushAddr
		push PacktIndex
		push PercelIndex
		mov ecx,USE_GOOD_CALL_ECX
		mov eax,USE_GOOD_CALL
		call eax
		popad
	}
	__CATCH("使用物品CALL出错")
}
//穿戴物品CALL
//参数1.穿戴位置2.包裹索引3.格子索引
void CCCall::CALL_WEAR_GOOD(int WearIndex,int PercelIndex,int PackIndex)
{
	__TRY
	int WEAR_GOOD_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + WEAR_GOOD_CALL_ECX_OFFSET;
	int WEAR_GOOD_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + WEAR_GOOD_CALL_OFFSET;
	_asm
	{
			pushad
			push 0
			push WearIndex
			push 0
			push PackIndex
			push PercelIndex
			mov ecx,WEAR_GOOD_CALL_ECX
			mov eax,WEAR_GOOD_CALL
			call eax
			popad
	}
	__CATCH("穿戴物品CALL出错")
}
//穿戴马匹CALL
//参数1.穿戴位置2.包裹索引3.格子索引
void CCCall::CALL_WEAR_HORSE(int WearIndex,int PercelIndex,int PackIndex)
{
	__TRY
	int WEAR_GOOD_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + WEAR_GOOD_CALL_ECX_OFFSET;
	int WEAR_GOOD_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + WEAR_GOOD_CALL_OFFSET;
	_asm
	{
		pushad
			push 0
			push 0
			push WearIndex
			push PackIndex
			push PercelIndex
			mov ecx,WEAR_GOOD_CALL_ECX
			mov eax,WEAR_GOOD_CALL
			call eax
			popad
	}
	__CATCH("穿戴马匹CALL出错")
}


//穿戴千机物品CALL
//参数1.千机数量2.千机的索引3.格子索引4.包裹索引
void CCCall::CALL_WEAR_THOUSADNS(int ThousandsCount,int ThousandsIndex,int PackIndex,int PercelIndex)
{
	__TRY
		int WEAR_GOOD_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + WEAR_GOOD_CALL_ECX_OFFSET;
	int WEAR_GOOD_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + WEAR_GOOD_CALL_OFFSET;
	_asm
	{
		pushad
			push ThousandsCount
			push ThousandsIndex
			push 0x11
			push PackIndex
			push PercelIndex
			mov ecx,WEAR_GOOD_CALL_ECX
			mov eax,WEAR_GOOD_CALL
			call eax
			popad
	}
	__CATCH("穿戴千机物品CALL出错")
}

//拾取金币CALL
//参数：要拾取的对象ID
void CCCall::CALL_PICKUP_GLOD(int PickupID)
{
	__TRY
	int PICKUP_GLOD_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + PICKUP_GLOD_CALL_ECX_OFFSET;
	int PICKUP_GLOD_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + PICKUP_GLOD_CALL_OFFSET;
	_asm
	{
		pushad
			push PickupID
			mov ecx,PICKUP_GLOD_CALL_ECX
			mov eax,PICKUP_GLOD_CALL
			call eax
			popad
	}
	__CATCH("拾取金币CALL出错")
}
//人物跳CALL
void CCCall::CALL_ROLE_JMP()
{
	__TRY
		CCUserInfo _CCUserInfo;
		int ROLE_ECX = _CCUserInfo.getBaseAddr();
		int ROLE_DE = _CCUserInfo.getObjectDirection();
		int ROLE_JMP_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_JMP_CALL_OFFSET;
		_asm
		{
				pushad
				push ROLE_DE
				push 0
				mov ecx,ROLE_ECX
				mov eax,ROLE_JMP_CALL
				call eax
			popad
		}
	__CATCH("人物跳CALL出错")
}
//轻功CALL
//参数:1.开启，0.关闭
void CCCall::CALL_ROLE_DODGE(int OffOrOn)
{
	__TRY
	CCUserInfo _CCUserInfo;
	int PUSHRole = _CCUserInfo.getBaseAddr();
	int ROLE_DODGE_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_DODGE_CALL_ECX_OFFSET;
	int ROLE_DODGE_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + ROLE_DODGE_CALL_OFFSET;
	_asm
	{
		pushad
			push OffOrOn
			push 1
			push PUSHRole
			mov ecx,ROLE_DODGE_CALL_ECX
			mov eax,ROLE_DODGE_CALL
			call eax
			popad
	}
	__CATCH("人物轻功CALL出错")
}
//取消打坐CALL
void CCCall::CALL_CANCEL_SET_DOWN()
{
	__TRY
	CCUserInfo _CCUserInfo;
	int EcxRole = _CCUserInfo.getBaseAddr();
	int ROLE_CANCLE_SET_DWON_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + CANCEL_SETDOWN_CALL_OFFSET;
	_asm
	{
		pushad
		push 1
		mov ecx,EcxRole
		mov eax,ROLE_CANCLE_SET_DWON_CALL
		call eax
		popad
	}
	__CATCH("使用取消打坐CALL出错!")
}
//按键CALL(抬起)
//参数：F 按键值
void CCCall::CALL_KEY_F_UP()
{
	__TRY
		int KGUI_ADDR = (int)_CCGameWndProc->GetGameKGUIModuleAddr();
		int _ECX = KGUI_ADDR + KEY_CALL_ECX_BASE_OFFSET;
		int KEY_CALL = KGUI_ADDR + KEY_CALL_OFFSET;
		_asm
		{
			pushad
				push 0x0210001
				push 0x46
				push 0x101
				mov ecx,_ECX
				mov ecx,[ecx]
				add ecx,KEY_CALL_ECX_BASE_BIG_OFFSET
				mov eax,KEY_CALL
				call eax
			popad
		}

	__CATCH("使用按键CALL出错!")
}
//按键CALL(按下)
//参数：F 按键值
void CCCall::CALL_KEY_F_DOWN()
{
	__TRY
	int KGUI_ADDR = (int)_CCGameWndProc->GetGameKGUIModuleAddr();
	int _ECX = KGUI_ADDR + KEY_CALL_ECX_BASE_OFFSET;
	int KEY_CALL = KGUI_ADDR + KEY_CALL_OFFSET;
	_asm
	{
		pushad
			push 0x0210001
			push 0x46
			push 0x100
			mov ecx,_ECX
			mov ecx,[ecx]
			add ecx,KEY_CALL_ECX_BASE_BIG_OFFSET
			mov eax,KEY_CALL
			call eax
			popad
	}

	__CATCH("使用按键CALL出错!")
}

//按键CALL(抬起)
//参数：ESC 按键值
void CCCall::CALL_KEY_ESC_UP()
{
	__TRY
		int KGUI_ADDR = (int)_CCGameWndProc->GetGameKGUIModuleAddr();
	int _ECX = KGUI_ADDR + KEY_CALL_ECX_BASE_OFFSET;
	int KEY_CALL = KGUI_ADDR + KEY_CALL_OFFSET;
	_asm
	{
		pushad
			push 0x10001
			push 0x46
			push 0x101
			mov ecx,_ECX
			mov ecx,[ecx]
		add ecx,KEY_CALL_ECX_BASE_BIG_OFFSET
			mov eax,KEY_CALL
			call eax
			popad
	}

	__CATCH("使用按键CALL出错!")
}
//按键CALL(按下)
//参数：ESC 按键值
void CCCall::CALL_KEY_ESC_DOWN()
{
	__TRY
		int KGUI_ADDR = (int)_CCGameWndProc->GetGameKGUIModuleAddr();
	int _ECX = KGUI_ADDR + KEY_CALL_ECX_BASE_OFFSET;
	int KEY_CALL = KGUI_ADDR + KEY_CALL_OFFSET;
	_asm
	{
		pushad
			push 0x10001
			push 0x1B
			push 0x100
			mov ecx,_ECX
			mov ecx,[ecx]
		add ecx,KEY_CALL_ECX_BASE_BIG_OFFSET
			mov eax,KEY_CALL
			call eax
			popad
	}

	__CATCH("使用按键CALL出错!")
}

//--------------------------------------------------------------------
//按键CALL(抬起)
//参数：SPACE 按键值
void CCCall::CALL_KEY_SPACE_UP()
{
	__TRY
		int KGUI_ADDR = (int)_CCGameWndProc->GetGameKGUIModuleAddr();
	int _ECX = KGUI_ADDR + KEY_CALL_ECX_BASE_OFFSET;
	int KEY_CALL = KGUI_ADDR + KEY_CALL_OFFSET;
	_asm
	{
		pushad
			push 0x390001
			push 0x20
			push 0x101
			mov ecx,_ECX
			mov ecx,[ecx]
		add ecx,KEY_CALL_ECX_BASE_BIG_OFFSET
			mov eax,KEY_CALL
			call eax
			popad
	}

	__CATCH("使用按键CALL出错!")
}
//按键CALL(按下)
//参数：SPACE 按键值
void CCCall::CALL_KEY_SPACE_DOWN()
{
	__TRY
	int KGUI_ADDR = (int)_CCGameWndProc->GetGameKGUIModuleAddr();
	int _ECX = KGUI_ADDR + KEY_CALL_ECX_BASE_OFFSET;
	int KEY_CALL = KGUI_ADDR + KEY_CALL_OFFSET;
	_asm
	{
		pushad
			push 0x390001
			push 0x20
			push 0x100
			mov ecx,_ECX
			mov ecx,[ecx]
		add ecx,KEY_CALL_ECX_BASE_BIG_OFFSET
			mov eax,KEY_CALL
			call eax
			popad
	}

	__CATCH("使用按键CALL出错!")
}

//转向CALL
//参数：转向角度
void CCCall::CALL_TRUN(double trnValue)
{
	__TRY
	int JX3RepresentAddr = (int)_CCGameWndProc->GetGameJX3RepresentModuleAddr();
	int _ECX = JX3RepresentAddr + TRAN_CALL_ECX_BASE_OFFSET;
	int _ECX_OFFSET = TRAN_CALL_ECX_BIG_OFFSET + 0x10;
	int TRAN_CALL = JX3RepresentAddr + TRAN_CALL_OFFSET;
	_ECX = *((int *)_ECX);
	_ECX = *(int *)(_ECX + _ECX_OFFSET);
	_ECX = *((int *)_ECX);
	_ECX = *((int *)_ECX);
	float trnValue_f = (float)trnValue;
	_asm
	{
		pushad
			mov ecx,_ECX
			push 1
			push trnValue_f
			mov eax,TRAN_CALL
			call eax
		popad
	}
	__CATCH("使用转向CALL出错!")
}

//销毁物品CALL
//参数1.格子索引，2.包裹索引
void CCCall::CALL_DISTORY_GOOD(int _packIndex,int _percelIndex)
{
	__TRY
	int DISTORY_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + DELETE_GOOD_CALL_ECX_OFFSET;
	int DISTORY_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + DELETE_GOOD_CALL_OFFSET;
	_asm
	{
		pushad
			push 0
			push 0
			push 0xFF
			push _packIndex
			push _percelIndex
			mov ecx,DISTORY_CALL_ECX
			mov eax,DISTORY_CALL
			call eax
			popad
	}
	__CATCH("使用销毁物品CALL出错!")
}

//退出组队
void CCCall::CALL_QUIT_THE_TEAM()
{
	__TRY
	byte _bufferQuitTeam[10] = {0x24,0x00 ,0x00,0x00 ,0x00 ,0x00 ,0x4C ,0x01 ,0x04 ,0x00};
	struct QUIT_TEAM *_QUIT_TEAM = (struct QUIT_TEAM *)(_bufferQuitTeam);
	CCUserInfo _CCUserInfo;
	int RoleBaseAddr = _CCUserInfo.getBaseAddr();
	if (IsReadAddrInt((PVOID)RoleBaseAddr))
	{
		int QuitTeamID = *(int *)(RoleBaseAddr + 0x4);
		_QUIT_TEAM->RoleID = QuitTeamID;
		int AccpetTask_Ecx = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_ECX_OFFSET;
		int AccpetTask_Call = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_OFFSET;
		_asm
		{
			pushad
				push 0xA
				push _QUIT_TEAM
				mov ecx,AccpetTask_Ecx
				mov eax,AccpetTask_Call
				call eax
				popad
		}
	}else
	{
		OutputDebugString("退出组队出错，人物基址异常!");
	}
	__CATCH("封包退出组队出错!")
}
//发起组队CALL
//参数：组队结构
void CCCall::CALL_REQUEST_TEAM(struct REQUEST_TETHER_TEAM *_REQUEST_TETHER_TEAM)
{
	__TRY
		byte _bufferRequestQuitTeam[46] = {0x20,0x00};
		struct REQUEST_TETHER_TEAM *__REQUEST_TETHER_TEAM = (struct REQUEST_TETHER_TEAM *)(_bufferRequestQuitTeam);
		memset(__REQUEST_TETHER_TEAM,0,46);
		__REQUEST_TETHER_TEAM->Flag = 0x20;
		memcpy(__REQUEST_TETHER_TEAM->PlayName,_REQUEST_TETHER_TEAM->PlayName,32);
		int AccpetTask_Ecx = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_ECX_OFFSET;
		int AccpetTask_Call = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_OFFSET;
		_asm
		{
				pushad
				push 0x2E
				push __REQUEST_TETHER_TEAM
				mov ecx,AccpetTask_Ecx
				mov eax,AccpetTask_Call
				call eax
				popad
		}

	__CATCH("封包发起组队出错!")
}
//接受组队
//参数：接受组队结构
void CCCall::CALL_RESPONSE_TEAM(struct RESPONE_TETHER_TEAM *_RESPONE_TETHER_TEAM)
{
	__TRY
	byte _bufferResponseQuitTeam[42] = {0x21,0x00};
	struct RESPONE_TETHER_TEAM *__RESPONE_TETHER_TEAM = (struct RESPONE_TETHER_TEAM *)(_bufferResponseQuitTeam);
	memset(__RESPONE_TETHER_TEAM,0,42);
	__RESPONE_TETHER_TEAM->Flag = 0x21;
	memcpy(__RESPONE_TETHER_TEAM->PlayName,_RESPONE_TETHER_TEAM->PlayName,36);
	OutputDebugString(__RESPONE_TETHER_TEAM->PlayName);
	int AccpetTask_Ecx = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_ECX_OFFSET;
	int AccpetTask_Call = (int)_CCGameWndProc->GetGameModuleAddr() + ACCPET_TASK_BUFFER_CALL_OFFSET;
	_asm
	{
			pushad
			push 0x2A
			push __RESPONE_TETHER_TEAM
			mov ecx,AccpetTask_Ecx
			mov eax,AccpetTask_Call
			call eax
			popad
	}
	__CATCH("接受组队出错!")
}
//图内寻路CALL
//三个参数是录制时自己记录
void CCCall::CALL_MAP_IN_RUN_TO(int Param1,int Param2,int Param3)
{
	int CALL_MAP_INT_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + MAP_IN_RUN_TO_CALL_ECX_OFFSET;
	int CALL_MAP_IN_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + MAP_IN_RUN_TO_CALL_OFFSET;
	__TRY
		_asm
		{
			pushad
			push Param1
			push Param2
			push Param3
			mov ecx,CALL_MAP_INT_ECX
			mov eax,CALL_MAP_IN_CALL
			call eax
			popad
		}
	__CATCH("图内寻路CALL出错")

}

//切换内功CALL
//参数：内功ID
void CCCall::CALL_CHANGE_KUNG_FU(int KungFuID)
{
	int CALL_CHANGE_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + CHANGE_KUNG_FU_CALL_ECX_OFFSET;
	int CALL_CHANGE_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + CHANGE_KUNG_FU_CALL_OFFSET;
	__TRY
		_asm
		{
			pushad
			push 1
			push KungFuID
			mov ecx,CALL_CHANGE_CALL_ECX
			mov eax,CALL_CHANGE_CALL
			call eax
			popad
		}
	__CATCH("切换内功CALL出错")
}

//交互CALL
//参数：交互结构
void CCCall::CALL_INTERACTIVE(struct INTERACTIVE_STRUCT *_INTERACTIVE_STRUCT)
{
	__TRY
		byte InterActiveBuffer[50] = {0x00};
		struct INTERACTIVE_STRUCT *__INTERACTIVE_STRUCT = (struct INTERACTIVE_STRUCT *)(InterActiveBuffer);
		memset(__INTERACTIVE_STRUCT,0,36);
		memcpy(__INTERACTIVE_STRUCT->ActiveItem,_INTERACTIVE_STRUCT->ActiveItem,36);
		int ActionFlag = _INTERACTIVE_STRUCT->Flag;
		int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
		int CONST_INTER = GAME_ADDR + INTERAVTIVE_CONST_BASE_OFFSET;
		if (IsReadAddrInt((PVOID)CONST_INTER))
		{
			int GAME_ADDR_VALUE = *(int *)CONST_INTER;
			int GAME_ADDR_VALUE_OFFSET = GAME_ADDR_VALUE + INTERACTIVE_CONST_OFFSET_1 + INTERACTIVE_CONST_OFFSET_2;
			int INTERACTIVE_CALL_ECX = GAME_ADDR + INTERACTIVE_CALL_ECX_OFFSET;
			int INTERACTIVE_CALL = GAME_ADDR + INTERACTIVE_CALL_OFFSET;
			if (IsReadAddrInt((PVOID)GAME_ADDR_VALUE_OFFSET))
			{
				int Const_Param = GAME_ADDR_VALUE_OFFSET;
				*(int *)Const_Param = _INTERACTIVE_STRUCT->Flag2;
				int StrAddr = (int )__INTERACTIVE_STRUCT->ActiveItem;
				_asm
				{
					pushad
					push ActionFlag
					push Const_Param
					push StrAddr
					mov ecx,INTERACTIVE_CALL_ECX
					mov eax,INTERACTIVE_CALL
					call eax
					popad
				}
			}else
			{
				OutputDebugString("交互CALL 常量异常2!");
			}
		}else
		{
			OutputDebugString("交互CALL 常量异常1!");
		}
	__CATCH("交互CALL出错!")
}
//交互CALL 刷木童
void CCCall::CALL_INTERACTIVE_MUTONG()
{
	__TRY
		byte InterActiveBuffer[70] = {0x00};
	char ItemStr[36] = "On_Teaching_Finish";
	byte ActionBuffer[30] = {0x1B,0x02,0x5A,0x55,0x4F,0x42,0x49,0x41,0x4F,0x31,0x00,0x11,0x00,0x00,0x74,0x00,0x11,0x00,0x00};
	struct INTERACTIVE_STRUCT_2 *__INTERACTIVE_STRUCT = (struct INTERACTIVE_STRUCT_2 *)(InterActiveBuffer);
	memset(__INTERACTIVE_STRUCT,0,70);
	memcpy(__INTERACTIVE_STRUCT->ActiveItem,ItemStr,36);
	memcpy(__INTERACTIVE_STRUCT->ActionFlag,ActionBuffer,30);
	int ActionFlag = 0x0E;
	int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int CONST_INTER = GAME_ADDR + INTERAVTIVE_CONST_BASE_OFFSET;
	int INTERACTIVE_CALL_ECX = GAME_ADDR + INTERACTIVE_CALL_ECX_OFFSET;
	int INTERACTIVE_CALL = GAME_ADDR + INTERACTIVE_CALL_OFFSET;
	int SubParam = (int )__INTERACTIVE_STRUCT->ActionFlag;
	int StrAddr = (int )__INTERACTIVE_STRUCT->ActiveItem;
	_asm
	{
		pushad
			push ActionFlag
			push SubParam
			push StrAddr
			mov ecx,INTERACTIVE_CALL_ECX
			mov eax,INTERACTIVE_CALL
			call eax
			popad
	}
	__CATCH("交互刷木童CALL出错!")
}
//交互CALL 唐门登高
void CCCall::CALL_INTERACTIVE_DENGGAO()
{
	__TRY
		byte InterActiveBuffer[70] = {0x00};
	char ItemStr[36] = "On_Teaching_Finish";
	byte ActionBuffer[30] = {0x1E,0x02,0x54,0x41,0x4E,0x47,0x4D,0x45,0x4E,0x4A,0x55,0x4D,0x50,0x00,0x11,0x00,0x00,0x00,0x00};
	struct INTERACTIVE_STRUCT_2 *__INTERACTIVE_STRUCT = (struct INTERACTIVE_STRUCT_2 *)(InterActiveBuffer);
	memset(__INTERACTIVE_STRUCT,0,70);
	memcpy(__INTERACTIVE_STRUCT->ActiveItem,ItemStr,36);
	memcpy(__INTERACTIVE_STRUCT->ActionFlag,ActionBuffer,30);
	int ActionFlag = 0x11;
	int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int CONST_INTER = GAME_ADDR + INTERAVTIVE_CONST_BASE_OFFSET;
	int INTERACTIVE_CALL_ECX = GAME_ADDR + INTERACTIVE_CALL_ECX_OFFSET;
	int INTERACTIVE_CALL = GAME_ADDR + INTERACTIVE_CALL_OFFSET;
	int SubParam = (int )__INTERACTIVE_STRUCT->ActionFlag;
	int StrAddr = (int )__INTERACTIVE_STRUCT->ActiveItem;
	_asm
	{
		pushad
			push ActionFlag
			push SubParam
			push StrAddr
			mov ecx,INTERACTIVE_CALL_ECX
			mov eax,INTERACTIVE_CALL
			call eax
			popad
	}
	__CATCH("交互登高CALL出错!")
}
//获取修理价格CALL
void CCCall::CALL_GET_REPAIR_PRICE(struct GET_REPIR_PRICE_STRUCT *_GET_REPIR_PRICE_STRUCT)
{
	__TRY
		CCUserInfo _CCUserInfo;
		int PUSHRole = _CCUserInfo.getBaseAddr();
		int Percel = _GET_REPIR_PRICE_STRUCT->PercelIndex;
		int PackIndex = _GET_REPIR_PRICE_STRUCT->PackIndex;
		int _ECX = _GET_REPIR_PRICE_STRUCT->_Ecx;
		int REPAIR_PRICE_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + REPAIR_PRICE_CALL_OFFSET;
		if(_ECX > 0)
		{
			int Price = 0;
			_asm
			{
				pushad
				push PackIndex
				push Percel
				push PUSHRole
				mov ecx,_ECX
				mov eax,REPAIR_PRICE_CALL
				call eax
				mov Price,eax
				popad
			}
			if (Price==-1)
			{
				Price = 0;
			}
			_GET_REPIR_PRICE_STRUCT->Price = Price;
		}else
		{
			OutputDebugString("ECX-获取商店地址出错");
		}
	__CATCH("获取修理价格CALL出错!")
}
//获取价格CALL
void CCCall::CALL_GET_PARE_PRICE(struct GET_REPIR_PRICE_STRUCT *_GET_REPIR_PRICE_STRUCT)
{
	__TRY
		CCUserInfo _CCUserInfo;
	int PUSHRole = _CCUserInfo.getBaseAddr();
	int Percel = _GET_REPIR_PRICE_STRUCT->PercelIndex;
	int PackIndex = _GET_REPIR_PRICE_STRUCT->PackIndex;
	int _ECX = _GET_REPIR_PRICE_STRUCT->_Ecx;
	int PRICE_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + GOOD_PRICE_CALL_OFFSET;
	if(_ECX > 0)
	{
		int Price = 0;
		_asm
		{
			pushad
				push PackIndex
				push Percel
				push PUSHRole
				mov ecx,_ECX
				mov eax,PRICE_CALL
				call eax
				mov Price,eax
				popad
		}
		if (Price==-1)
		{
			Price = 0;
		}
		_GET_REPIR_PRICE_STRUCT->Price = Price;
	}else
	{
		OutputDebugString("ECX-获取商店地址出错");
	}
	__CATCH("获取价格CALL出错!")
}
//修理全部装备
//参数1：全部价格
//参数2：商店编号
void CCCall::CALL_REPAIR_WEAR(int AllPrice,int ShopID)
{
	__TRY
		int REPAIR_WEAR_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + REPAIR_WEAR_CALL_ECX_OFFSET;
		int REPAIR_WEAR_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + REPAIR_WEAR_CALL_OFFSET;
		_asm
		{
			pushad
				push 0
				push 0
				push AllPrice
				push 0
				push ShopID
				mov ecx,REPAIR_WEAR_CALL_ECX
				mov eax,REPAIR_WEAR_CALL
				call eax
			popad
		}
	__CATCH("修理全部装备CALL出错!")
}
//升级技能CALL
//参数1：需要的修为
//参数2：技能等级
//参数3：技能ID
void CCCall::CALL_SKILL_UP(int NeedXiuWei,int Level,int SkillID)
{
	__TRY
	int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int SKILL_UP_CALL_ECX = GAME_ADDR + SKILL_UP_CALL_ECX_OFFSET;
	int SKILL_UP_CALL = GAME_ADDR + SKILL_UP_CALL_OFFSET;
	_asm
	{
		pushad
			push NeedXiuWei
			push Level
			push SkillID
			mov ecx,SKILL_UP_CALL_ECX
			mov eax,SKILL_UP_CALL
			call eax
		popad
	}
	__CATCH("修理全部装备CALL出错!")
}
//定点使用技能
//参数1.释放点X 2.释放点Y 3.释放点Z 4.技能等级 5.技能ID
void CCCall::CALL_SKILL_MAKE_POINT(int PointX,int PointY,int PointZ,int SkillLevel,int SkillID)
{
	__TRY
	int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int SKILL_MAKE_CALL_CURRENT = GAME_ADDR + SKILL_MAKE_POINT_CALL_OFFSET;
	CCUserInfo _CCUserInfo;
	int EcxRole = _CCUserInfo.getBaseAddr();
	_asm
	{
		pushad
			push PointX
			push PointY
			push PointZ
			push SkillLevel
			push SkillID
			mov ecx,EcxRole
			mov eax,SKILL_MAKE_CALL_CURRENT
			call eax
		popad
	}
	__CATCH("定点释放技能CALL出错!")
}
//奇穴设置
void CCCall::CALL_SPECIL_SET(int Param1,int Param2)
{
	__TRY
	int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int SPECIL_CALL_ECX = GAME_ADDR + SPECIL_SET_CALL_ECX_OFFSET;
	int SPECIL_CALL = GAME_ADDR + SPECIL_SET_CALL_OFFSET;
	_asm
	{
		pushad
			push Param1
			push Param2
			mov ecx,SPECIL_CALL_ECX
			mov eax,SPECIL_CALL
			call eax
		popad
	}
	__CATCH("奇穴设置CALL出错!")
}
//机关任务移动CALL
//参数：点击的选项
void CCCall::CALL_ORGAN_MOVE(int ClickIndex)
{
	__TRY
	if (TALK_ID==0)
	{
		OutputDebugString("请打开NPC对话!");
		return;
	}
	int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int ORGAN_CALL_ECX = GAME_ADDR + CALL_ORGAN_CALL_ECX_OFFSET;
	int ORGAN_CALL = GAME_ADDR + CALL_ORGAN_CALL_OFFSET;
	int BASE_PARAM = (int)_CCGameWndProc->GetGameKGUIModuleAddr() + TASK_SUB_TALK_PRARTM_BASE_OFFSET;
	int LASTVALE = 0;
	if (BASE_PARAM && IsReadAddrInt((PVOID)BASE_PARAM))
	{
		int FIRST_VALUE = *(int *)BASE_PARAM;
		if (IsReadAddrInt((PVOID)(FIRST_VALUE+TASK_SUB_TALK_PRARTM_OFFSET_1+TASK_SUB_TALK_PRARTM_OFFSET_2)))
		{
			int SECOND_VALUE = *(int *)(FIRST_VALUE+TASK_SUB_TALK_PRARTM_OFFSET_1+TASK_SUB_TALK_PRARTM_OFFSET_2);
			INT_BUFER _INT_BUFER;
			_INT_BUFER._VALUE=SECOND_VALUE;
			_INT_BUFER.BUF.b1 = ClickIndex;
			_INT_BUFER.BUF.b3 = 0x7F;
			_INT_BUFER.BUF.b4 = 0x00;
			LASTVALE = _INT_BUFER._VALUE;
		}else
		{
			OutputDebugString("机关任务CALL出错:取参数一表达式出错!");
			return;
		}

	}else
	{
		OutputDebugString("机关任务CALL出错:取参数一表达式出错!");
		return;
	}
	int SECOND_PARAM = TALK_ID;
	_asm
	{
			pushad
			push LASTVALE
			push SECOND_PARAM
			mov ecx,ORGAN_CALL_ECX
			mov eax,ORGAN_CALL
			call eax
			popad
	}
	__CATCH("奇穴设置CALL出错!")
}

//判断怪物是否在视野内
//怪物ID，怪物对象，技能对象
void CCCall::CALL_MONSTER_VIEW_SHOW(struct AL_STRUCT_FOUR *_AL_STRUCT_FOUR)
{
	__TRY
	struct AL_STRUCT_THREAD _AL_STRUCT_THREAD = {3,_AL_STRUCT_FOUR->Param1,_AL_STRUCT_FOUR->Param2};
	int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int _ECX = _AL_STRUCT_FOUR->Param3;
	int PointMonster = (int)&_AL_STRUCT_THREAD;
	int MONSTER_VIEW_CALL = GAME_ADDR + CALL_MONSTER_VIEW;
	CCUserInfo _CCUserInfo;
	int PUSHRole = _CCUserInfo.getBaseAddr();
	int RetValue = 1;
	_asm
	{
		pushad
		push 0
		push 0
		push PointMonster
		push PUSHRole
		mov ecx,_ECX
		mov eax,MONSTER_VIEW_CALL
		call eax
		mov RetValue,eax
		popad
	}
	_AL_STRUCT_FOUR->Param4 = RetValue;
	__CATCH("视野CALL出错!")
}
//判断类型CALL
//通用类型结构
void CCCall::CALL_OBJECT_TYPE_RET(struct AL_STRUCT *_AL_STRUCT)
{
	__TRY
		int RetValue = 0;//默认为0
		int ObjectAddr = _AL_STRUCT->Param1;
		if (ObjectAddr > 0)
		{
			int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
			int OBJECT_TYPE_RET_CALL = GAME_ADDR + CALL_TYPE_RET;
			CCUserInfo _CCUserInfo;
			int PUSHRole = _CCUserInfo.getBaseAddr();
			_asm
			{
				pushad
				push ObjectAddr
				push PUSHRole
				mov eax,OBJECT_TYPE_RET_CALL
				call eax
				mov RetValue,eax
				add esp,0x8
				popad
			}
		}else
		{
			OutputDebugString("对象地址异常!");
		}
		_AL_STRUCT->Param2 = RetValue;
	__CATCH("类型CALL出错!")
}
//神行千里
//参数1.地图代码 2.区域代码
void CCCall::CALL_SHEN_XING_QIAN_LI(int MapCode,int AreaCode)
{
	__TRY
	int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int SKILL_MAKE_CALL_CURRENT = GAME_ADDR + SKILL_MAKE_POINT_CALL_OFFSET;
	CCUserInfo _CCUserInfo;
	int EcxRole = _CCUserInfo.getBaseAddr();
	_asm
	{
		pushad
			push 0
			push MapCode
			push AreaCode
			push 1
			push 0xE6B
			mov ecx,EcxRole
			mov eax,SKILL_MAKE_CALL_CURRENT
			call eax
			popad
	}
	__CATCH("神行千里CALL出错!")
}
//使用礼包CALL
//参数1.包裹索引2.格子索引
void CCCall::CALL_USE_PACKET(int PercelIndex,int PackIndex)
{
	__TRY
	int USE_PACKET_CALL_ECX = (int)_CCGameWndProc->GetGameModuleAddr() + CALL_USE_PACKET_CALL_ECX_OFFSET;
	int USE_PACKET_CALL = (int)_CCGameWndProc->GetGameModuleAddr() + CALL_USE_PACKET_CALL_OFFSET;
	_asm
	{
		pushad
			push 0
			push PackIndex
			push PercelIndex
			mov ecx,USE_PACKET_CALL_ECX
			mov eax,USE_PACKET_CALL
			mov esi,1
			call eax
			popad
	}
	__CATCH("使用礼包CALL出错")
}
//卖物品CALL
void CCCall::CALL_SELL_GOOD(struct AL_STRUCT_FOUR *_AL_STRUCT_FOUR)
{
	__TRY
		if (HOOKText == "HOOKTEXT")
		{
			OutputDebugString("打开商店失败，请先打开NPC对话!");
			return;
		}
		int SHOP_NUM = -1;
		int iPos = 0, iPos2 = 0;
		iPos = HOOKText.find ("M ");
		iPos2 = HOOKText.find (" ", iPos + 2);
		string currentStr = HOOKText.substr (iPos + 2, iPos2 - (iPos + 2));
		SHOP_NUM = _ttoi(currentStr.c_str());
		if(SHOP_NUM==-1)
		{
			OutputDebugString("编号获取错误");
			return;
		}
	struct AL_STRUCT_THREAD _AL_STRUCT_THREAD = {3,_AL_STRUCT_FOUR->Param1,_AL_STRUCT_FOUR->Param2};
	int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int SELL_GOOD_CALL_ECX = GAME_ADDR + SELL_GOOD_CALL_ECX_OFFSET;
	int SELL_GOOD_CALL = GAME_ADDR + SELL_GOOD_CALL_OFFSET;
	int PacketIndex = _AL_STRUCT_FOUR->Param1;
	int PercelIndex = _AL_STRUCT_FOUR->Param2;
	int Price = _AL_STRUCT_FOUR->Param3;
	int Handle = _AL_STRUCT_FOUR->Param4;
	_asm
	{
			pushad
			push PacketIndex
			push PercelIndex
			push Price
			push Handle
			push SHOP_NUM
			mov ecx,SELL_GOOD_CALL_ECX
			mov eax,SELL_GOOD_CALL
			call eax
			popad
	}
	__CATCH("视野CALL出错!")
}
//过图CALL
void CCCall::CALL_PASS_MAP(int MapID)
{
	__TRY
		int GAME_ADDR = (int)_CCGameWndProc->GetGameModuleAddr();
	int PASS_MAP_CALL_ECX = GAME_ADDR + PASS_MAP_CALL_ECX_OFFSET;
	int PASS_MAP_CALL = GAME_ADDR + PASS_MAP_CALL_OFFSET;
	_asm
	{
		pushad
			push MapID
			mov ecx,PASS_MAP_CALL_ECX
			mov eax,PASS_MAP_CALL
			call eax
			popad
	}
	__CATCH("过图CALL出错!")
}