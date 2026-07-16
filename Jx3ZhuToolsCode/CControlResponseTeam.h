#pragma once
class CCControlResponseTeam
{
private:
	int BASE_ADDR;
	int BASE_VALUE;
public:
	CCControlResponseTeam(void);
	~CCControlResponseTeam(void);
	//获取最后一个发起组队消息，并组队
	void GetLastTeamerAndResponse();
};

