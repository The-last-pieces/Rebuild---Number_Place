#include "Game_Input.h"
#include "Game_Output.h"
#include "Game_MessageQueue.h"

//三大全局对象的实现

GTalker* GTalker::Instance = new GTalker;
GListener* GListener::Instance = new GListener;
GMessageQueue* GMessageQueue::Instance = new GMessageQueue;

void GTalker::Render(vector<string> info)
{

}

bool GListener::Update(void)
{
	//更新输入数据
	Info.onkey = 0;
	if (_kbhit())
	{
		Info.onkey = _getch();
		return true;
	}
	return false;
}

void GMessageQueue::AddMsg(G_MsgInfo info)
{

}
G_MsgInfo GMessageQueue::PopMsg()
{
	return { GMType::NOP };
}