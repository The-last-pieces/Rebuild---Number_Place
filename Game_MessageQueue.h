#pragma once
#include "Game_Global.h"
class GMessageQueue
{
private:
	//Ψһʵ��������,������ȷ��
	static GMessageQueue* Instance;
	//��������Զ�����
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
	//��ֹ������޸Ķ���
	GMessageQueue()
	{
		//��update�������߳���
	}
	~GMessageQueue()
	{
		//�ͷ��߳���Դ
	}
	GMessageQueue(const GMessageQueue&) = delete;
public:
	//��Ϣ����
	queue<G_MsgInfo> MQueue;
public:
	static GMessageQueue* getInstance()
	{
		//����ÿ��GInputͬ��
		return Instance;
	}
	void AddMsg(G_MsgInfo info);
	G_MsgInfo PopMsg();
};

#define GMsg GMessageQueue::getInstance()