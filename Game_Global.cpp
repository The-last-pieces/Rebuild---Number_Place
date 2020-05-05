#include "Game_Input.h"
#include "Game_Output.h"

GB_Msg CreateMsg(double _sleeptime)
{
	//以秒位单位
	GB_Msg rmsg;
	rmsg.type = GMType::Sleep;
	rmsg.ex.sleeptime = max(0, DWORD(_sleeptime * 1000));
	return rmsg;
}
GB_Msg CreateMsg(GResType ptr)
{
	GB_Msg rmsg;
	rmsg.type = GMType::Change_View;
	rmsg.ex.newshow = ptr;
	return rmsg;
}
GB_Msg CreateMsg(ExInfo::NumInfo numinfo)
{
	GB_Msg rmsg;
	rmsg.type = GMType::Change_View;
	rmsg.ex.setnum = numinfo;
	return rmsg;
}
GB_Msg CreateMsg(GSetType mode,GMType mtype)
{
	GB_Msg rmsg;
	rmsg.type = mtype;
	if (mtype == GMType::Change_Hard)
		rmsg.ex.hard = mode;
	if (mtype == GMType::Change_PMode)
		rmsg.ex.pmode = mode;
	return rmsg;
}
GB_Msg CreateMsg(GMType mtype)
{
	GB_Msg rmsg;
	rmsg.type = mtype;
	return rmsg;
}

int getmillis(SYSTEMTIME tstp)
{
	int rtime = tstp.wMilliseconds;
	rtime += 60 * tstp.wSecond;
	rtime += 60 * 60 * tstp.wHour;
	rtime += 24 * 60 * 60 * tstp.wDay;
	return rtime;
}

//三大全局对象的实例化
GTalker* GTalker::Instance = new GTalker;
GListener* GListener::Instance = new GListener;
GMessageQueue* GMessageQueue::Instance = new GMessageQueue;

void GTalker::backgroud()
{
	const string backstring = "@%&";
	//绘制动态背景

	int offpos = 0;

	while (true)
	{
		++offpos;
		Sleep(FPS * 4);

		moveto({ 0,0 });
		for (int i = 0; i < horizontal(); )
		{
			int temp = (i + offpos) % backstring.size();
			cout << backstring[temp];

			i += 1;
		}
		for (int i = 1; i < vertical(); ++i)
		{
			moveto({ 0,i });
			cout << backstring[(i + offpos) % backstring.size()];
			moveto({ horizontal() - 1,i });
			cout << backstring[(i + offpos) % backstring.size()];
		}
		moveto({ 0,vertical() - 1 });
		for (int i = 0; i < horizontal(); )
		{
			int temp = (i + offpos) % backstring.size();
			cout << backstring[temp];
			i += 1;
		}
		moveto({ 0,0 });
	}

}

void GTalker::DealInfo(GO_Msg& info)
{
	map<GOType, vector<GO_Msg::Str_Info>>AfterDeal;

	for (auto node : info.AllStrings)
	{
		AfterDeal[node.type].push_back(node);
	}

	int Needs = int(AfterDeal[GOType::Center].size());
	int Up_Down = vertical() - between_point * (Needs - 1) - Needs;
	Up_Down /= 2;

	info.AllStrings.clear();
	for (auto& node : AfterDeal)
	{
		for (int index = 0; index <int(node.second.size()); ++index)
		{
			switch (node.first)
			{
			case GOType::Center:
				node.second[index].pos =
				{(horizontal() - int(node.second[index].StrView.size())) / 2, Up_Down + index + index * between_point };
				break;
			case GOType::Explanation:
				node.second[index].pos =
				{ (horizontal() - int(node.second[index].StrView.size())) / 2 , vertical() - Up_Down + index + 1 };
				break;
			case GOType::SelfDef:
				break;
			case GOType::GameTable:
				node.second[index].pos =
				{ (horizontal() - int(node.second[index].StrView.size())) / 2, (vertical() - int(node.second.size())) / 2 + index };
				break;
			case GOType::NoBetween_Center:
				break;
			case GOType::GameHint:
				node.second[index].pos =
				{ (horizontal() - int(node.second[index].StrView.size())) / 2 , (vertical() + 13) / 2 + 3 };
				break;
			default:
				break;
			}
			info.AllStrings.push_back(node.second[index]);
		}
	}
}

void GTalker::Render(GO_Msg info)
{
	//backgroud();

	//对坐标预处理
	DealInfo(info);

	for (const auto& node : info.AllStrings)
	{
		moveto(node.pos);
		cout << node.StrView;
	}
}

int GTalker::horizontal()
{
	return GInput->Info.screensize.Horizontal;
}

int GTalker::vertical()
{
	return GInput->Info.screensize.Vertical;
}


bool GListener::Update(void)
{
	//更新输入数据
	updateWindowInfo();
	bool temp = updateKeyBoardInfo() || updateMouseInfo();
	updateType();
	return temp;
}


void GMessageQueue::AddMsg(GB_Msg info)
{
	if (info.type == GMType::Rend)
		AddMsg(GB_Msg{ GMType::Clear });
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

//自动销毁
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