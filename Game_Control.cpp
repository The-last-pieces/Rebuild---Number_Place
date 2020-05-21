#include "Game_Control.h"

GControl::GControl()
{
	if (_access(R"(.\data)", 0) == -1)
	{
		_mkdir(R"(.\data)");
	}

	//GView数据初始化
	
	GResources[GResType::Play_OnGame] = new GPlay{

	}; 
	
	GResources[GResType::Choose_StartGame] = new GChoose{
		"开始游戏",
		"不读取存档开始新进度",
		{CreateMsg(GResType::Play_OnGame)}
	};
	GResources[GResType::Choose_ContinueGame] = new GChoose{
		"继续游戏",
		"读取存档中的进度",
		{CreateMsg(GMType::Load)}
	};
	GResources[GResType::Choose_ModeSetting] = new GChoose{
		"游戏设置",
		"设置游戏的参数",
		{CreateMsg(GResType::Menu_Setting)}
	};

	GResources[GResType::Choose_GameHelp] = new GChoose{
		"游戏帮助",
		"查看游戏帮助",
		{CreateMsg(GResType::Text_Help)}
	};
	GResources[GResType::Choose_QuitGame] = new GChoose{
		"退出游戏",
		"退出本游戏",
		{CreateMsg(GResType::Menu_Quit)}
	};

	GResources[GResType::Choose_ExitWithinSave] = new GChoose{
		"不保存进度并退出",
		"下次进入游戏时,只会读取上次的进度",
		{CreateMsg(GMType::Exit_Process)}
	};
	GResources[GResType::Choose_ExitWithSave] = new GChoose{
		"保存进度并退出",
		"下次进入游戏时,可以读取本次游戏的进度",
		{CreateMsg(GMType::Save),CreateMsg(GMType::Exit_Process)}
	};

	GResources[GResType::Lable_SetHard] = new GLable{
		{
			{ "简单模式","提供35个提示",GSetType::Choose_Easy },
			{ "一般模式","提供30个提示",GSetType::Choose_Normal },
			{ "大师模式","提供25个提示",GSetType::Choose_Master }
		},GMType::Change_Hard
	};
	GResources[GResType::Lable_SetMode] = new GLable{
		{
			{"标准模式","标准模式:国际上统一的标准,每行,每列,每个九宫格都不能有重复数字",GSetType::Choose_Standard }
			//{"经典模式","经典模式:最常见的数独,每行,每列,每个斜边,每个九宫格都不能有重复数字",GSetType::Choose_Classic},
		},GMType::Change_PMode
	};

	GResources[GResType::Menu_Main] = new GMenu{
		{
			GResources[GResType::Choose_StartGame],
			GResources[GResType::Choose_ContinueGame],
			GResources[GResType::Choose_ModeSetting],
			GResources[GResType::Choose_GameHelp] ,
			GResources[GResType::Choose_QuitGame]
		}
	};

	GResources[GResType::Text_Welcome] = new GText{
		{
			{
				{
					{"欢迎游玩,请查看以下说明"},{"本程序以鼠标(详情见游戏帮助)/键盘进行交互"},{"W/S键操作目录选项,A/D键选择游戏设置"},
					{"ESC/Q键返回上级目录"},{"回车键进入选项目录/执行选项操作"},{"请按任意键继续"}
				}
			}
		},
		GResType::Menu_Main
	};
	GResources[GResType::Text_Help] = new GText{
		{
			{ 
				{
					{"游戏帮助:"},{"键盘按下0~9可选择数字"},{"鼠标点击处会被替换为当前选择的数字"},
					{"按空格可以撤销最近的一次操作"},{"按下回车可以进行自动求解"},{"正确求解后会自动退出程序"}
				} 
			}
		},
		GResType::Menu_Main
	};
	GResources[GResType::Text_Win] = new GText{
		{
			{ {{"你获得了游戏胜利,3秒钟后自动退出程序"}} }
		},
		GResType::Menu_Main
	};

	GResources[GResType::Menu_Setting] = new GMenu{
		{
			GResources[GResType::Lable_SetHard],
			GResources[GResType::Lable_SetMode],
		},
		GResType::Menu_Main
	};
	GResources[GResType::Menu_Quit] = new GMenu{
		{
			GResources[GResType::Choose_ExitWithSave],
			GResources[GResType::Choose_ExitWithinSave]
		},
		GResType::Menu_Main
	};
	GResources[GResType::Choose_GameHelp] = new GMenu{
		{
			GResources[GResType::Text_Help]
		},
		GResType::Menu_Main
	};

	OnView = GResources[GResType::Text_Welcome];
	
	Render();
	_getch();

	PlayMusic(L"menu.mp3");

	OnView= GResources[GResType::Menu_Main];
	Render();
}

GControl::~GControl()
{
	for (auto &node : GResources)
	{
		if (node.second)
		{
			delete node.second;
			node.second = nullptr;
		}
	}
}