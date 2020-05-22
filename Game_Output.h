#pragma once
#include "Game_PInterface.h"
//处理输出请求,封装为一个全局API
class GTalker
{
	friend class autodelete;//自动销毁
public:
	static GTalker* getInstance()
	{
		//保持每个GInput同步
		if (!Instance)
			Instance = new GTalker;
		return Instance;
	}
	//根据string串渲染图像
	void Render(GO_Msg info);//渲染器的公用接口
private:
	//唯一实例化对象,编译期确定
	static GTalker* Instance;
	const int between_point = 4;//游标间距

	thread keepback;
	thread keeppaint;
	static queue<GO_Msg> showqueue;
	static mutex safelock;

	static bool OnRunning;
private:
	void DealInfo(GO_Msg& info);//格式化处理

	static void ClearQueue(queue<GO_Msg>& tclear)
	{
		//处理绘图信息
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
	static void Painter()//渲染器
	{
		while (OnRunning)
		{
			//保证数据安全
			safelock.lock();
			ClearQueue(showqueue);
			safelock.unlock();
		}
	}
	static void backgroud();//生成背景
private:
	//防止意外的修改对象
	GTalker() :keeppaint(Painter), keepback(backgroud)
	{
		system("mode con lines=30 cols=90");
		SetConsoleTitle(TEXT("Sudoku"));

		mciSendStringW(L"setaudio mp3 volume to 50", NULL, 0, NULL);
		PlayMusic(L"welcome.mp3", false);
		keepback.detach();
		keeppaint.detach();

		CONSOLE_CURSOR_INFO CursorInfo;
		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);//获取控制台光标信息
		CursorInfo.bVisible = false; //隐藏控制台光标
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CursorInfo);//设置控制台光标状态
	}
	~GTalker()
	{
		//释放线程资源
		OnRunning = false;
	}
	GTalker(const GTalker&) = delete;
};

#define GOutput GTalker::getInstance()
