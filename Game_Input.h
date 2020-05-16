#pragma once
#include "Game_MessageQueue.h"

//�����û�����,��װΪһ��ȫ��API
class GListener
{
	friend class autodelete;//�Զ�����
private:
	//Ψһʵ��������,������ȷ��
	static GListener* Instance;
private:
	//��ֹ������޸Ķ���
	GListener()
	{
		//��update�������߳���
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hStdin, &mode);
		mode &= ~ENABLE_QUICK_EDIT_MODE;  //�Ƴ����ٱ༭ģʽ
		mode &= ~ENABLE_INSERT_MODE;      //�Ƴ�����ģʽ
		mode &= ~ENABLE_MOUSE_INPUT;	  //���������������
		SetConsoleMode(hStdin, mode);

		SetWindowLongPtrA(
            GetConsoleWindow(),
            GWL_STYLE,
            GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)
            & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX
        );//�������ڴ�С
	}
	~GListener()
	{
		//�ͷ��߳���Դ
	}
	GListener(const GListener&) = delete;
public:
	//���ڴ��浱ǰ����������
	GI_Msg Info;
public:
	static GListener* getInstance()
	{
		//����ÿ��GInputͬ��
		if (!Instance)
			Instance = new GListener;

		return Instance;
	}
	//������������,��Ϊ�ɽ��ܵ������򷵻�true
	bool Update(void);
private:
	inline HANDLE WinHandle()
	{
		return GetStdHandle(STD_OUTPUT_HANDLE);
	}
	void updateType()
	{
		Info.intype = GIType::None;
		if (Info.onkey >= '0' && Info.onkey <= '9')
			Info.intype = GIType::Number;
		if (Info.mouse_hit)
			Info.intype = GIType::Mouse_Left;
		if (Info.onkey == VK_RETURN)
			Info.intype = GIType::Confirm;
		if (Info.onkey == 'q' || Info.onkey == 'Q' || Info.onkey == VK_ESCAPE)
			Info.intype = GIType::Back;
		if (Info.onkey == 'w' || Info.onkey == 'W' || Info.onkey == VK_UP)
			Info.intype = GIType::Up_Page;
		if (Info.onkey == 's' || Info.onkey == 'S' || Info.onkey == VK_DOWN)
			Info.intype = GIType::Down_Page;
		if (Info.onkey == 'a' || Info.onkey == 'A' || Info.onkey == VK_LEFT)
			Info.intype = GIType::Left_Lable;
		if (Info.onkey == 'd' || Info.onkey == 'D' || Info.onkey == VK_RIGHT)
			Info.intype = GIType::Right_Lable;
		if (Info.onkey == VK_SPACE)
			Info.intype = GIType::Regret;

	}
	bool updateKeyBoardInfo()
	{
		Info.onkey = 0;
		if (_kbhit())
		{
			Info.onkey = _getch();
			return true;
		}
		return false;
	}
	bool updateMouseInfo()
	{
		//��¼�ϴΰ�ѹ�Ƿ����
		static bool hasend = true;

		POINT curpos;
		GetCursorPos(&curpos);

		//������ʵ����
		Info.mouse_pos = { (curpos.x - Info.basepoint.Vertical) / 8,(curpos.y - Info.basepoint.Horizontal) / 16 };

		//���ڰ�ѹ״̬
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			//�ϴΰ�ѹ�Ѿ�����
			if (hasend)
			{
				hasend = false;//��ֹ�ظ��İ�ѹ��Ϣ
				Info.mouse_hit = true;
				return true;
			}
		}
		else
		{
			hasend = true;
		}
		Info.mouse_hit = false;
		return false;
	}
	void updateWindowInfo()
	{
		Info.winhandle = WinHandle();

		//���»�����

		/* --------
			�ɰ��㷨,�����Բ�
			RECT rect;
			GetWindowRect(GetConsoleWindow(), &rect);
			Info.basepoint = { rect.left + 7, rect.top + 31 };//�ֶ�����
		*/
		POINT rect = { 0,0 };
		ClientToScreen(GetConsoleWindow(), &rect);
		Info.basepoint = { rect.x,rect.y };
	}
};

#define GInput GListener::getInstance()
