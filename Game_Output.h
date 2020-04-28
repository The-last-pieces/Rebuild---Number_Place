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
//public:
	void moveto(GPoint pos)
	{
		COORD temp;
		temp.X = pos.Vertical;
		temp.Y = pos.Horizontal;
		SetConsoleCursorPosition(GInput->Info.winhandle, temp);
	}
	void DealInfo(GO_Msg& info);//格式化处理
private:
	//防止意外的修改对象
	GTalker()
	{
		system("mode con lines=30 cols=90");
		system("color e9");
		//将update加入子线程中
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
