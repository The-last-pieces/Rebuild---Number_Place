#pragma once
#include "Game_MessageQueue.h"
//�����������,��װΪһ��ȫ��API
class GTalker
{
	friend class autodelete;//�Զ�����
private:
	//Ψһʵ��������,������ȷ��
	static GTalker* Instance;
private:
	//������ͼ��Χ
	//int Height = 20;//���¾����
	//int Width = 80;//���Ҿ����

	//��֤�������
	//const int up_down = 3;//���¼��
	//const int left_right = 30;//���Ҽ��

	string backstring = "@%&";//"--��Ȩ����--���֮��--";
	const int between_point = 4;//�α���
private:
	vector<string> getbackstring()
	{
		string temp;
		vector<string>result;
		for (int index = 0; index<int(backstring.size()); ++index)
		{
			temp.push_back(backstring[index]);
			if (backstring[index] < 0)
			{
				temp.push_back(backstring[++index]);
			}
			result.push_back(temp);
			temp.clear();
		}
		return result;
	}
private:
	int vertical()
	{
		return GInput->Info.screensize.Vertical;
	}
	int horizontal()
	{
		return GInput->Info.screensize.Horizontal;
	}
	void moveto(GPoint pos)
	{
		COORD temp;
		temp.X = pos.Vertical;
		temp.Y = pos.Horizontal;
		SetConsoleCursorPosition(GInput->Info.winhandle, temp);
	}
	void SmartRender(const GO_Msg& info);
	void DealInfo(GO_Msg& info);//��ʽ������
private:
	//��ֹ������޸Ķ���
	GTalker()
	{
		system("mode con lines=30 cols=90");
		system("color e9");
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
	//����string����Ⱦͼ��
	void Render(GO_Msg info);//��Ⱦ��
	void backgroud();

};

#define GOutput GTalker::getInstance()
