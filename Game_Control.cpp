#include "Game_Control.h"

GControl::GControl()
{
	//GView���ݳ�ʼ��

	//��ʼ��GChoose

	//GResources[GResType::OnPlay] = new GPlay();

	
	GResources[GResType::Play_OnGame] = new GPlay{

	};

	GResources[GResType::Choose_StartGame] = new GChoose{
		"��ʼ��Ϸ",
		"����ȡ�浵��ʼ�½���",
		{CreateMsg(GResType::Play_OnGame)}
	};
	GResources[GResType::Choose_ContinueGame] = new GChoose{
		"������Ϸ",
		"��ȡ�浵�еĽ���",
		{CreateMsg(GMType::Load),CreateMsg(GResType::Play_OnGame)}
	};
	GResources[GResType::Choose_ModeSetting] = new GChoose{
		"��Ϸ����",
		"������Ϸ�Ĳ���",
		{CreateMsg(GResType::Menu_Setting)}
	};

	GResources[GResType::Choose_GameHelp] = new GChoose{
		"��Ϸ����",
		"�鿴��Ϸ����",
		{CreateMsg(GResType::Menu_Help)}
	};
	GResources[GResType::Choose_QuitGame] = new GChoose{
		"�˳���Ϸ",
		"�˳�����Ϸ",
		{CreateMsg(GResType::Menu_Quit)}
	};

	GResources[GResType::Choose_ExitWithinSave] = new GChoose{
		"��������Ȳ��˳�",
		"�´ν�����Ϸʱ,ֻ���ȡ�ϴεĽ���",
		{CreateMsg(GMType::Exit_Process)}
	};
	GResources[GResType::Choose_ExitWithSave] = new GChoose{
		"������Ȳ��˳�",
		"�´ν�����Ϸʱ,���Զ�ȡ������Ϸ�Ľ���",
		{CreateMsg(GMType::Save),CreateMsg(GMType::Exit_Process)}
	};

	GResources[GResType::Lable_SetHard] = new GLable{
		{
			{ "��ģʽ","�ṩ40����ʾ",GStatus::Choose_Easy },
			{ "һ��ģʽ","�ṩ30����ʾ",GStatus::Choose_Normal },
			{ "��ʦģʽ","�ṩ20����ʾ",GStatus::Choose_Master }
		},GMType::Change_Hard
	};
	GResources[GResType::Lable_SetMode] = new GLable{
		{
			{"��׼ģʽ","��׼ģʽ:������ͳһ�ı�׼,ÿ��,ÿ��,ÿ���Ź��񶼲������ظ�����",GStatus::Choose_Standard },
			{"����ģʽ","����ģʽ:���������,ÿ��,ÿ��,ÿ��б��,ÿ���Ź��񶼲������ظ�����",GStatus::Choose_Classic},
		},GMType::Change_Hard
	};

	OnView = GResources[GResType::Menu_Main] = new GMenu{
		{
			GResources[GResType::Choose_StartGame],
			GResources[GResType::Choose_ContinueGame],
			GResources[GResType::Choose_ModeSetting],
			GResources[GResType::Choose_GameHelp] ,
			GResources[GResType::Choose_QuitGame]
		}
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
			GResources[GResType::Choose_ExitWithinSave] ,
			GResources[GResType::Choose_ExitWithSave]
		},
		GResType::Menu_Main
	};
	GResources[GResType::Choose_GameHelp] = new GMenu{
		{

		},
		GResType::Menu_Main
	};

	//GResources[GResType::]


	GMsg->AddMsg(CreateMsg(GMType::Rend));
}