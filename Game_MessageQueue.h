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
	queue<G_MsgInfo> MQueue;
public:
	static GMessageQueue* getInstance()
	{
		//保持每个GInput同步
		return Instance;
	}
	void AddMsg(G_MsgInfo info);
	G_MsgInfo PopMsg();
};

#define GMsg GMessageQueue::getInstance()