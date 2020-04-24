#pragma once
#include "Game_MessageQueue.h"

//处理用户输入,封装为一个全局API
class GListener
{
	friend class autodelete;//自动销毁
private:
	//唯一实例化对象,编译期确定
	static GListener* Instance;
private:
	//防止意外的修改对象
	GListener()
	{
		//将update加入子线程中
	}
	~GListener()
	{
		//释放线程资源
	}
	GListener(const GListener&) = delete;
public:
	//用于储存当前的输入数据
	GI_Msg Info;
public:
	static GListener* getInstance()
	{
		//保持每个GInput同步
		return Instance;
	}
	//更新输入数据,若为可接受的输入则返回true
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
		GetConsoleCursorInfo(Info.winhandle, &CursorInfo);//获取控制台光标信息
		CursorInfo.bVisible = false; //隐藏控制台光标
		SetConsoleCursorInfo(Info.winhandle, &CursorInfo);//设置控制台光标状态

	}
};

#define GInput GListener::getInstance()
