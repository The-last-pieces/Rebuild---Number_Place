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
	Choose_Easy,//���Ѷ�
	Choose_Normal,//һ���Ѷ�
	Choose_Master,//�����Ѷ�

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
	Explanation,
	Left_top,
	Left_bottom,
	Right_top,
	Right_bottom,
	SelfDef
};
//��ͼ��Դö��
enum class GResType
{
	StartGame,//��ʼ��ϷChoose
	ContinueGame,//������ϷChoose
	ModeSetting,//��Ϸ����Choose
	GameHelp,//��Ϸ����Choose
	QuitGame,//�˳���ϷChoose

	SetHard,//��Ϸ�Ѷ�Lable
	SetMode,//��ϷģʽLable

	MainMenu,//���˵�
	SettingMenu,//��Ϸ���ò˵�
	QuitMenu,//�����˳���Ϊ
	HelpMenu//��Ϸ����
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

	void* newshow;

	GStatus hard;
	GStatus pmode;

	ExInfo()
	{
		newshow = nullptr;
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
	GPoint mouse_pos = { 0,0 };
	GPoint screensize = { 30,90 };
	HANDLE winhandle = nullptr;
	bool left_mouse_down = false;
	bool right_mouse_down = false;
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



