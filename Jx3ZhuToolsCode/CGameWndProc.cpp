#include "stdafx.h"

  

 //枚举窗口句柄
 BOOL CALLBACK EnumWindowsProc(_In_  HWND hwnd, _In_  LPARAM lParam)
 {
	 DWORD dwProcessId = 0;
	 if (NULL != hwnd) {
		 ::GetWindowThreadProcessId(hwnd, &dwProcessId);
		 if (::GetCurrentProcessId() == dwProcessId) {
			*(HWND*)lParam = hwnd;
			 return FALSE;
		 }
	 }

	 return TRUE;
 }

 ///////更改信息操作功能/////
 LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
 {
	 LRESULT re;
	 switch (uMsg)
	 {
	 case MOVETO://鼠标寻路
		 {
			 MOTO *_Moto = (MOTO *)lParam;
			 CCCall _CCCall;
			 _CCCall.MoveTo((int)_Moto->fMoveToX,(int)_Moto->fMoveToY);
			 break;
		 }
	 case SELECT_MONSTER://选怪
		 {
			 int MonsterID = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_SELECT_MONSTGER(MonsterID);
			 break;
		 }
	 case SKILL://使用技能
		 {
			  AL_STRUCT *_AL_STRUCT = (AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_SKILL(_AL_STRUCT->Param1,_AL_STRUCT->Param2);
			 break;
		 }
	 case ACQUITST://采集
		 {
			 int DoorID = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_ACQUIST(DoorID);
			 break;
		 }
	 case PICKUPGOOD://拾取物品
		 {
			 PickCall_Struct *_PickCall_Struct = (PickCall_Struct *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_PICKUP(_PickCall_Struct->pickID,_PickCall_Struct->pickUpGoodID);
			 break;
		 }
	 case ACCPET_TASK_BUFFER://封包接任务
		 {
			 AL_STRUCT *_AL_STRUCT = (AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_ACCPET_TASK(_AL_STRUCT->Param1,_AL_STRUCT->Param2);
			 break;
		 }
	 case FINSH_TASK_BUFFER://封包交任务
		 {
			 AL_STRUCT *_AL_STRUCT = (AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_FINSH_TASK(_AL_STRUCT->Param1,_AL_STRUCT->Param2);
			 break;
		 }
	 case FINSH_TASK_BUFFER_EX://封包交任务,选择物品
		 {
			 AL_STRUCT_THREAD *_AL_STRUCT_THREAD = (AL_STRUCT_THREAD *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_FINSH_TASK_BY_SELECT(_AL_STRUCT_THREAD->Param1,_AL_STRUCT_THREAD->Param2,_AL_STRUCT_THREAD->Param3);
			 break;
		 }
	 case OPEN_NPC://打开NPC
		 {
			 int NPCID = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_OPEN_NPC(NPCID);
			 break;
		 }
	 case BUY_GOOD://买东西
		 {
			 struct Buy_Good_Struct *_Buy_Good_Struct = (struct Buy_Good_Struct *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_BUY_GOOD(_Buy_Good_Struct);
			 break;
		 }
	 case OPEN_SHOP://打开商店
		 {
			 int ShopNum = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_OPEN_SHOP(ShopNum);
			 break;
		 }
	 case NPC_TASK_TALK_SUB://任务二级对话
		 {
			 AL_STRUCT *_AL_STRUCT = (AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_TASK_NPC_TALK(_AL_STRUCT->Param1,_AL_STRUCT->Param2);
			 break;
		 }
	 case USE_GOOD://使用物品
		 {
			 struct USE_GOOD_PARAM_STRUCT *_USE_GOOD_PARAM_STRUCT = (struct USE_GOOD_PARAM_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_USE_GOOD(_USE_GOOD_PARAM_STRUCT->PercelIndex,_USE_GOOD_PARAM_STRUCT->PackIndex);
			 break;
		 }
	 case WEAR_GOOD://穿戴物品
		 {
			 struct USE_GOOD_PARAM_STRUCT *_USE_GOOD_PARAM_STRUCT = (struct USE_GOOD_PARAM_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_WEAR_GOOD(_USE_GOOD_PARAM_STRUCT->GoodID,_USE_GOOD_PARAM_STRUCT->PercelIndex,_USE_GOOD_PARAM_STRUCT->PackIndex);
			 break;
		 }
	 case WEAR_HORSE://穿戴马匹
		 {
			 struct USE_GOOD_PARAM_STRUCT *_USE_GOOD_PARAM_STRUCT = (struct USE_GOOD_PARAM_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_WEAR_HORSE(_USE_GOOD_PARAM_STRUCT->GoodID,_USE_GOOD_PARAM_STRUCT->PercelIndex,_USE_GOOD_PARAM_STRUCT->PackIndex);
			 break;
		 }
	 case PICKUPGLOD://拾取金币
		 {
			 int PickID = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_PICKUP_GLOD(PickID);
			 break;
		 }
	 case ROLEJMP://人物跳CALL
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_ROLE_JMP();
			 break;
		 }
	 case ROLEDODGE://轻功CALL
		 {
			 int OffOrOn = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_ROLE_DODGE(OffOrOn);
			 break;
		 }
	 case CANCEL_SET_DOWN://取消打坐CALL
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_CANCEL_SET_DOWN();
			 break;
		 }
	 case KEY_ACTION_F_UP://按键CALL F
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_KEY_F_UP();
			 break;
		 }
	 case KEY_ACTION_F_DOWN://按键CALL F
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_KEY_F_DOWN();
			 break;
		 }
	 case KEY_ACTION_ESC_UP://按键CALL ESC
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_KEY_ESC_UP();
			 break;
		 }
	 case KEY_ACTION_ESC_DOWN://按键CALL ESC
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_KEY_ESC_DOWN();
			 break;
		 }
	 case KEY_ACTION_SPACE_UP://按键CALL SPACE
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_KEY_SPACE_UP();
			 break;
		 }
	 case KEY_ACTION_SPACE_DOWN://按键CALL SPACE
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_KEY_SPACE_DOWN();
			 break;
		 }
	 case TRAN_ACTION://转向CALL
		 {
			 double *tranValue = (double *)lParam;
			 double valueTran = *tranValue;
			 CCCall _CCCall;
			 _CCCall.CALL_TRUN(valueTran);
			 break;
		 }
	 case DISTORY_GOOD://销毁物品
		 {
			 AL_STRUCT *_AL_STRUCT = (AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_DISTORY_GOOD(_AL_STRUCT->Param1,_AL_STRUCT->Param2);
			 break;
		 }
	 case QUIT_TEAM_MESSAGE://退出组队
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_QUIT_THE_TEAM();
			 break;
		 }
	 case REQUEST_TEAM_MESSAGE://发起组队
		 {
			 struct REQUEST_TETHER_TEAM *_REQUEST_TETHER_TEAM = (struct REQUEST_TETHER_TEAM *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_REQUEST_TEAM(_REQUEST_TETHER_TEAM);
			 break;
		 }
	 case RESPONSE_TEAM_MESSAGE://接受组队
		 {
			 struct RESPONE_TETHER_TEAM *_RESPONE_TETHER_TEAM = (struct RESPONE_TETHER_TEAM *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_RESPONSE_TEAM(_RESPONE_TETHER_TEAM);
			 break;
		 }
	 case MAP_IN_RUN_TO://图内寻路
		 {
			 struct AL_STRUCT_THREAD *_AL_STRUCT_THREAD = (struct AL_STRUCT_THREAD *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_MAP_IN_RUN_TO(_AL_STRUCT_THREAD->Param1,_AL_STRUCT_THREAD->Param2,_AL_STRUCT_THREAD->Param3);
			 break;
		 }
	 case CHANGE_KUNG_FU://切换内功
		 {
			  int KungFuID = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_CHANGE_KUNG_FU(KungFuID);
			 break;
		 }
	 case INTERAVTIVE://交互CALL
		 {
			 struct INTERACTIVE_STRUCT *_INTERACTIVE_STRUCT = (struct INTERACTIVE_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_INTERACTIVE(_INTERACTIVE_STRUCT);
			 break;
		 }
	 case GET_REPAIR_PRICE://获取修理价格CALL
		 {
			 struct GET_REPIR_PRICE_STRUCT *_GET_REPIR_PRICE_STRUCT = (struct GET_REPIR_PRICE_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_GET_REPAIR_PRICE(_GET_REPIR_PRICE_STRUCT);
			 break;
		 }
	 case GET_GOOD_PRICE://获取价格CALL
		 {
			 struct GET_REPIR_PRICE_STRUCT *_GET_REPIR_PRICE_STRUCT = (struct GET_REPIR_PRICE_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_GET_PARE_PRICE(_GET_REPIR_PRICE_STRUCT);
			 break;
		 }
	 case REPAIR_WEAR://修理全部装备CALL
		 {
			 struct AL_STRUCT *_AL_STRUCT = (struct AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_REPAIR_WEAR(_AL_STRUCT->Param1,_AL_STRUCT->Param2);
			 break;
		 }
	 case SKILL_UP_LEVEL://升级技能CALL
		 {
			 struct AL_STRUCT_THREAD *_AL_STRUCT_THREAD = (struct AL_STRUCT_THREAD *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_SKILL_UP(_AL_STRUCT_THREAD->Param1,_AL_STRUCT_THREAD->Param2,_AL_STRUCT_THREAD->Param3);
			 break;
		 }
	 case SKILL_MAKE_POINT://定点使用技能CALL
		 {
			 struct AL_STRUCT_FIVE *_AL_STRUCT_FIVE = (struct AL_STRUCT_FIVE *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_SKILL_MAKE_POINT(_AL_STRUCT_FIVE->Param1,_AL_STRUCT_FIVE->Param2,_AL_STRUCT_FIVE->Param3,_AL_STRUCT_FIVE->Param4,_AL_STRUCT_FIVE->Param5);
			 break;
		 }
	 case SPECIL_SET://奇穴设置
		 {
			 struct AL_STRUCT *_AL_STRUCT = (struct AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_SPECIL_SET(_AL_STRUCT->Param1,_AL_STRUCT->Param2);
			 break;
		 }
	 case ORGAN_RUN_MOVE://机关任务
		 {
			 int SelectIndex = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_ORGAN_MOVE(SelectIndex);
			 break;
		 }
	 case MONSTER_VIEW://怪物视野
		 {
			 struct AL_STRUCT_FOUR *_AL_STRUCT_FOUR = (struct AL_STRUCT_FOUR *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_MONSTER_VIEW_SHOW(_AL_STRUCT_FOUR);
			 break;
		 }
	 case OBJECT_TYPE_RET://对象类型
		 {
			 struct AL_STRUCT *_AL_STRUCT = (struct AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_OBJECT_TYPE_RET(_AL_STRUCT);
			 break;
		 }
	 case WEAR_THOUSANDS://装备千机
		 {
			 struct AL_STRUCT_FOUR *_AL_STRUCT_FOUR = (struct AL_STRUCT_FOUR *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_WEAR_THOUSADNS(_AL_STRUCT_FOUR->Param1,_AL_STRUCT_FOUR->Param2,_AL_STRUCT_FOUR->Param3,_AL_STRUCT_FOUR->Param4);
			 break;
		 }
	 case DELETE_TASK_BUFFER://放弃任务
		 {
			 int _index = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_DELETE_TASK(_index);
			 break;
		 }
	 case SHEN_XING_QIN_LI://神行千里
		 {
			 struct AL_STRUCT *_AL_STRUCT = (struct AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_SHEN_XING_QIAN_LI(_AL_STRUCT->Param1,_AL_STRUCT->Param2);
			 break;
		 }
	 case USE_PACKET://使用礼包
		 {
			 struct AL_STRUCT *_AL_STRUCT = (struct AL_STRUCT *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_USE_PACKET(_AL_STRUCT->Param1,_AL_STRUCT->Param2);
			 break;
		 }
	 case SELL_GOOD://卖物
		 {
			 struct AL_STRUCT_FOUR *_AL_STRUCT_FOUR = (struct AL_STRUCT_FOUR *)lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_SELL_GOOD(_AL_STRUCT_FOUR);
			 break;
		 }
	 case INTERAVTIVE_SHUA_MUTONG://刷木童
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_INTERACTIVE_MUTONG();
			 break;
		 }
	 case INTERAVTIVE_DENGGAO://登高
		 {
			 CCCall _CCCall;
			 _CCCall.CALL_INTERACTIVE_DENGGAO();
			 break;
		 }
	 case MAP_CHANGE_MOVE://过图CALL
		 {
			 int MapID = lParam;
			 CCCall _CCCall;
			 _CCCall.CALL_PASS_MAP(MapID);
			 break;
		 }
	 }
	 re= CallWindowProc((WNDPROC)lwndProc,hwnd, uMsg, wParam,lParam);  
	 return re;  
 }