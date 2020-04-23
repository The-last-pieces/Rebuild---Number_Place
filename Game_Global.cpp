#include "Game_Input.h"
#include "Game_Output.h"
#include "Game_MessageQueue.h"

//����ȫ�ֶ����ʵ��

GTalker* GTalker::Instance = new GTalker;
GListener* GListener::Instance = new GListener;
GMessageQueue* GMessageQueue::Instance = new GMessageQueue;

void GTalker::Render(vector<string> info)
{

}

bool GListener::Update(void)
{
	//������������
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

class autodelete {
public:
	~autodelete()
	{
		//�Զ�����3��ȫ�ֱ���
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