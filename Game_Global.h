#pragma once
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

//��Ϸ���õ�ö��
enum class GSetType//������Ϸ����
{
	Choose_Standard,//��׼ģʽ
	Choose_Classic,//����ģʽ

	Choose_Master = 25,//���Ѷ�
	Choose_Normal = 30,//һ���Ѷ�
	Choose_Easy = 35,//�����Ѷ�
};
//��Ϣ����ö��
enum class GMType
{
	Exit_Process,//�˳�����
	Clear,//��ջ���
	Rend,//��ӻ���(������)
	Change_View,//�л�OnView
	Change_Hard,//�л�Hard
	Change_PMode,//�л�PMode
	GetAnswer,//��ȡ��
	Save,//�浵
	Load,//����
	Sleep,//����
	NOP//�ղ���
};
//�����ʽö��
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
//������Ϊö��
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
//��ͼ��Դö��
enum class GResType
{
	Play_OnGame,//��Ϸ��ͼ

	Choose_StartGame,//��ʼ��ϷChoose
	Choose_ContinueGame,//������ϷChoose
	Choose_ModeSetting,//��Ϸ����Choose
	Choose_GameHelp,//��Ϸ����Choose
	Choose_QuitGame,//�˳���ϷChoose
	Choose_ExitWithSave,
	Choose_ExitWithinSave,

	Lable_SetHard,//��Ϸ�Ѷ�Lable
	Lable_SetMode,//��ϷģʽLable

	Menu_Main,//���˵�
	Menu_Setting,//��Ϸ���ò˵�
	Menu_Quit,//�����˳���Ϊ

	Text_Help,//��Ϸ����
	Text_Win//ʤ����ʾ��Ϣ
};

//һЩ������Ķ���

//��Ϸ�����
class GPoint
{
public:
	int Vertical = 0;//�������¾���
	int Horizontal = 0;//�������Ҿ���
};

const int FPS = 10;//ˢ����

//��֮���ͨ��
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
}ExInfo;//������Ϣ
typedef struct Behavior_Info
{
	GMType type = GMType::NOP;
	ExInfo ex;
}GB_Msg;
//�����û����ͨ��
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
//������Ⱦ����ͨ��
typedef struct Output_Info
{
	typedef struct Str_Info
	{
		string StrView;//ͼ��
		GPoint pos;//λ��
		GOType type = GOType::Center;//�����ʽ
		int offlen = 0;//ƫ����
	}Str_Info;

	vector<Str_Info>AllStrings;
}GO_Msg;





