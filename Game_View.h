#pragma once
#include "Base_Lib.h"

//游戏视图类

class GView
{
public:
	virtual GO_Msg Stringify() = 0;
	virtual bool Behavior() = 0;
};

//一个选项,指向一个GView 指针 
//可以是任意GMenu */GPlay *
class GChoose :public GView
{
public:
	bool OnMe = false;
private:
	string Column;
	string Explanation;
private:
	//GView* Link = nullptr;
	vector<GB_Msg> BondAction = { FormatMsg(GMType::NOP) };//绑定的附加事件
public:
	GChoose(string _Column, string _Explanation, GView* _Link, vector<GB_Msg> _BondAction) :
		Column(_Column), Explanation(_Explanation), BondAction(_BondAction)
	{}

	string GetExplanation()
	{
		return Explanation;
	}
	/*string GetColumn()
	{
		return Column;
	}*/
	GO_Msg Stringify()
	{
		GO_Msg info;
		info.AllStrings.push_back({ Column });
		return { {{Column}} };
	}
	bool Behavior()
	{
		if (GInput->Info.onkey == 13)
		{
			for (auto node : BondAction)
			{
				GMsg->AddMsg(node);
				//执行绑定的行为
			}
			return true;
		}
		return false;
	}
};

//管理可由用户设置的参数
class GLable :public GView
{
	int NowSelect = 0;
	typedef struct {
		string Column;
		string Explanation;
		GStatus Mode;
	}GSet;
	const int SetsCount;
private:
	vector<GSet>AllSettings;
	GMType LableType;
public:
	GLable(vector<GSet> _sets, GMType _LableType) :AllSettings(_sets), SetsCount(_sets.size()), LableType(_LableType) {}
public:
	string GetExplanation()
	{
		return AllSettings[NowSelect].Explanation;
	}
	GO_Msg Stringify()
	{
		return { {{AllSettings[NowSelect].Column}} };
	}
	bool Behavior()
	{
		switch (GInput->Info.onkey)
		{
		case 'a':
			NowSelect = (NowSelect + SetsCount - 1) % SetsCount;
			break;
		case 'd':
			NowSelect = (NowSelect + 1) % SetsCount;
			break;
		default:
			return false;
		}
		GMsg->AddMsg(FormatMsg(AllSettings[NowSelect].Mode, LableType));
		GMsg->AddMsg(FormatMsg(GMType::Rend));
		return true;
	}
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
	int NowSelect = 0;
	const int LinksCount;
public:
	GMenu(vector<GChoose*>_AllLinks)
		:AllLinks(_AllLinks), LinksCount(_AllLinks.size())
	{

	}
public:
	GO_Msg Stringify()
	{
		GO_Msg info;
		for (int i = 0; i < LinksCount; ++i)
		{
			//获取子控件的序列化字符串
			info.AllStrings.insert(
				info.AllStrings.end(),
				AllLinks[i]->Stringify().AllStrings.begin(),
				AllLinks[i]->Stringify().AllStrings.end()
				);
		}
		return info;
		//return { {{AllLinks[NowSelect].Column}} };
	}
	bool Behavior()
	{
		int temp = NowSelect;
		switch (GInput->Info.onkey)
		{
		case 'w':
			NowSelect = (NowSelect + LinksCount - 1) % LinksCount;
			break;
		case 's':
			NowSelect = (NowSelect + 1) % LinksCount;
			break;
		default:
			return AllLinks[NowSelect]->Behavior();
		}

		AllLinks[temp]->OnMe = false;
		AllLinks[NowSelect]->OnMe = true;

		GMsg->AddMsg({ GMType::Rend });
		return true;
	}
};