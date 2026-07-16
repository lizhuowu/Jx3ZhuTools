#include "stdafx.h"
#include "CCommon.h"


CCCommon::CCCommon(void)
{
}


CCCommon::~CCCommon(void)
{
}
//取脚本运行目录
CString CCCommon::GetLuaRootPath ()
{
	char szPathTemp[512];
	CString RootPath;

	GetModuleFileName(GetModuleHandle("Jx3ZhuToolsCode.dll"), szPathTemp, 512);//取模块运行路径
	for (int i=strlen(szPathTemp); i>=0; i--)   //////去掉模块名，保存最终路径
	{    if (szPathTemp[i] == '\\')  
	{   
		szPathTemp[i] = '\0'; 
		break;
	}
	}
	RootPath = szPathTemp;
	RootPath = RootPath;
	return RootPath;
}
/************************************************************************/
/* 寻路相关                                                             */
/************************************************************************/
//判断是否寻路到
BOOLEAN CCCommon::IsRunOver(int MoveX,int MoveY,int RoleX,int RoleY)
{
	const int TempData = 30;
	BOOLEAN IsValue = (RoleX>=(MoveX-TempData) && RoleX<=(MoveX+TempData) && RoleY>=(MoveY-TempData) && RoleY<=(MoveY+TempData));
	return IsValue;
}
//堵塞寻路
BOOLEAN CCCommon::MoveTo(int MoveX,int MoveY)
{
	CString RunStr;
	RunStr.Format("开始寻路：%d - %d",MoveX,MoveY);
	OutputDebugString(RunStr.GetBuffer());
	CCUserInfo _CCUserInfo;
	BOOLEAN IsOK = FALSE;
	MOTO moto;
	moto.fMoveToX = (float)MoveX;
	moto.fMoveToY = (float)MoveY;
	moto.MoveToZ = 0;
	int RoleX = _CCUserInfo.getObjectPointX();
	int RoleY = _CCUserInfo.getObjectPointY();
	while(!IsRunOver(MoveX,MoveY,RoleX,RoleY)){
		SendMessageA (g_hGameHandle,MOVETO, 0, (LPARAM)&moto);
		RoleX = _CCUserInfo.getObjectPointX();
		RoleY = _CCUserInfo.getObjectPointY();
		Sleep(1500);
	}
	IsOK = TRUE;
	OutputDebugString("寻路结束");
	return IsOK;
}
//HOOK 轻功1
void CCCommon::HOOK_DODGE_1()
{
	//修改内存地址可读可写属性
	int Addr = (int)_CCGameWndProc->GetGameModuleAddr() + DODGE_HOOK_1;
	int Addr2 = (int)_CCGameWndProc->GetGameModuleAddr() + DODGE_HOOK_1+1;
	int Addr3 = (int)_CCGameWndProc->GetGameModuleAddr() + DODGE_HOOK_1+2;
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)Addr,16,PAGE_EXECUTE_READWRITE,&OldProtect);
	*(byte *)Addr = 0xC2;
	*(byte *)Addr2 = 0x04;
	*(byte *)Addr3 = 0x00;
	VirtualProtect((LPVOID)Addr,4,OldProtect,&OldProtect);
}
//HOOK 轻功2
void CCCommon::HOOK_DODGE_2()
{
	//修改内存地址可读可写属性
	int Addr = (int)_CCGameWndProc->GetGameModuleAddr() + DODGE_HOOK_2;
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)Addr,4,PAGE_EXECUTE_READWRITE,&OldProtect);
	*(byte *)Addr = 0xEB;
	VirtualProtect((LPVOID)Addr,4,OldProtect,&OldProtect);
}
//修理全部装备
void CCCommon::RepairWear()
{
	//先获取身上装备价格
	//获取打开商店的ECX
	if (HOOKText == "HOOKTEXT")
	{
		OutputDebugString("修理装备失败，请先打开NPC对话!");
		return;
	}
	int SHOP_NUM = -1;
	int iPos = 0, iPos2 = 0;
	iPos = HOOKText.find ("M ");
	iPos2 = HOOKText.find (" ", iPos + 2);
	string currentStr = HOOKText.substr (iPos + 2, iPos2 - (iPos + 2));
	SHOP_NUM = _ttoi(currentStr.c_str());
	int _ECX = GetShopAddr(SHOP_NUM);
	/************************************************************************/
	/* 穿戴装备价格                                                         */
	/************************************************************************/
	CCRoleWear _CCRoleWear;
	CCPackArray _CCPackArray(_CCRoleWear.getAddr());
	int Count = _CCPackArray.getCount();
	int AllPrice = 0;
	for (int i = 0;i<Count;i++)
	{
		int Addr = _CCPackArray.getAddrByIndex(i);
		if (Addr > 0)
		{
			GET_REPIR_PRICE_STRUCT _GET_REPIR_PRICE_STRUCT;
			_GET_REPIR_PRICE_STRUCT.PercelIndex = 0;
			_GET_REPIR_PRICE_STRUCT.PackIndex = i;
			_GET_REPIR_PRICE_STRUCT._Ecx = _ECX;
			SendMessageA (g_hGameHandle,GET_REPAIR_PRICE, 0, (LPARAM)&_GET_REPIR_PRICE_STRUCT);
			if (_GET_REPIR_PRICE_STRUCT.Price > 0)
			{
				AllPrice = AllPrice + _GET_REPIR_PRICE_STRUCT.Price;
			}
		}
	}
	/************************************************************************/
	/* 背包中的装备                                                         */
	/************************************************************************/
	CCPackPercelArray _CCPackPercelArray;
	int CountArrayPercel = _CCPackPercelArray.getCount();
	for (int i = 0;i < CountArrayPercel;i++)
	{
		int PacketStart = _CCPackPercelArray.getAddrByIndex(i);
		if (PacketStart > 0)
		{
			CCPackArray _CCPackArray(PacketStart);
			int PacketCount = _CCPackArray.getCount();
			for (int j = 0;j < PacketCount;j++)
			{
				int PacketObjectAddr = _CCPackArray.getAddrByIndex(j);
				if (PacketObjectAddr > 0 )
				{
					int Percel_Current_index = i + 1;
					int Packet_index = j;
					GET_REPIR_PRICE_STRUCT _GET_REPIR_PRICE_STRUCT;
					_GET_REPIR_PRICE_STRUCT.PercelIndex = Percel_Current_index;
					_GET_REPIR_PRICE_STRUCT.PackIndex = Packet_index;
					_GET_REPIR_PRICE_STRUCT._Ecx = _ECX;
					SendMessageA (g_hGameHandle,GET_REPAIR_PRICE, 0, (LPARAM)&_GET_REPIR_PRICE_STRUCT);
					if (_GET_REPIR_PRICE_STRUCT.Price > 0)
					{
						AllPrice = AllPrice + _GET_REPIR_PRICE_STRUCT.Price;
					}
				}
			}
		}
	}
	//修理全部装备
	AL_STRUCT _AL_STRUCT;
	_AL_STRUCT.Param1 = AllPrice;
	_AL_STRUCT.Param2 = SHOP_NUM;
	SendMessageA (g_hGameHandle,REPAIR_WEAR, 0, (LPARAM)&_AL_STRUCT);
}
//根据商店ID 获取商店地址
int CCCommon::GetShopAddr(int ShopID)
{
		int ShopAddr = 0; 
		CCShopTree _CCShopTree;
		int count = _CCShopTree.getAllShopCount();
		for (int i = 0;i < count;i++)
		{
			int StartAddr = _CCShopTree.getAddrByIndex(i);
			if (StartAddr > 0)
			{
				CCShopTreeObject _CCShopTreeObject(StartAddr);
				if (_CCShopTreeObject.getShopID() == ShopID)
				{
					ShopAddr =  _CCShopTreeObject.getShopAddr();
					break;
				}
			}
		}
		return ShopAddr;
}


