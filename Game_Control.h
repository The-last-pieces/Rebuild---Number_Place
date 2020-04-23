#pragma once
#include "Game_View.h"
#include "Game_Map.h"

class GControl
{
	void DealMsg(G_MsgInfo ToDeal)
	{
		//������Ϣ
	}
	bool DealInput()
	{
		//��������
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
			//ѭ������Ϸ����
			G_MsgInfo ToDeal = GMsg->PopMsg();
			if (ToDeal.type == GMType::Exit_Process)
				break;
			else
				DealMsg(ToDeal);
			if (GInput->Update() && DealInput())
			{
				//״̬���º�ŵ���Paint,����ˢ���ʹ��������˸
				Render();
			}
			break;
		}
		
		//�ͷ���Դ
	}
};