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
	string backstring = "@%&";//"--��Ȩ����--���֮��--";
	const int between_point = 4;//�α���
	//HANDLE hOut[2] = {};
	//int activeh = 0;
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

	/*void transoutput();
	void clearhout(HANDLE hd);*/
//public:
	void moveto(GPoint pos)
	{
		COORD temp;
		temp.X = pos.Vertical;
		temp.Y = pos.Horizontal;
		SetConsoleCursorPosition(GInput->Info.winhandle, temp);
	}
	void DealInfo(GO_Msg& info);//��ʽ������
private:
	//��ֹ������޸Ķ���
	GTalker()
	{
		system("mode con lines=30 cols=90");
		system("color e9");
		//hOut[0] = GetStdHandle(STD_OUTPUT_HANDLE);
		//hOut[1] = CreateConsoleScreenBuffer(
		//	GENERIC_WRITE,//������̿�����������д����
		//	FILE_SHARE_WRITE,//���建�����ɹ���дȨ��
		//	NULL,
		//	CONSOLE_TEXTMODE_BUFFER,
		//	NULL
		//	);
		//CONSOLE_CURSOR_INFO cci;
		//cci.bVisible = 0;
		//cci.dwSize = 1;
		//SetConsoleCursorInfo(hOut[0], &cci);
		//SetConsoleCursorInfo(hOut[1], &cci);
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
