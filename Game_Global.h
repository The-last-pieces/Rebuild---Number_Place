#pragma once
//#define debug

#include <vector>
#include <string>
#include <array>
#include <map>
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <mutex>
#include <time.h>
#include <conio.h>
#include <io.h>
#include <direct.h>
#include <Windows.h>

using std::vector;
using std::string;
using std::wstring;
using std::stack;
using std::array;
using std::pair;
using std::map;
using std::queue;
using std::thread;
using std::mutex;
using std::fstream;
using std::stringstream;

using std::swap;
using std::max;
using std::endl;

using std::cout;
using std::cin;

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow();

#pragma comment (lib, "winmm.lib") 

//��Ϸ���õ�ö��

enum class GSetType//������Ϸ����
{
	Choose_Standard,//��׼ģʽ
	//Choose_Classic,//����ģʽ ##������
	Choose_Master = 25,//���Ѷ�
	Choose_Normal = 30,//һ���Ѷ�
	Choose_Easy = 35,//�����Ѷ�
};
//��Ϣ����ö��
enum class GMType
{
	Exit_Process,//�˳�����
	Clear,//��ջ���
	Rend,//��ӻ���(����)
	Change_View,//�л�OnView
	Change_Hard,//�л�Hard
	Change_PMode,//�л�PMode
	Save,//�浵
	Load,//����
	Sleep,//����
	MapInit,//��ʼ������
	NOP//�ղ���
};
//�����ʽö��
enum class GOType
{
	Center,		//�������Ŀ¼
	Explanation,//Ŀ¼ѡ��Ľ���
	SelfDef,	//�Զ���λ��
	GameTable,	//�����Ϸ����
	GameHint	//���ѡ�������
};
//������Ϊö��
enum class GIType
{
	None,		//��
	Number,		//����0~9
	Confirm,	//�س�
	Back,		//ESC����Q
	Up_Page,	//W 
	Down_Page,	//S
	Left_Lable,	//A
	Right_Lable,//D
	Mouse_Left,	//������
	Regret		//�ո�
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

	Text_Welcome,//��ӭ��Ϣ
	Text_Help,//��Ϸ����
	Text_Win//ʤ����ʾ��Ϣ
};

//һЩ������Ķ���

//��Ϸ�����
typedef struct GPoint
{
	int Vertical = 0;//�������¾���
	int Horizontal = 0;//�������Ҿ���
}GPoint;

const int FPS = 20;//ˢ����

//��֮���ͨ��
typedef struct Behavior_Info
{
	union ExInfo
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
			sleeptime = 0;
		}
	}ex;//������Ϣ
	GMType type = GMType::NOP;
}GB_Msg;
//�����û����ͨ��
typedef struct Input_Info
{
	GIType intype = GIType::None;	//��������
	GPoint mouse_pos = { 0,0 };		//���λ��
	GPoint screensize = { 30,90 };	//��Ļ�ߴ�
	GPoint basepoint = { 0,0 };		//���ڼ���������Ļ�����
	HANDLE winhandle = nullptr;		//��׼������
	bool mouse_hit = false;			//�Ƿ�ѹ������
	int onkey = 0;					//��ǰ��ѹ�ļ�
}GI_Msg;
//������Ⱦ����ͨ��
typedef struct Output_Info
{
	typedef struct Str_Info
	{
		string StrView;					//��������
		GPoint pos;						//λ��
		GOType type = GOType::Center;	//�����ʽ
		int offlen = 0;					//ƫ����
	}Str_Info;//��������

	vector<Str_Info>AllStrings;//����������������
}GO_Msg;