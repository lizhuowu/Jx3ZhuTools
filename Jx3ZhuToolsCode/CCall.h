#pragma once


class CCCall
{
public:
	CCCall(void);
	~CCCall(void);
	//鼠标寻路
	void MoveTo(int MoveToX,int MoveToY);
	//使用技能CALL
	void CALL_SKILL(int SkillID,int SkillLevel);
	//选怪CALL
	void CALL_SELECT_MONSTGER(int MonsterID);
	//采集CALL
	void CALL_ACQUIST(int DoorID);
	//拾取物品ID(不能拾取金钱)
	void CALL_PICKUP(int PackID,int PickUpID);
	//明文包接任务
	//第一参数：任务ID，第二个参数：NPC ID
	void CALL_ACCPET_TASK(int TASK_ID,int NPC_ID);
	//明文包交任务(不带奖励选择)
	//第一参数：任务ID，第二个参数：NPC ID
	void CALL_FINSH_TASK(int TASK_ID,int NPC_ID);
	//选择物品交任务
	void CALL_FINSH_TASK_BY_SELECT(int TASK_ID,int NPC_ID,int SelectIndex);
	//放弃任务明文
	//参数：任务索引
	void CALL_DELETE_TASK(int _Index);
	//打开NPC 对话
	//参数：NPCID
	void CALL_OPEN_NPC(int NPCID);
	//买物品CALL
	void CALL_BUY_GOOD(struct Buy_Good_Struct *__Buy_Good_Struct);
	//打开商店
	//参数，商店编号
	void CALL_OPEN_SHOP(int ShopNum);
	//任务二级对话
	void CALL_TASK_NPC_TALK(int talkIndex, int TalkID);
	//使用物品CALL
	//参数1.包裹索引 2.背包格子索引
	void CALL_USE_GOOD(int PercelIndex,int PacktIndex);
	//穿戴物品CALL
	//参数1.穿戴位置2.包裹索引3.格子索引
	void CALL_WEAR_GOOD(int WearIndex,int PercelIndex,int PackIndex);
	//穿戴马匹CALL
	//参数1.穿戴位置2.包裹索引3.格子索引
	void CALL_WEAR_HORSE(int WearIndex,int PercelIndex,int PackIndex);
	//穿戴千机物品CALL
	//参数1.千机数量2.千机的索引3.格子索引4.包裹索引
	void CALL_WEAR_THOUSADNS(int ThousandsCount,int ThousandsIndex,int PackIndex,int PercelIndex);
	//拾取金币CALL
	//参数：要拾取的对象ID
	void CALL_PICKUP_GLOD(int PickupID);
	//人物跳CALL
	void CALL_ROLE_JMP();
	//轻功CALL
	//参数:1.开启，0.关闭
	void CALL_ROLE_DODGE(int OffOrOn);
	//取消打坐CALL
	void CALL_CANCEL_SET_DOWN();
	//按键CALL(按下)
	//参数：按键值
	void CALL_KEY_F_UP();
	//按键CALL(抬起)
	//参数：按键值
	void CALL_KEY_F_DOWN();
	//按键CALL(抬起)
	//参数：ESC 按键值
	void CALL_KEY_ESC_UP();
	//参数：ESC 按键值
	void CALL_KEY_ESC_DOWN();
	//按键CALL(抬起)
	//参数：SPACE 按键值
	void CALL_KEY_SPACE_UP();
	//按键CALL(按下)
	//参数：SPACE 按键值
	void CALL_KEY_SPACE_DOWN();
	//转向CALL
	//参数：转向角度
	void CALL_TRUN(double trnValue);
	//销毁物品CALL
	//参数1.格子索引，2.包裹索引
	void CALL_DISTORY_GOOD(int _packIndex,int _percelIndex);
	//退出组队
	void CALL_QUIT_THE_TEAM();
	//发起组队CALL
	//参数：组队结构
	void CALL_REQUEST_TEAM(struct REQUEST_TETHER_TEAM *_REQUEST_TETHER_TEAM);
	//接受组队
	//参数：接受组队结构
	void CALL_RESPONSE_TEAM(struct RESPONE_TETHER_TEAM *_RESPONE_TETHER_TEAM);
	//图内寻路CALL
	//三个参数是录制时自己记录
	void CALL_MAP_IN_RUN_TO(int Param1,int Param2,int Param3);
	//切换内功CALL
	//参数：内功ID
	void CALL_CHANGE_KUNG_FU(int KungFuID);
	//交互CALL
	//参数：交互结构
	void CALL_INTERACTIVE(struct INTERACTIVE_STRUCT *_INTERACTIVE_STRUCT);
	//交互CALL 刷木童
	void CALL_INTERACTIVE_MUTONG();
	//交互CALL 唐门登高
	void CALL_INTERACTIVE_DENGGAO();
	//获取修理价格CALL
	void CALL_GET_REPAIR_PRICE(struct GET_REPIR_PRICE_STRUCT *_GET_REPIR_PRICE_STRUCT);
	//获取价格CALL
	void CALL_GET_PARE_PRICE(struct GET_REPIR_PRICE_STRUCT *_GET_REPIR_PRICE_STRUCT);
	//修理全部装备
	//参数1：全部价格
	//参数2：商店编号
	void CALL_REPAIR_WEAR(int AllPrice,int ShopID);
	//升级技能CALL
	//参数1：需要的修为
	//参数2：技能等级
	//参数3：技能ID
	void CALL_SKILL_UP(int NeedXiuWei,int Level,int SkillID);
	//定点使用技能
	//参数1.释放点X 2.释放点Y 3.释放点Z 4.技能等级 5.技能ID
	void CALL_SKILL_MAKE_POINT(int PointX,int PointY,int PointZ,int SkillLevel,int SkillID);
	//奇穴设置
	void CALL_SPECIL_SET(int Param1,int Param2);
	//机关任务移动CALL
	//参数：点击的选项
	void CALL_ORGAN_MOVE(int ClickIndex);

	//判断怪物是否在视野内
	//怪物ID，怪物对象，技能对象
	void CALL_MONSTER_VIEW_SHOW(struct AL_STRUCT_FOUR *_AL_STRUCT_FOUR);
	//判断类型CALL
	//通用类型结构
	void CALL_OBJECT_TYPE_RET(struct AL_STRUCT *_AL_STRUCT);
	//神行千里
	//参数1.地图代码 2.区域代码
	void CALL_SHEN_XING_QIAN_LI(int MapCode,int AreaCode);
	//使用礼包CALL
	//参数1.包裹索引2.格子索引
	void CALL_USE_PACKET(int PercelIndex,int PackIndex);
	//卖物品CALL
	void CALL_SELL_GOOD(struct AL_STRUCT_FOUR *_AL_STRUCT_FOUR);
	//过图CALL
	void CALL_PASS_MAP(int MapID);
};

