#pragma once
#include "Game_MessageQueue.h"

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
	GI_Msg Info;
public:
	static GListener* getInstance()
	{
		//����ÿ��GInputͬ��
		return Instance;
	}
	//������������,��Ϊ�ɽ��ܵ������򷵻�true
	bool Update(void);
public:
	inline HANDLE WinHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
	void updateWindowInfo()
	{
		Info.winhandle = WinHandle();

		CONSOLE_SCREEN_BUFFER_INFO Pif;
		GetConsoleScreenBufferInfo(Info.winhandle, &Pif);

		Pif.dwSize.X = Pif.srWindow.Right + 1;
		Pif.dwSize.Y = Pif.srWindow.Bottom + 1;

		if (Info.screensize.Horizontal != Pif.dwSize.X || Info.screensize.Vertical != Pif.dwSize.Y)
		{
			Info.screensize.Horizontal = Pif.dwSize.X;
			Info.screensize.Vertical = Pif.dwSize.Y;

			GMsg->AddMsg({ GMType::Clear });
		}
		SetConsoleScreenBufferSize(Info.winhandle, Pif.dwSize);

		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(Info.winhandle, &CursorInfo);//��ȡ����̨�����Ϣ
		CursorInfo.bVisible = false; //���ؿ���̨���
		SetConsoleCursorInfo(Info.winhandle, &CursorInfo);//���ÿ���̨���״̬

	}
};

#define GInput GListener::getInstance()
