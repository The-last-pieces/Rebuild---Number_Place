#pragma once
#include "Game_MessageQueue.h"
//处理输出请求,封装为一个全局API
class GTalker
{
	friend class autodelete;//自动销毁
private:
	//唯一实例化对象,编译期确定
	static GTalker* Instance;
private:
	const int between_point = 4;//游标间距

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
	void DealInfo(GO_Msg& info);//格式化处理

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
	//防止意外的修改对象
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
		//释放线程资源
	}
	GTalker(const GTalker&) = delete;
public:
	static queue<GO_Msg> mapqueue;

	static GTalker* getInstance()
	{
		//保持每个GInput同步
		if (!Instance)
			Instance = new GTalker;
		return Instance;
	}
	//根据string串渲染图像
	void Render(GO_Msg info);//渲染器
	static void backgroud();
};

#define GOutput GTalker::getInstance()
