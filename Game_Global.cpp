#include "Game_Input.h"
#include "Game_Output.h"
//#include "Game_MessageQueue.h"

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

	if (info.autoplace)
	{
		SmartRender(info);
		return;
	}
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