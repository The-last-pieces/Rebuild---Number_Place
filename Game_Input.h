#pragma once
#include "Game_Global.h"

//�����û�����,��װΪһ��ȫ��API
class GListener
{
private:
	//Ψһʵ��������,������ȷ��
	static GListener* Instance;
	//��������Զ�����
	class autodelete {
	public:
		~autodelete()
		{
			cout << "\nwwww\n";
			if (GListener::Instance)
			{
				delete GListener::Instance;
				GListener::Instance = nullptr;
			}
		}
	}Killer;
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
