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
		mode &= ~ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, mode);
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
		{
			Info.intype = GIType::Mouse_Left;
			if (Info.mouse_hit_quick)
				Info.intype = GIType::Quick_Mouse;
		}
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
		//按下 -> 放起 ->按下
		//static SYSTEMTIME lastcancle;
		//static SYSTEMTIME nowhit;
		const int subtime = 200;
		Info.mouse_hit = false;
		//Info.mouse_hit_quick = false;

		INPUT_RECORD* mouseRec = nullptr;
		DWORD res = 0, mescount = 0;

		POINT curpos;
		GetCursorPos(&curpos);
		
		//更新真实坐标
		Info.mouse_pos = { (curpos.x - Info.basepoint.Vertical) / 8,(curpos.y - Info.basepoint.Horizontal) / 16 };

		//cout<< "\n  x:" << curpos.x << " y:" << curpos.y<<"         ";
		//cout << "\n  hx:" << Info.mouse_pos.Horizontal << " vy:" << Info.mouse_pos.Vertical << "         ";
		//GetNumberOfConsoleInputEvents(GetStdHandle(STD_INPUT_HANDLE), &mescount);
		//if (mescount)
		//{
		//	mouseRec = (INPUT_RECORD*)malloc(sizeof(INPUT_RECORD) * mescount);
		//	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), mouseRec, mescount, &res);
		//}
		//for(DWORD i=0;i< mescount;++i)
		//{
		//	cout << "\n   " << mouseRec[i].EventType;
		//	if (mouseRec[i].EventType == MOUSE_EVENT)
		//	{
		//		Info.mouse_pos.Horizontal = mouseRec[i].Event.MouseEvent.dwMousePosition.X;
		//		Info.mouse_pos.Vertical = mouseRec[i].Event.MouseEvent.dwMousePosition.Y;
		//		Info.left_mouse_down = (mouseRec[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED);
		//		Info.right_mouse_down = (mouseRec[i].Event.MouseEvent.dwButtonState == FROM_LEFT_2ND_BUTTON_PRESSED);
		//		//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		//		return true;
		//	}
		//	//FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		//}

		

		if (GetAsyncKeyState(VK_LBUTTON) && 0x8000)
		{
			//if (!Info.on_hit)
			//{
			//	GetLocalTime(&nowhit);
			//	int a = getmillis(nowhit), b = getmillis(lastcancle);
			//	//cout << "\n nowhit:" << a << "  lastcancle:" << b << "        ";
			//	if (getmillis(nowhit) - getmillis(lastcancle) < subtime)
			//	{
			//		Info.mouse_hit_quick = true;
			//		//system("pause");
			//	}
			//}
			Info.mouse_hit = true;
			//Info.on_hit = true;
			return true;
		}
		/*else
		{
			if(Info.on_hit)
				GetLocalTime(&lastcancle);

			Info.on_hit = false;
		}*/
		return false;
	}
	void updateWindowInfo()
	{
		Info.winhandle = WinHandle();

		//更新基坐标
		RECT rect;
		GetWindowRect(GetConsoleWindow(), &rect);
		Info.basepoint = { rect.left + 7, rect.top + 31 };
		
		//更新缓冲区大小
		CONSOLE_SCREEN_BUFFER_INFO Pif;
		GetConsoleScreenBufferInfo(Info.winhandle, &Pif);
		Pif.dwSize.X = Pif.srWindow.Right + 1;
		Pif.dwSize.Y = Pif.srWindow.Bottom + 1;

		if (Info.screensize.Horizontal != Pif.dwSize.X || Info.screensize.Vertical != Pif.dwSize.Y)
		{
			Info.screensize.Horizontal = Pif.dwSize.X;
			Info.screensize.Vertical = Pif.dwSize.Y;

			GMsg->AddMsg({ GMType::Clear });
		}
		SetConsoleScreenBufferSize(Info.winhandle, Pif.dwSize);

		//cout << "\n  x:" << rect.left << " y:" << rect.top << "         ";

		

		//CONSOLE_CURSOR_INFO CursorInfo;
		//GetConsoleCursorInfo(Info.winhandle, &CursorInfo);//获取控制台光标信息
		//CursorInfo.bVisible = false; //隐藏控制台光标
		//SetConsoleCursorInfo(Info.winhandle, &CursorInfo);//设置控制台光标状态

	}
};

#define GInput GListener::getInstance()
