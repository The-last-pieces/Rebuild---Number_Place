#pragma once
#include "Game_Global.h"
class GMessageQueue
{
	friend class autodelete;//自动销毁
private:
	//唯一实例化对象,编译期确定
	static GMessageQueue* Instance;
private:
	//防止意外的修改对象
	GMessageQueue()
	{
		//将update加入子线程中
	}
	~GMessageQueue()
	{
		//释放线程资源
	}
	GMessageQueue(const GMessageQueue&) = delete;
public:
	//消息队列
	queue<GB_Msg> MQueue;
public:
	static GMessageQueue* getInstance()
	{
		//保持每个GInput同步
		if (!Instance)
			Instance = new GMessageQueue;
		return Instance;
	}
	void AddMsg(GB_Msg info);
	GB_Msg PopMsg();
};

#define GMsg GMessageQueue::getInstance()

GB_Msg CreateMsg(double sleeptime);//Sleep信息
GB_Msg CreateMsg(GResType ptr);//Change_View信息
GB_Msg CreateMsg(ExInfo::NumInfo numinfo);//Set_Num信息
GB_Msg CreateMsg(GSetType mode, GMType mtype);//Change_Mode信息
GB_Msg CreateMsg(GMType mtype);//普通信息