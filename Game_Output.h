#pragma once
#include "Game_PInterface.h"
//�����������,��װΪһ��ȫ��API
class GTalker
{
	friend class autodelete;//�Զ�����
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
private:
	//Ψһʵ��������,������ȷ��
	static GTalker* Instance;
	const int between_point = 4;//�α���

	thread keepback;
	thread keeppaint;
	static queue<GO_Msg> showqueue;
	static mutex safelock;
private:
	void DealInfo(GO_Msg& info);//��ʽ������

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
};

#define GOutput GTalker::getInstance()
