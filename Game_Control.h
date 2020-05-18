#pragma once
#include "Game_View.h"
//管理视图的类
class GControl
{
public:
	GControl();
	~GControl();
	void OnLoad()//对外公开的启动接口
	{
		while (true)
		{
			//抓取到可能有效的输入才进行处理
			if (GInput->Update() && GInput->Info.intype != GIType::None)
				DealInput();
			GB_Msg ToDeal = GMsg->PopMsg();//获取队首消息
			if (ToDeal.type == GMType::Exit_Process)//循环至游戏结束
				break;
			else
				DealMsg(ToDeal);//处理所有类型的消息
		}
	}
private:
	GSetType Hard = GSetType::Choose_Easy;//游戏难度
	GSetType PMode = GSetType::Choose_Standard;//游戏类型
	GView* OnView = nullptr;
	GResType whichres = GResType::Menu_Main;
	map<GResType, GView*>GResources;

	const string savepath = R"(.\data\save.txt)";
private:
	bool SaveProcess()
	{
		if (GResources[GResType::Play_OnGame])
		{
			GPlay* mp = dynamic_cast<GPlay*>(GResources[GResType::Play_OnGame]);
			if (mp)
			{
				if (mp->OnMap)
				{
					std::ofstream fs(savepath);

					if (!fs)
						return false;

					fs << (int)mp->OnMap->hard << ' ' << (int)mp->OnMap->mode << '\n';
					for (int i = 0; i < 9; ++i)
					{
						for (int j = 0; j < 9; ++j)
						{
							fs << mp->OnMap->map_info[i][j] << ' ';
						}
						fs << endl;
					}

					fs.close();
					return true;
				}
			}
		}
		return false;
	}
	bool LoadProcess()
	{
		if (GResources[GResType::Play_OnGame])
		{
			GPlay* mp = dynamic_cast<GPlay*>(GResources[GResType::Play_OnGame]);
			if (mp)
			{
				if (!mp->OnMap)
				{
					fstream fs(savepath);
					if (!fs)
						return false;

					mp->OnMap = new GMap;
					mp->startgame = true;
					int temp=0;
					
					fs >> temp;
					mp->OnMap->hard = (GSetType)temp;
					fs >> temp;
					mp->OnMap->mode = (GSetType)temp;

					for (int i = 0; i < 9; ++i)
					{
						for (int j = 0; j < 9; ++j)
						{
							fs >> mp->OnMap->map_info[i][j];
						}
					}

					fs.close();
					return true;
				}
			}
		}
		return false;
	}
private:
	void DealMsg(GB_Msg ToDeal)
	{
		//处理消息
		switch (ToDeal.type)
		{
		case GMType::Rend:
			Render();
			break;
		case GMType::Change_View:
			whichres = ToDeal.ex.newshow;
			if (whichres == GResType::Play_OnGame)
				GMsg->AddMsg(CreateMsg(GMType::MapInit));
			if (GResources[whichres])
			{
				if (OnView)
					OnView->OnMe = false;
				OnView = GResources[whichres];
				if (OnView)
					OnView->OnMe = true;
			}
			break;
		case GMType::Change_Hard:
			Hard = ToDeal.ex.hard;
			break;
		case GMType::Change_PMode:
			PMode = ToDeal.ex.pmode;
			break;
		case GMType::Save:
			SaveProcess();
			break;
		case GMType::Load:
			if (LoadProcess())
			{
				GMsg->AddMsg(CreateMsg(GResType::Play_OnGame));
				GMsg->AddMsg(CreateMsg(GMType::Rend));
			}
			break;
		case GMType::MapInit:
			GameMapInitialize();
			break;
		case GMType::Sleep:
			Sleep(ToDeal.ex.sleeptime);
		case GMType::NOP:
		default:
			break;
		}
	}
	void DealInput()
	{
		//处理输入,将消息传入消息队列中
		if (!OnView)
			return;
		OnView->Behavior();
	}
	void Render()
	{
		//提交绘图请求
		if (!OnView)
			return;
		system("cls");
		GOutput->Render(OnView->Stringify());
	}
	void GameMapInitialize()
	{
		//数据初始化
		if (whichres == GResType::Play_OnGame)
		{
			GPlay* temp = dynamic_cast<GPlay*>(OnView);
			if (temp)
			{
				if (!temp->startgame)
				{
					temp->CreateMap(Hard, PMode);
					temp->startgame = true;
				}
			}
		}
	}
};