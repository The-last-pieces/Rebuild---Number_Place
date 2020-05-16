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

	static queue<GO_Msg> showqueue;
	static mutex safelock;
	static void ClearQueue(queue<GO_Msg>& tclear)
	{
		//�����ͼ��Ϣ
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
	static void Painter()//��Ⱦ��
	{
		while (true)
		{
			//��֤���ݰ�ȫ
			safelock.lock();
			ClearQueue(showqueue);
			safelock.unlock();
		}
	}
	static void backgroud();//���ɱ���
private:
	//��ֹ������޸Ķ���
	GTalker() :keeppaint(Painter), keepback(backgroud)
	{
		system("mode con lines=30 cols=90");
		SetConsoleTitle(TEXT("Sudoku"));
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
	void Render(GO_Msg info);//��Ⱦ���Ĺ��ýӿ�
};

#define GOutput GTalker::getInstance()
