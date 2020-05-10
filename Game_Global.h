#pragma once
//#define debug

#include <vector>
#include <string>
#include <array>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <time.h>
#include <conio.h>
#include <io.h>
#include <direct.h>
#include <Windows.h>

using std::vector;
using std::string;
using std::array;
using std::pair;
using std::map;
using std::queue;
using std::thread;
using std::fstream;

using std::swap;
using std::max;
using std::endl;

using std::cout;
using std::cin;

//游戏设置的枚举
enum class GSetType//储存游戏设置
{
	Choose_Standard,//标准模式
	Choose_Classic,//经典模式

	Choose_Master = 25,//简单难度
	Choose_Normal = 30,//一般难度
	Choose_Easy = 35,//困难难度
};
//信息类型枚举
enum class GMType
{
	Exit_Process,//退出进程
	Clear,//清空画面
	Rend,//添加画面(不覆盖)
	Change_View,//切换OnView
	Change_Hard,//切换Hard
	Change_PMode,//切换PMode
	GetAnswer,//获取答案
	Save,//存档
	Load,//读档
	Sleep,//休眠
	NOP//空操作
};
//输出格式枚举
enum class GOType
{
	Center,
	NoBetween_Center,
	Explanation,
	//Left_top,
	//Left_bottom,
	//Right_top,
	//Right_bottom,
	SelfDef,
	GameTable,
	GameHint
};
//输入行为枚举
enum class GIType
{
	None,
	Number,
	Confirm,
	Back,
	Up_Page,
	Down_Page,
	Left_Lable,
	Right_Lable,
	Mouse_Left
};
//视图资源枚举
enum class GResType
{
	Play_OnGame,//游戏视图

	Choose_StartGame,//开始游戏Choose
	Choose_ContinueGame,//继续游戏Choose
	Choose_ModeSetting,//游戏设置Choose
	Choose_GameHelp,//游戏帮助Choose
	Choose_QuitGame,//退出游戏Choose
	Choose_ExitWithSave,
	Choose_ExitWithinSave,

	Lable_SetHard,//游戏难度Lable
	Lable_SetMode,//游戏模式Lable

	Menu_Main,//主菜单
	Menu_Setting,//游戏设置菜单
	Menu_Quit,//处理退出行为

	Text_Help,//游戏帮助
	Text_Win//胜利提示信息
};

//一些公用类的定义

//游戏坐标点
class GPoint
{
public:
	int Vertical = 0;//从上至下距离
	int Horizontal = 0;//从左至右距离
};

const int FPS = 10;//刷新率

//类之间的通信
typedef union ExInfo
{
	typedef struct
	{
		GPoint pos;
		int num = 0;
	}NumInfo;

	NumInfo setnum;

	GResType newshow;
	GSetType hard;
	GSetType pmode;
	DWORD sleeptime;

	ExInfo()
	{
		newshow = GResType::Menu_Main;
	}
}ExInfo;//额外信息
typedef struct Behavior_Info
{
	GMType type = GMType::NOP;
	ExInfo ex;
}GB_Msg;
//类与用户层的通信
typedef struct Input_Info
{
	GIType intype=GIType::None;
	GPoint mouse_pos = { 0,0 };
	GPoint screensize = { 30,90 };
	GPoint basepoint = { 0,0 };
	HANDLE winhandle = nullptr;
	bool mouse_hit = false;
	int onkey = 0;
}GI_Msg;
//类与渲染器的通信
typedef struct Output_Info
{
	typedef struct Str_Info
	{
		string StrView;//图形
		GPoint pos;//位置
		GOType type = GOType::Center;//输出格式
		int offlen = 0;//偏移量
	}Str_Info;

	vector<Str_Info>AllStrings;
}GO_Msg;





