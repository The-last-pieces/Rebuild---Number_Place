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
	const int between_point = 4;//�α���
	
	thread keepback;
	thread keeppaint;
	bool OnPaint = false;

private:
	/*vector<string> getbackstring()
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
	}*/
private:
	static int vertical();
	static int horizontal();
	static void moveto(GPoint pos)
	{
		COORD temp;
		temp.X = (SHORT)pos.Vertical;
		temp.Y = (SHORT)pos.Horizontal;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
	}
	void DealInfo(GO_Msg& info);//��ʽ������

	template<typename T>
	static void outstring(const T& what)
	{
		cout << what;
		OnPaint = false;
	}

	static queue<GO_Msg> showqueue;
	static void Painter()
	{
		while (true)
		{
			if (showqueue.empty())
				continue;
			for (const auto& node : showqueue.front().AllStrings)
			{
				moveto(node.pos);
				cout << node.StrView;
			}
			showqueue.pop();
		}
	}
private:
	//��ֹ������޸Ķ���
	GTalker() :keeppaint(Painter), keepback(backgroud)
	{
		//a.empty();
		system("mode con lines=30 cols=90");
		keepback.detach();
		keeppaint.detach();
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
		if (!Instance)
			Instance = new GTalker;
		return Instance;
	}
	//����string����Ⱦͼ��
	void Render(GO_Msg info);//��Ⱦ��
	static void backgroud();
};

#define GOutput GTalker::getInstance()
