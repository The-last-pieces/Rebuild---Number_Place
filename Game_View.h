#pragma once
#include "Base_Lib.h"
//游戏视图类

class GView
{
public:
	bool OnMe = false;
	GResType Father = GResType::Menu_Main;
public:
	virtual GO_Msg Stringify() = 0;
	virtual bool Behavior() = 0;
	virtual ~GView() {}
};

//一个选项,指向一个GView 指针 
//可以是任意GMenu */GPlay */GText *

class GText:public GView
{
private:
	GO_Msg txt;
public:
	GText(GO_Msg _txt, GResType _Father) :txt(_txt) 
	{
		Father = _Father;
	}
	GO_Msg Stringify()
	{
		return txt;
	}
	bool Behavior()
	{
		switch (GInput->Info.intype)
		{
		case GIType::Back:
			GMsg->AddMsg(CreateMsg(Father));
			break;
		default:
			return false;
		}
		GMsg->AddMsg(CreateMsg(GMType::Rend));
		return true;
	}
};

class GChoose :public GView
{
private:
	string Column;
	string Explanation;
private:
	vector<GB_Msg> BondAction = { CreateMsg(GMType::NOP) };//绑定的附加事件
public:
	GChoose(string _Column, string _Explanation, vector<GB_Msg> _BondAction) :
		Column(_Column), Explanation(_Explanation), BondAction(_BondAction)
	{}

	string GetExplanation()
	{
		return Explanation;
	}
	GO_Msg Stringify()
	{
		GO_Msg info;
		string temp = Column;
		if (OnMe)
		{
			temp = string("--> ") + temp + string(" <--");
			info.AllStrings.push_back({ GetExplanation(),{},GOType::Explanation });
		}
		info.AllStrings.push_back({ temp });
		return info;
	}
	bool Behavior()
	{
		if (GInput->Info.intype == GIType::Confirm)
		{
			for (auto node : BondAction)
			{
				GMsg->AddMsg(node);
				//执行绑定的行为
			}
			GMsg->AddMsg(CreateMsg(GMType::Rend));
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
		GSetType Mode;
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
		GO_Msg info;
		string temp = AllSettings[NowSelect].Column;
		if (OnMe)
		{
			temp = string("--> ") + temp + string(" <--");
			info.AllStrings.push_back({ GetExplanation(),{},GOType::Explanation });
		}
		info.AllStrings.push_back({ temp });
		return info;
	}
	bool Behavior()
	{
		switch (GInput->Info.intype)
		{
		case GIType::Left_Lable:
			NowSelect = (NowSelect + SetsCount - 1) % SetsCount;
			break;
		case GIType::Right_Lable:
			NowSelect = (NowSelect + 1) % SetsCount;
			break;
		default:
			return false;
		}
		GMsg->AddMsg(CreateMsg(AllSettings[NowSelect].Mode, LableType));
		GMsg->AddMsg(CreateMsg(GMType::Rend));
		return true;
	}
};

//专用于游戏交互的类
class GPlay :public GView
{
	int ChooseNum = 0;
	GPoint ChoosePos;
private:
	GPoint TransformHit(GPoint pos)
	{
		GPoint rpt;
		int lr = (GInput->Info.screensize.Horizontal - 13) / 2;
		int ud = (GInput->Info.screensize.Vertical - 13) / 2;
		rpt.Vertical = pos.Vertical - lr;
		rpt.Horizontal = pos.Horizontal - ud;

		if (!(rpt.Horizontal % 4 && rpt.Vertical))
			return { -1,-1 };

		rpt.Vertical -= rpt.Vertical / 4 + 1;
		rpt.Horizontal -= rpt.Horizontal / 4 + 1;
		swap(rpt.Vertical, rpt.Horizontal);
		return rpt;
	}
public:
	GMap* OnMap = nullptr;
	bool startgame = false;

	void CreateMap(GSetType hard,GSetType mode)
	{
		OnMap = new GMap(hard,mode);
		GMsg->AddMsg(CreateMsg(GMType::Rend));
	}
	GO_Msg Stringify()
	{
		if (!OnMap)
			return {};

		GO_Msg mtemp = OnMap->Stringify();
		string stemp = "当前选择的数字为:";
		stemp.push_back(char(ChooseNum + '0'));
		mtemp.AllStrings.push_back({ stemp,{},GOType::GameHint });
		return mtemp;
	}
	bool Behavior()
	{
		if (!OnMap)
			return false;

		switch (GInput->Info.intype)
		{
		case GIType::Number:
			ChooseNum = GInput->Info.onkey - '0';
			break;
		case GIType::Back:
			GMsg->AddMsg(CreateMsg(Father));
			break;
		case GIType::Mouse_Left:
			ChoosePos = GInput->Info.mouse_pos;
			ChoosePos = TransformHit(ChoosePos);
			OnMap->SetNumber(ChoosePos, ChooseNum);
			break;
		case GIType::Confirm:
			OnMap->WorkOut();
			break;
		case GIType::Regret:
			OnMap->Back();
			break;
		default:
			return false;
		}
		if (OnMap->IsWin())
		{
			GOutput->Render(this->Stringify());

			GO_Msg msg;
			msg.AllStrings.push_back({ "你获得了游戏胜利,按任意键退出程序",{GInput->Info.screensize.Horizontal / 2 - 17,3},GOType::SelfDef });
			GOutput->Render(msg);

			GMsg->AddMsg(CreateMsg(GMType::Exit_Process));
			_getch();
		}
		else
			GMsg->AddMsg(CreateMsg(GMType::Rend));

		return true;
	}

	~GPlay()
	{
		if (OnMap)
		{
			delete OnMap;
			OnMap = nullptr;
		}
	}
};

//游戏目录 
//包含多个GChoose
class GMenu :public GView
{
private:
	vector<GView*>AllLinks;
	int NowSelect = 0;
	const int LinksCount;
public:
	GMenu(vector<GView*>_AllLinks, GResType  _Father = GResType::Menu_Main)
		:AllLinks(_AllLinks), LinksCount(_AllLinks.size())
	{
		Father = _Father;
		if (AllLinks.size())
			AllLinks[0]->OnMe = true;
	}
public:
	GO_Msg Stringify()
	{
		GO_Msg info;
		for (int i = 0; i < LinksCount; ++i)
		{
			//获取子控件的序列化字符串
			auto temp = AllLinks[i]->Stringify().AllStrings;
			info.AllStrings.insert(
				info.AllStrings.end(),
				temp.begin(),
				temp.end()
				);
		}
		return info;
	}
	bool Behavior()
	{
		if (!LinksCount)
			return false;
		int temp = NowSelect;
		bool rstatus = true;
		switch (GInput->Info.intype)
		{
		case GIType::Up_Page:
			NowSelect = (NowSelect + LinksCount - 1) % LinksCount;
			break;
		case GIType::Down_Page:
			NowSelect = (NowSelect + 1) % LinksCount;
			break;
		case GIType::Back:
			GMsg->AddMsg(CreateMsg(Father));
			break;
		default:
			rstatus = AllLinks[NowSelect]->Behavior();
			break;
		}

		AllLinks[temp]->OnMe = false;
		AllLinks[NowSelect]->OnMe = true;

		GMsg->AddMsg(CreateMsg(GMType::Rend));
		return rstatus;
	}
};