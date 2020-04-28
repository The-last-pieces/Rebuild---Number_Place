#include "Game_Input.h"
#include "Game_Output.h"

GB_Msg FormatMsg(void * ptr)
{
	GB_Msg rmsg;
	rmsg.type = GMType::Change_View;
	rmsg.ex.newshow = ptr;
	return rmsg;
}
GB_Msg FormatMsg(ExInfo::NumInfo numinfo)
{
	GB_Msg rmsg;
	rmsg.type = GMType::Change_View;
	rmsg.ex.setnum = numinfo;
	return rmsg;
}
GB_Msg FormatMsg(GStatus mode,GMType mtype)
{
	GB_Msg rmsg;
	rmsg.type = mtype;
	if (mtype == GMType::Change_Hard)
		rmsg.ex.hard = mode;
	if (mtype == GMType::Change_PMode)
		rmsg.ex.pmode = mode;
	return rmsg;
}
GB_Msg FormatMsg(GMType mtype)
{
	GB_Msg rmsg;
	rmsg.type = mtype;
	return rmsg;
}

//三大全局对象的实现
GTalker* GTalker::Instance = new GTalker;
GListener* GListener::Instance = new GListener;
GMessageQueue* GMessageQueue::Instance = new GMessageQueue;

void GTalker::backgroud()
{
	static int off = 0;
	off++;
	int offpos = off / 4;
	vector<string>WordsArr = getbackstring();
	//绘制动态背景

	moveto({ 0,0 });
	for (int i = 0; i < horizontal(); )
	{
		int temp = (i + offpos) % WordsArr.size();
		cout << WordsArr[temp];
		i += int(WordsArr[temp].size());
	}
	//cout << string(Width, '*');
	for (int i = 1; i < vertical(); ++i)
	{
		moveto({ 0,i });
		cout << WordsArr[(i + offpos) % WordsArr.size()];
		moveto({ horizontal() - 1,i });
		cout << WordsArr[(i + offpos) % WordsArr.size()];
	}
	moveto({ 0,vertical() - 1 });
	for (int i = 0; i < horizontal(); )
	{
		int temp = (i + offpos) % WordsArr.size();
		cout << WordsArr[temp];
		i += int(WordsArr[temp].size());
	}
	moveto({ 0,0 });
}

void GTalker::DealInfo(GO_Msg& info)
{
	map<GOType, vector<GO_Msg::Str_Info>>AfterDeal;

	for (auto node : info.AllStrings)
	{
		AfterDeal[node.type].push_back(node);
	}

	int Needs = int(AfterDeal[GOType::Center].size());
	int Up_Down = vertical() - between_point * (Needs - 1) + Needs;
	Up_Down /= 2;

	for (auto& node : AfterDeal)
	{
		for (int index = 0; index <int(node.second.size()); ++index)
		{
			switch (node.first)
			{
			case GOType::Center:
				node.second[index].pos =
				{ Up_Down + index + index * between_point,(horizontal() - int(node.second[index].StrView.size())) / 2 };
				break;
			case GOType::Explanation:
				node.second[index].pos =
				{ vertical() - Up_Down + index + 1,(horizontal() - int(node.second[index].StrView.size())) / 2 };
				break;
			case GOType::Left_top:
				break;
			case GOType::Left_bottom:
				break;
			case GOType::Right_top:
				break;
			case GOType::Right_bottom:
				break;
			case GOType::SelfDef:
				break;
			default:
				break;
			}
		}
	}
}
void GTalker::SmartRender(const GO_Msg& info)
{
	int Needs = int(info.AllStrings.size());
	int Up_Down = vertical() - between_point * (Needs - 1) + Needs;
	Up_Down /= 2;
	for (int i = 0; i < Needs; ++i)
	{
		moveto({ Up_Down + i + i * between_point,(horizontal() - int(info.AllStrings[i].StrView.size())) / 2 });
		cout << info.AllStrings[i].StrView;
	}
}
void GTalker::Render(GO_Msg info)
{
	backgroud();
	
	DealInfo(info);

	for (const auto& node : info.AllStrings)
	{
		moveto(node.pos);
		cout << node.StrView;
	}
}

bool GListener::Update(void)
{
	//更新输入数据
	updateWindowInfo();
	Info.onkey = 0;
	if (_kbhit())
	{
		Info.onkey = _getch();
		return true;
	}
	return false;
}

void GMessageQueue::AddMsg(GB_Msg info)
{
	if (MQueue.empty() || MQueue.front().type != info.type)
		MQueue.push(info);
}
GB_Msg GMessageQueue::PopMsg()
{
	if (MQueue.empty())
		return { GMType::NOP };
	GB_Msg temp = MQueue.front();
	MQueue.pop();
	return temp;
}

class autodelete {
public:
	~autodelete()
	{
		//自动析构3大全局变量
		if (GInput)
		{
			delete GInput;
			GListener::Instance = nullptr;
		}
		if (GOutput)
		{
			delete GOutput;
			GListener::Instance = nullptr;
		}
		if (GMsg)
		{
			delete GMsg;
			GListener::Instance = nullptr;
		}

	}
}const Killer = autodelete();