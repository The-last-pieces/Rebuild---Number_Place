#pragma once
#include "Game_Global.h"
//�����������,��װΪһ��ȫ��API
class GTalker
{
private:
	//Ψһʵ��������,������ȷ��
	static GTalker* Instance;
	//��������Զ�����
	class autodelete {
	public:
		~autodelete()
		{
			if (GTalker::Instance)
			{
				delete GTalker::Instance;
				GTalker::Instance = nullptr;
			}
		}
	}Killer;
private:
	//��ֹ������޸Ķ���
	GTalker()
	{
		//��update�������߳���
	}
	~GTalker()
	{
		//�ͷ��߳���Դ
	}
	GTalker(const GTalker&) = delete;
public:
	static GTalker* getInstance()
	{
		//����ÿ��GInputͬ��
		return Instance;
	}
	//����string������Ⱦͼ��
	void Render(vector<string> info);//��Ⱦ��
};

#define GOutput GTalker::getInstance()
