#pragma once
#include "Game_Global.h"

//�����û�����,��װΪһ��ȫ��API
class GListener
{
	friend class autodelete;//�Զ�����
private:
	//Ψһʵ��������,������ȷ��
	static GListener* Instance;
private:
	//��ֹ������޸Ķ���
	GListener()
	{
		//��update�������߳���
	}
	~GListener()
	{
		//�ͷ��߳���Դ
	}
	GListener(const GListener&) = delete;
public:
	//���ڴ��浱ǰ����������
	G_InputInfo Info;
public:
	static GListener* getInstance()
	{
		//����ÿ��GInputͬ��
		return Instance;
	}
	//������������,��Ϊ�ɽ��ܵ������򷵻�true
	bool Update(void);
};

#define GInput GListener::getInstance()
