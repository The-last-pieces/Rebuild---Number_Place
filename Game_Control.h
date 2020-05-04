#pragma once
#include "Game_View.h"
#include "Game_Map.h"

class GControl
{
private:
	GStatus Hard = GStatus::Choose_Easy;//��Ϸ�Ѷ�
	GStatus PMode = GStatus::Choose_Classic;//��Ϸ����
	GView* OnView = nullptr;
	GResType whichres = GResType::Menu_Main;
	map<GResType, GView*>GResources;

	const string savepath = R"(C:\Users\Administrator\Desktop\save.txt)";
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
					fstream fs;
					fs.open(savepath);

					if (!fs)
						return;

					fs << (int)mp->OnMap->hard << ' ' << (int)mp->OnMap->mode << ' ';
					for (int i = 0; i < 9; ++i)
					{
						for (int j = 0; j < 9; ++j)
						{
							fs << mp->OnMap->map_info[i][j] << ' ';
						}
					}

					fs.close();
				}
			}
		}
	}
	void LoadProcess()
	{
		if (GResources[GResType::Play_OnGame])
		{
			GPlay* mp = dynamic_cast<GPlay*>(GResources[GResType::Play_OnGame]);
			if (mp)
			{
				if (!mp->OnMap)
				{
					mp->OnMap = new GMap;
					mp->startgame = true;
					fstream fs(savepath);

					if (!fs)
						return;

					int temp=0;
					
					fs >> temp;
					mp->OnMap->hard = (GStatus)temp;
					fs >> temp;
					mp->OnMap->mode = (GStatus)temp;

					for (int i = 0; i < 9; ++i)
					{
						for (int j = 0; j < 9; ++j)
						{
							fs >> mp->OnMap->map_info[j][i];
						}
					}

					fs.close();
				}
			}
		}
	}
private:
	void DealMsg(GB_Msg ToDeal)
	{
		//������Ϣ
		switch (ToDeal.type)
		{
		case GMType::Clear:
			system("cls");
			break;
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
		//case GMType::SetNum:
		//	break;
		case GMType::GetHint:
			break;
		//case GMType::GetAnswer:
		//	break;
		case GMType::Save:
			SaveProcess();
			break;
		case GMType::Load:
			LoadProcess();
			break;
		//case GMType::Prompt:
		//	Prompt();
			break;
		case GMType::NOP:
		default:
			break;
		}
	}
	void DealInput()
	{
		//��������,����Ϣ������Ϣ������
		if (!OnView)
			return;
		OnView->Behavior();
	}
	void Prompt()
	{
		//������Ⱦ
		
	}
	void Render()
	{
		if (!OnView)
			return;
		GOutput->Render(OnView->Stringify());
	}
public:
	GControl(); 
	~GControl();
	void OnLoad()
	{
		while (true)
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

			//ץȡ��������Ч������Ž��д���
			GInput->Update();
			if (GInput->Info.intype!=GIType::None)
				DealInput();

			GOutput->backgroud();
			GB_Msg ToDeal = GMsg->PopMsg();//��ȡ������Ϣ
			if (ToDeal.type == GMType::Exit_Process)
				break;//ѭ������Ϸ����
			else
				DealMsg(ToDeal);//�����������͵���Ϣ

			Sleep(1000 / FPS);
		}
		
		//�ͷ���Դ
	}
};