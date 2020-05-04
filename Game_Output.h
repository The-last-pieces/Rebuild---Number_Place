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
	string backstring = "@%&";//"--版权所有--最后之作--";
	const int between_point = 4;//游标间距
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
		temp.X = (SHORT)pos.Vertical;
		temp.Y = (SHORT)pos.Horizontal;
		SetConsoleCursorPosition(GInput->Info.winhandle, temp);
	}
	void DealInfo(GO_Msg& info);//格式化处理
private:
	//防止意外的修改对象
	GTalker()
	{
		system("mode con lines=30 cols=90");
		system("color e9");
		//hOut[0] = GetStdHandle(STD_OUTPUT_HANDLE);
		//hOut[1] = CreateConsoleScreenBuffer(
		//	GENERIC_WRITE,//定义进程可以往缓冲区写数据
		//	FILE_SHARE_WRITE,//定义缓冲区可共享写权限
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
		//释放线程资源
	}
	GTalker(const GTalker&) = delete;
public:
	static GTalker* getInstance()
	{
		//保持每个GInput同步
		return Instance;
	}
	//根据string串渲染图像
	void Render(GO_Msg info);//渲染器
	void backgroud();

};

#define GOutput GTalker::getInstance()
