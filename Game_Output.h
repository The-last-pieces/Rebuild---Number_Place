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
	static void ClearQueue(queue<GO_Msg>& tclear)
	{
		if (tclear.empty())
			return;
		auto temp = tclear.front().AllStrings;
		for (size_t index = 0; index < temp.size(); ++index)
		{
			moveto(temp[index].pos);
			cout << temp[index].StrView;
		}
		tclear.pop();
	}
	static void Painter()
	{
		while (true)
		{
			ClearQueue(showqueue);
			ClearQueue(mapqueue);
		}
	}
private:
	//��ֹ������޸Ķ���
	GTalker() :keeppaint(Painter), keepback(backgroud)
	{
		//a.empty();
		system("mode con lines=30 cols=90");
		SetConsoleTitle(L"Sudoku");
		keepback.detach();
		keeppaint.detach();
	}
	~GTalker()
	{
		//�ͷ��߳���Դ
	}
	GTalker(const GTalker&) = delete;
public:
	static queue<GO_Msg> mapqueue;

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
