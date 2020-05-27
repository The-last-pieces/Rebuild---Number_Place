#include "Game_PInterface.h"

GB_Msg CreateMsg(double _sleeptime)
{
	//以秒位单位
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

void PlayMusic(const wstring& msc, bool ifrepeat, double start)
{
	static wstring now = L"";
	wstring cmd = L"open data\\";
	cmd += msc + L" alias msc";

	if (!msc.empty() && msc != now) {
		mciSendStringW(L"close msc", NULL, 0, NULL);//关闭之前的音乐

		mciSendStringW(cmd.c_str(), NULL, 0, NULL);//alias后为设备名称

		std::wstringstream ss;
		ss << L"play msc from " << int(start * 1000);
		ifrepeat && (ss << L" repeat", 0);
		mciSendStringW(ss.str().c_str(), NULL, 0, NULL);//播放新音乐
	}
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
			"Exit_Process,//退出进程",
			"Clear,//清空画面",
			"Rend,//添加画面(不覆盖)",
			"Change_View,//切换OnView",
			"Change_Hard,//切换Hard",
			"Change_PMode,//切换PMode",
			"GetAnswer,//获取答案",
			"Save,//存档",
			"Load,//读档",
			"Sleep,//休眠",
			"NOP//空操作"
	};
	DebugLog(sts[int(what.type)]);
}
#endif // debug
