#pragma once
#include "Game_Global.h"
//处理输出请求,封装为一个全局API
class GTalker
{
	friend class autodelete;//自动销毁
private:
	//唯一实例化对象,编译期确定
	static GTalker* Instance;
private:
	//防止意外的修改对象
	GTalker()
	{
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
	//根据string数组渲染图像
	void Render(vector<string> info);//渲染器
};

#define GOutput GTalker::getInstance()
