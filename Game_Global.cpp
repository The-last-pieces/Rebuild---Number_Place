#include "Game_Input.h"
#include "Game_Output.h"

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
GB_Msg CreateMsg(GStatus mode,GMType mtype)
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

void GTalker::transoutput()
{
	SMALL_RECT srctReadRect;
	SMALL_RECT srctWriteRect;
	CHAR_INFO* chiBuffer = new CHAR_INFO[(horizontal() + 1) * (vertical() + 1)];
	COORD coordBufSize = { horizontal() , vertical() };
	COORD coordBufCoord = { 0,0 };
	/*coordBufSize.Y = 25;
	coordBufSize.X = 80;*/
	//// The top left destination cell of the temporary buffer is 
	//// row 0, col 0. 
	coordBufCoord.X = 0;
	coordBufCoord.Y = 0;
	BOOL fSuccess;
	fSuccess = ReadConsoleOutput(
		hOut[1], // screen buffer to read from 
		chiBuffer, // buffer to copy into 
		coordBufSize, // col-row size of chiBuffer 
		coordBufCoord, // top left dest. cell in chiBuffer 
		&srctReadRect); // screen buffer source rectangle 

	srctWriteRect.Top = 0; // top lt: row 10, col 0 
	srctWriteRect.Left = 0;
	srctWriteRect.Bottom = GInput->Info.screensize.Vertical;
	srctWriteRect.Right = GInput->Info.screensize.Horizontal;

	fSuccess = WriteConsoleOutput(
		hOut[0], // screen buffer to write to 
		chiBuffer, // buffer to copy from 
		coordBufSize, // col-row size of chiBuffer 
		coordBufCoord, // top left src cell in chiBuffer 
		&srctWriteRect); // dest. screen buffer rectangle 
}

void GTalker::clearhout(HANDLE hd)
{
	SMALL_RECT srctReadRect;
	SMALL_RECT srctWriteRect;
	CHAR_INFO* chiBuffer = new CHAR_INFO[GInput->Info.screensize.Horizontal * GInput->Info.screensize.Vertical]{ 0 };
	COORD coordBufSize = { GInput->Info.screensize.Horizontal ,GInput->Info.screensize.Vertical };
	COORD coordBufCoord = { GInput->Info.screensize.Horizontal ,GInput->Info.screensize.Vertical };
	BOOL fSuccess;
	WriteConsoleOutput(
		hd, // screen buffer to write to 
		chiBuffer, // buffer to copy from 
		coordBufSize, // col-row size of chiBuffer 
		coordBufCoord, // top left src cell in chiBuffer 
		&srctWriteRect); // dest. screen buffer rectangle 
}

void GTalker::Render(GO_Msg info)
{
	//获取
	//在闲置hout中绘图

	//SetConsoleActiveScreenBuffer(hOut[1]);
	backgroud();

	DealInfo(info);

	for (const auto& node : info.AllStrings)
	{
		moveto(node.pos);
		cout << node.StrView;
	}

	//transoutput();

	//SetConsoleActiveScreenBuffer(hOut[0]);

	//clearhout(hOut[1]);
	
	//闲置hout设置为活动窗口
	//递增下标

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
	//if (info.type == GMType::Rend)
		//MQueue.push(GB_Msg{ GMType::Clear });
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