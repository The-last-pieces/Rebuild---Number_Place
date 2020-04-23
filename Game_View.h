#pragma once
#include "Base_Lib.h"

//游戏视图

class GView
{
public:
	virtual vector<string> Stringify() = 0;
	virtual bool Behavior() = 0;
};

//一个选项,指向一个GView 指针 
//可以是任意GMenu */GPlay *
class GChoose :public GView
{
private:
	string Column;
	string Explanation;
private:
	GView* Link = nullptr;
};

//管理可由用户设置的参数
class GLable :public GView
{
	int Select = 0;
	typedef struct {
		string Column;
		string Explanation;
		GStatus Mode;
	}GSet;
private:
	vector<GSet>AllSettings;
};

//专用于游戏交互的类
class GPlay :public GView
{
	
};

//游戏目录 
//包含多个GChoose
class GMenu :public GView
{
private:
	vector<GChoose*>AllLinks;
public:
	const int length;
};