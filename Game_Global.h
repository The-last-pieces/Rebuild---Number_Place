#pragma once
#include <vector>
#include <string>
#include <array>
#include <map>
#include <queue>
#include <iostream>
#include <conio.h>

using std::vector;
using std::string;
using std::array;
using std::pair;
using std::map;
using std::queue;

using std::cout;
using std::cin;

//用于GMap的序列化
const char AngleChar = '*';
const char HorizonChar = '-';
const char VerticalChar = '|';
const char BlockChar = 'N';

//保证居中输出
static const int up_down = 3;//上下间距
static const int left_right = 30;//左右间距
static const int between_point = 4;//游标间距



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
	Exit_Process,
	NOP
};


//一些公用类的定义

//游戏坐标点
class GPoint
{
	static int length;
	static int width;
public:
	int x = 0;
	int y = 0;

	GPoint Transform()
	{
		//真实坐标和本地坐标的转换
	}
};
//类之间的通信
typedef struct
{
	GMType type;
}G_MsgInfo;
//类与用户层的通信
typedef struct Input_Info
{
	GPoint mouse_pos;
	bool left_mouse_down = false;
	bool right_mouse_down = false;
	int onkey = 0;
}G_InputInfo;



