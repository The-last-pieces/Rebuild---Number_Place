#pragma once
#include <vector>
#include <string>
#include <array>
#include <map>
#include <queue>
#include <iostream>
#include <fstream>
#include <time.h>
#include <conio.h>
#include <Windows.h>

using std::vector;
using std::string;
using std::array;
using std::pair;
using std::map;
using std::queue;

using std::swap;

using std::cout;
using std::cin;
using std::fstream;

using std::endl;



//��Ϸ״̬��ö��
enum class GStatus//������Ϸ״̬
{
	Exit_with_save,//�˳����򲢱���
	Exit_with_notsave,//ֱ���˳�����

	//��������״̬
	Game_Playing,
	Game_Saving,
	Game_Loading,

	//һ����ֵѡ��
	Lable_HintCount,//��ʼ��ʾ��

	Choose_NewGame,//����Ϸ
	Choose_LoadGame,//����

	Choose_Standard,//��׼ģʽ
	Choose_Classic,//����ģʽ

	Choose_Master = 25,//���Ѷ�
	Choose_Normal = 30,//һ���Ѷ�
	Choose_Easy = 35,//�����Ѷ�

	//����������
	ObjType_Play,//��Ϸ�������
	ObjType_Menu,//ת��Ŀ¼
	ObjType_Choose,
	ObjType_Lable,//������Ϸ����
	ObjType_Base,

	//��Ϊ�˵���
	MainMenu,//���˵�
	OptionMenu,//�Ѷ�ѡ��˵�
	SelfdefMenu,//�Զ����ѶȽ���
	PlayModeMenu,//ѡ����Ϸģʽ
	QuitMenu,//�����˳���Ϊ
	HelpMenu//��Ϸ����
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
	Prompt,//��ʾ��Ϣ,ǿ���л���ͼ
	SetNum,//������
	GetHint,//��ȡ��ʾ
	GetAnswer,//��ȡ��
	Save,//�浵
	Load,//����
	NOP//�ղ���
};
//�����ʽö��
enum class GOType
{
	Center,
	NoBetween_Center,
	Explanation,
	Left_top,
	Left_bottom,
	Right_top,
	Right_bottom,
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
	Quick_Mouse,
	Mouse_Left
};
//��ͼ��Դö��
enum class GResType
{
	Play_OnGame,//��Ϸ��ͼ
	Play_WinGame,//ʤ������

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
	int Vertical;//�������¾���
	int Horizontal;//�������Ҿ���
	GPoint(int _Vertical = 0, int _Horizontal = 0) :
		Vertical(_Vertical), Horizontal(_Horizontal) {}
	GPoint Transform()
	{
		//��ʵ����ͱ��������ת��

	}
};

const int FPS = 20;//ˢ����

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
	//void* newshow;

	GStatus hard;
	GStatus pmode;

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
	bool on_hit = false;
	bool mouse_hit_quick = false;
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

	}Str_Info;

	vector<Str_Info>AllStrings;
}GO_Msg;

int getmillis(SYSTEMTIME tstp);



