#pragma once
#include "Game_Global.h"

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
	G_InputInfo Info;
public:
	static GListener* getInstance()
	{
		//保持每个GInput同步
		return Instance;
	}
	//更新输入数据,若为可接受的输入则返回true
	bool Update(void);
};

#define GInput GListener::getInstance()
