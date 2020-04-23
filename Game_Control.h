#pragma once
#include "Game_View.h"
#include "Game_Map.h"

class GControl
{
	void DealMsg(G_MsgInfo ToDeal)
	{
		//处理消息
	}
	bool DealInput()
	{
		//处理输入
		return false;
	}
	void Render()
	{
		GOutput->Render({});
	}
public:
	GControl()
	{

	}
	void OnLoad()
	{
		Render();
		while (true)
		{
			//循环至游戏结束
			G_MsgInfo ToDeal = GMsg->PopMsg();
			if (ToDeal.type == GMType::Exit_Process)
				break;
			else
				DealMsg(ToDeal);
			if (GInput->Update() && DealInput())
			{
				//状态更新后才调用Paint,避免刷新率过快产生闪烁
				Render();
			}
			break;
		}
		
		//释放资源
	}
};