//机关任务
void CCCommon::OrganMoveSucess()
{
	if (HOOKText == "HOOKTEXT")
	{
		OutputDebugString("机关任务失败，请先打开NPC对话!");
		return;
	}
	int weizhi1 = 0, weizhi2 = 0;
	int a[4] = {0, 0, 0, 0}, b[4] = {0, 0, 0, 0}, c[4] = {0, 0, 0, 0}, d[4] = {0, 0, 0, 0}, juli[4] = {0, 0, 0, 0}, i = 0;
	string tmp_Str = "";
	if (HOOKText != "HOOKTEXT") 
	{
		for (i = 0; i < 9; i++)
		{
			weizhi1 = HOOKText.find ("T ", weizhi1);
			weizhi2 = HOOKText.find (">", weizhi1 + 2);
			tmp_Str = HOOKText.substr (weizhi1 + 2, weizhi2 - weizhi1 - 2);
			weizhi1++;
			if (tmp_Str == "")
			{
				break;
			}
			switch (i)
			{
			case 0:{
				a[0] = _ttoi (tmp_Str.c_str());
				break;
				   }

			case 1: {
				a[1] = _ttoi (tmp_Str.c_str());
				b[0] = _ttoi (tmp_Str.c_str());
				break;
					}

			case 2: {
				b[1] = _ttoi (tmp_Str.c_str());
				break;
					}

			case 3: {
				a[3] = _ttoi (tmp_Str.c_str());
				c[0] = _ttoi (tmp_Str.c_str());
				break;
					}

			case 4: {
				a[2] = _ttoi (tmp_Str.c_str());
				b[3] = _ttoi (tmp_Str.c_str());
				c[1] = _ttoi (tmp_Str.c_str());
				d[0] = _ttoi (tmp_Str.c_str());
				break;
					}

			case 5: {
				b[2] = _ttoi (tmp_Str.c_str());
				d[1] = _ttoi (tmp_Str.c_str());
				break;
					}

			case 6: {
				c[3] = _ttoi (tmp_Str.c_str());
				break;
					}

			case 7: {
				c[2] = _ttoi (tmp_Str.c_str());
				d[3] = _ttoi (tmp_Str.c_str());
				break;
					}

			case 8: {
				d[2] = _ttoi (tmp_Str.c_str());
				break;
					}
			default: break;
			}

		}

		if (a[0] != 0 && b[0] != 0 && c[0]!= 0 && d[0] != 0)
		{

			int aa = 0, bb = 0, lable1 = 0, lable2 = 0;
			for (aa = 0; aa < 4; aa++)
			{
				if (a[aa] == 3131)
				{
					lable1 = 1;
					break;
				}
			}

			for (bb = 0; bb < 4; bb++)
			{
				if (a[bb] == 3132)
				{
					lable2 = 1;
					break;
				}
			}

			if (lable1 == 1 && lable2 == 1)
			{
				juli[0] = bb - aa;
				if (juli[0] < 0)
				{
					juli[0] = juli[0] + 4;	
				}
			}


			aa = 0;
			bb = 0;
			lable1 = 0;
			lable2 = 0;
			for (aa = 0; aa < 4; aa++)
			{
				if (b[aa] == 3131)
				{
					lable1 = 1;
					break;
				}
			}

			for (bb = 0; bb < 4; bb++)
			{
				if (b[bb] == 3132)
				{
					lable2 = 1;
					break;
				}
			}

			if (lable1 == 1 && lable2 == 1)
			{
				juli[1] = bb - aa;
				if (juli[1] < 0)
				{
					juli[1] = juli[1] + 4;	
				}
			}


			aa = 0;
			bb = 0;
			lable1 = 0;
			lable2 = 0;
			for (aa = 0; aa < 4; aa++)
			{
				if (c[aa] == 3131)
				{
					lable1 = 1;
					break;
				}
			}

			for (bb = 0; bb < 4; bb++)
			{
				if (c[bb] == 3132)
				{
					lable2 = 1;
					break;
				}
			}

			if (lable1 == 1 && lable2 == 1)
			{
				juli[2] = bb - aa;
				if (juli[2] < 0)
				{
					juli[2] = juli[2] + 4;	
				}
			}


			aa = 0;
			bb = 0;
			lable1 = 0;
			lable2 = 0;
			for (aa = 0; aa < 4; aa++)
			{
				if (d[aa] == 3131)
				{
					lable1 = 1;
					break;
				}
			}

			for (bb = 0; bb < 4; bb++)
			{
				if (d[bb] == 3132)
				{
					lable2 = 1;
					break;
				}
			}

			if (lable1 == 1 && lable2 == 1)
			{
				juli[3] = bb - aa;
				if (juli[3] < 0)
				{
					juli[3] = juli[3] + 4;	
				}
			}

			aa = 0;
			bb = 0;
			for (aa = 0; aa < 4; aa++)
			{
				if (juli[aa] == 1)
				{
					bb = 1;
					int IndexSelect = aa;
					SendMessageA (g_hGameHandle,ORGAN_RUN_MOVE, 0, (LPARAM)IndexSelect);
					Sleep(300);
					break;
				}
			}


			if (bb == 0)
			{
				for (aa = 0; aa < 4; aa++)
				{
					if (juli[aa] == 2)
					{
						int IndexSelect = aa;
						SendMessageA (g_hGameHandle,ORGAN_RUN_MOVE, 0, (LPARAM)IndexSelect);
						Sleep(300);
						bb = 2;
						break;
					}
				}
			}

			if (bb == 0)
			{
				for (aa = 0; aa < 4; aa++)
				{
					if (juli[aa] == 3)
					{
						int IndexSelect = aa;
						SendMessageA (g_hGameHandle,ORGAN_RUN_MOVE, 0, (LPARAM)IndexSelect);
						Sleep(300);
						bb = 3;
						break;
					}
				}
			}
			bb = 0;
			if (juli[0] == 0 && juli [1] == 0 && juli [2] == 0 && juli[3] == 0)
			{
				int xiabiao = 0, tmp_xiabiao = 0;
				for (xiabiao = 0; xiabiao < 16; xiabiao++)
				{
					if (xiabiao < 4)
					{
						if (a[xiabiao] == 3131)
						{
							//OutputDebugString("执行1");
							int IndexSelect = 0;
							SendMessageA (g_hGameHandle,ORGAN_RUN_MOVE, 0, (LPARAM)IndexSelect);
							Sleep(300);
							break;
						}
					}else {
						if (xiabiao >= 4 && xiabiao < 8)
						{
							tmp_xiabiao = xiabiao - 4;
							if (b[tmp_xiabiao] == 3131)
							{
								//OutputDebugString("执行2");
								int IndexSelect = 1;
								SendMessageA (g_hGameHandle,ORGAN_RUN_MOVE, 0, (LPARAM)IndexSelect);
								Sleep(300);
								break;
							}
						}else {
							if (xiabiao >= 8 && xiabiao < 12)
							{
								tmp_xiabiao = xiabiao - 8;
								if (c[tmp_xiabiao] == 3131)
								{
									//OutputDebugString("执行3");
									int IndexSelect = 2;
									SendMessageA (g_hGameHandle,ORGAN_RUN_MOVE, 0, (LPARAM)IndexSelect);
									Sleep(300);
									break;
								}
							}else {
								if (xiabiao >= 12 && xiabiao < 16)
								{
									tmp_xiabiao = xiabiao - 12;
									if (d[tmp_xiabiao] == 3131)
									{
										//OutputDebugString("执行4");
										int IndexSelect = 3;
										SendMessageA (g_hGameHandle,ORGAN_RUN_MOVE, 0, (LPARAM)IndexSelect);
										Sleep(300);
										break;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
