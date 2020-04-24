#pragma once
#include "Game_View.h"
#include "Game_Map.h"

class GControl
{
private:
	GStatus Hard = GStatus::Choose_Easy;//��Ϸ�Ѷ�
	GStatus PMode = GStatus::Choose_Classic;//��Ϸ����
	GView* OnView = nullptr;
private:
	void SaveProcess(){}
	void LoadProcess(){}
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
			OnView = (GView*)ToDeal.ex.newshow;
			break;
		case GMType::Change_Hard:
			Hard = ToDeal.ex.hard;
			break;
		case GMType::Change_PMode:
			PMode = ToDeal.ex.pmode;
			break;
		case GMType::SetNum:
			break;
		case GMType::GetHint:
			break;
		case GMType::GetAnswer:
			break;
		case GMType::Save:
			SaveProcess();
			break;
		case GMType::Load:
			LoadProcess();
			break;
		case GMType::Prompt:
			Prompt();
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
		/*
		GO_Msg gm;
		gm.AllStrings.push_back({ "", { rand() % 80,rand() % 20} });
		GOutput->Render(gm);*/
		if (!OnView)
			return;
		GOutput->Render(OnView->Stringify());
	}
public:
	GControl()
	{

	}
	void OnLoad()
	{
		while (true)
		{
			//ץȡ��������Ч������Ž��д���
			if (GInput->Update())
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