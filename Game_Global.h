#pragma once
#include <vector>
#include <string>
#include <array>
#include <map>
#include <queue>
#include <iostream>
#include <conio.h>
#include <Windows.h>

using std::vector;
using std::string;
using std::array;
using std::pair;
using std::map;
using std::queue;

using std::cout;
using std::cin;
using std::endl;



//游戏状态的枚举
enum class GStatus//储存游戏状态
{
	Exit_with_save,//退出程序并保存
	Exit_with_notsave,//直接退出程序

	//三个特殊状态
	Game_Playing,
	Game_Saving,
	Game_Loading,

	//一个数值选项
	Lable_HintCount,//初始提示数

	Choose_NewGame,//新游戏
	Choose_LoadGame,//读档

	Choose_Standard,//标准模式
	Choose_Classic,//经典模式
	Choose_Easy,//简单难度
	Choose_Normal,//一般难度
	Choose_Master,//困难难度

	//派生类类型
	ObjType_Play,//游戏进程相关
	ObjType_Menu,//转移目录
	ObjType_Choose,
	ObjType_Lable,//设置游戏参数
	ObjType_Base,

	//下为菜单项
	MainMenu,//主菜单
	OptionMenu,//难度选项菜单
	SelfdefMenu,//自定义难度界面
	PlayModeMenu,//选择游戏模式
	QuitMenu,//处理退出行为
	HelpMenu//游戏帮助
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
	Prompt,//提示信息,强制切换视图
	SetNum,//填数字
	GetHint,//获取提示
	GetAnswer,//获取答案
	Save,//存档
	Load,//读档
	NOP//空操作
};

//一些公用类的定义

//游戏坐标点
class GPoint
{
public:
	int Vertical;//从上至下距离
	int Horizontal;//从左至右距离
	GPoint(int _Vertical = 0, int _Horizontal = 0) :
		Vertical(_Vertical), Horizontal(_Horizontal) {}
	GPoint Transform()
	{
		//真实坐标和本地坐标的转换

	}
};

const int FPS = 20;//刷新率

//类之间的通信
typedef union ExInfo
{
	struct
	{
		GPoint pos;
		int num = 0;
	}setnum;

	void* newshow;

	GStatus hard;
	GStatus pmode;

	ExInfo()
	{
		newshow = nullptr;
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
	GPoint mouse_pos = { 0,0 };
	GPoint screensize = { 30,90 };
	HANDLE winhandle = nullptr;
	bool left_mouse_down = false;
	bool right_mouse_down = false;
	int onkey = 0;
}GI_Msg;
//类与渲染器的通信
typedef struct Output_Info
{
	typedef struct Str_Info
	{
		string StrView;//图形
		GPoint pos;//位置
	}Str_Info;

	vector<Str_Info>AllStrings;
	bool autoplace = true;//自动对齐
}GO_Msg;



