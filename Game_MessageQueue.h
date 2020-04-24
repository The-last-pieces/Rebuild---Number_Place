#pragma once
#include "Game_Global.h"
class GMessageQueue
{
	friend class autodelete;//�Զ�����
private:
	//Ψһʵ��������,������ȷ��
	static GMessageQueue* Instance;
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
	queue<GB_Msg> MQueue;
public:
	static GMessageQueue* getInstance()
	{
		//����ÿ��GInputͬ��
		return Instance;
	}
	void AddMsg(GB_Msg info);
	GB_Msg PopMsg();
};

#define GMsg GMessageQueue::getInstance()