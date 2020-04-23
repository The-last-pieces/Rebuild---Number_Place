#pragma once
#include "Game_Global.h"
class GMessageQueue
{
private:
	//唯一实例化对象,编译期确定
	static GMessageQueue* Instance;
	//程序结束自动销毁
	class autodelete {
	public:
		~autodelete()
		{
			cout << "\nwwww\n";
			if (GMessageQueue::Instance)
			{
				delete GMessageQueue::Instance;
				GMessageQueue::Instance = nullptr;
			}
		}
	}Killer;
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