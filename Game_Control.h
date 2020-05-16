#pragma once
#include "Game_View.h"
#include "Game_Map.h"

class GControl
{
private:
	GSetType Hard = GSetType::Choose_Easy;//游戏难度
	GSetType PMode = GSetType::Choose_Standard;//游戏类型
	GView* OnView = nullptr;
	GResType whichres = GResType::Menu_Main;
	map<GResType, GView*>GResources;

	const string savepath = R"(.\data\save.txt)";
private:
	void SaveProcess()
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
						return;

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
					
				}
			}
		}
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
		if (!OnView)
			return;
		system("cls");
		GOutput->Render(OnView->Stringify());
	}
	void GameMapInitialize()
	{
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
public:
	GControl(); 
	~GControl();
	void OnLoad()
	{
		while (true)
		{
			GameMapInitialize();

			//抓取到可能有效的输入才进行处理
			GInput->Update();
			if (GInput->Info.intype != GIType::None)
				DealInput();
			GB_Msg ToDeal = GMsg->PopMsg();//获取队首消息
			if (ToDeal.type == GMType::Exit_Process)
				break;//循环至游戏结束
			else
				DealMsg(ToDeal);//处理所有类型的消息

		}
	}
};