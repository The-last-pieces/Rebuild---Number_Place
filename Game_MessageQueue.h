#pragma once
#include "Game_Global.h"
class GMessageQueue
{
	friend class autodelete;//�Զ�����
public:
	static GMessageQueue* getInstance()
	{
		//����ÿ��GInputͬ��
		if (!Instance)
			Instance = new GMessageQueue;
		return Instance;
	}
	void AddMsg(GB_Msg info);
	GB_Msg PopMsg();
private:
	//Ψһʵ��������,������ȷ��
	static GMessageQueue* Instance;
	//��Ϣ����
	queue<GB_Msg> MQueue;
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
};

#define GMsg GMessageQueue::getInstance()
