#pragma once
#include "Game_MessageQueue.h"

//处理用户输入,封装为一个全局API
class GListener
{
	friend class autodelete;//自动销毁
private:
	//唯一实例化对象,编译期确定
	static GListener* Instance;
private:
	//防止意外的修改对象
	GListener()
	{
		//将update加入子线程中
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(hStdin, &mode);
		mode &= ~ENABLE_QUICK_EDIT_MODE;  //移除快速编辑模式
		mode &= ~ENABLE_INSERT_MODE;      //移除插入模式
		mode &= ~ENABLE_MOUSE_INPUT;	  //过滤其他鼠标输入
		SetConsoleMode(hStdin, mode);

		SetWindowLongPtrA(
            GetConsoleWindow(),
            GWL_STYLE,
            GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)
            & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX
        );//锁定窗口大小
	}
	~GListener()
	{
		//释放线程资源
	}
	GListener(const GListener&) = delete;
public:
	//用于储存当前的输入数据
	GI_Msg Info;
public:
	static GListener* getInstance()
	{
		//保持每个GInput同步
		if (!Instance)
			Instance = new GListener;

		return Instance;
	}
	//更新输入数据,若为可接受的输入则返回true
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
		//记录上次按压是否结束
		static bool hasend = true;

		POINT curpos;
		GetCursorPos(&curpos);

		//更新真实坐标
		Info.mouse_pos = { (curpos.x - Info.basepoint.Vertical) / 8,(curpos.y - Info.basepoint.Horizontal) / 16 };

		//处于按压状态
		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			//上次按压已经结束
			if (hasend)
			{
				hasend = false;//防止重复的按压信息
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

		//更新基坐标

		/* --------
			旧版算法,兼容性差
			RECT rect;
			GetWindowRect(GetConsoleWindow(), &rect);
			Info.basepoint = { rect.left + 7, rect.top + 31 };//手动测量
		*/
		POINT rect = { 0,0 };
		ClientToScreen(GetConsoleWindow(), &rect);
		Info.basepoint = { rect.x,rect.y };
	}
};

#define GInput GListener::getInstance()
