#include "Game_PInterface.h"

GB_Msg CreateMsg(double _sleeptime)
{
	//����λ��λ
	GB_Msg rmsg;
	rmsg.type = GMType::Sleep;
	rmsg.ex.sleeptime = max(DWORD(0), DWORD(_sleeptime * 1000));
	return rmsg;
}
GB_Msg CreateMsg(GResType ptr)
{
	GB_Msg rmsg;
	rmsg.type = GMType::Change_View;
	rmsg.ex.newshow = ptr;
	return rmsg;
}
GB_Msg CreateMsg(GSetType mode, GMType mtype)
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

int horizontal()
{
	return GInput->Info.screensize.Horizontal;
}

int vertical()
{
	return GInput->Info.screensize.Vertical;
}

void moveto(GPoint pos)
{
	COORD temp;
	temp.X = (SHORT)pos.Vertical;
	temp.Y = (SHORT)pos.Horizontal;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), temp);
}

#ifdef debug
template <typename T>
void DebugLog(T what)
{
	fstream fs(R"(.\data\log.txt)", std::ios_base::app);
	if (fs)
	{
		fs << what << endl;
	}
	fs.close();
}
template <>
void DebugLog<GB_Msg>(GB_Msg what)
{
	const vector<string>sts = {
			"Exit_Process,//�˳�����",
			"Clear,//��ջ���",
			"Rend,//���ӻ���(������)",
			"Change_View,//�л�OnView",
			"Change_Hard,//�л�Hard",
			"Change_PMode,//�л�PMode",
			"GetAnswer,//��ȡ��",
			"Save,//�浵",
			"Load,//����",
			"Sleep,//����",
			"NOP//�ղ���"
	};
	DebugLog(sts[int(what.type)]);
}
#endif // debug
