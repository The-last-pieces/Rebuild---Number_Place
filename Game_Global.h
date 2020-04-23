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

//����GMap�����л�
const char AngleChar = '*';
const char HorizonChar = '-';
const char VerticalChar = '|';
const char BlockChar = 'N';

//��֤�������
static const int up_down = 3;//���¼��
static const int left_right = 30;//���Ҽ��
static const int between_point = 4;//�α���



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
	Exit_Process,
	NOP
};


//һЩ������Ķ���

//��Ϸ�����
class GPoint
{
	static int length;
	static int width;
public:
	int x = 0;
	int y = 0;

	GPoint Transform()
	{
		//��ʵ����ͱ��������ת��
	}
};
//��֮���ͨ��
typedef struct
{
	GMType type;
}G_MsgInfo;
//�����û����ͨ��
typedef struct Input_Info
{
	GPoint mouse_pos;
	bool left_mouse_down = false;
	bool right_mouse_down = false;
	int onkey = 0;
}G_InputInfo;



