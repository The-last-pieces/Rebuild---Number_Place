#pragma once
#include "Game_View.h"
#include "Game_Map.h"

class GControl
{
private:
	GStatus Hard = GStatus::Choose_Easy;//游戏难度
	GStatus PMode = GStatus::Choose_Classic;//游戏类型
	GView* OnView = nullptr;
private:
	void SaveProcess(){}
	void LoadProcess(){}
private:
	void DealMsg(GB_Msg ToDeal)
	{
		//处理消息
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
		//处理输入,将消息传入消息队列中
		if (!OnView)
			return;
		OnView->Behavior();
	}
	void Prompt()
	{
		//特殊渲染
		
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
			//抓取到可能有效的输入才进行处理
			if (GInput->Update())
				DealInput();

			GOutput->backgroud();
			GB_Msg ToDeal = GMsg->PopMsg();//获取队首消息
			if (ToDeal.type == GMType::Exit_Process)
				break;//循环至游戏结束
			else
				DealMsg(ToDeal);//处理所有类型的消息

			Sleep(1000 / FPS);
		}
		
		//释放资源
	}
};