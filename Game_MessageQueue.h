#pragma once
#include "Game_Global.h"
class GMessageQueue
{
	friend class autodelete;//�Զ�����
private:
	//Ψһʵ��������,������ȷ��
	static GMessageQueue* Instance;
private:
	//��ֹ������޸Ķ���
	GMessageQueue()
	{
		//��update�������߳���
	}
	~GMessageQueue()
	{
		//�ͷ��߳���Դ
	}
	GMessageQueue(const GMessageQueue&) = delete;
public:
	//��Ϣ����
	queue<GB_Msg> MQueue;

	//�������õ���־����
#ifdef debug

	template <typename T>
	static void DebugLog(T what)
	{
		fstream fs(R"(.\data\log.txt)", std::ios_base::app);
		if (fs)
		{
			fs << what << endl;
		}
		fs.close();
	}
	static void DebugLog(GB_Msg what)
	{
		const vector<string>sts = {
				"Exit_Process,//�˳�����",
				"Clear,//��ջ���",
				"Rend,//��ӻ���(������)",
				"Change_View,//�л�OnView",
				"Change_Hard,//�л�Hard",
				"Change_PMode,//�л�PMode",
				"GetAnswer,//��ȡ��",
				"Save,//�浵",
				"Load,//����",
				"Sleep,//����",
				"NOP//�ղ���"
		};
		DebugLog(sts[int(what.type)]);
	}
#endif // debug

public:
	static GMessageQueue* getInstance()
	{
		//����ÿ��GInputͬ��
		if (!Instance)
			Instance = new GMessageQueue;
		return Instance;
	}
	void AddMsg(GB_Msg info);
	GB_Msg PopMsg();
};

#define GMsg GMessageQueue::getInstance()

GB_Msg CreateMsg(double sleeptime);//Sleep��Ϣ
GB_Msg CreateMsg(GResType ptr);//Change_View��Ϣ
GB_Msg CreateMsg(ExInfo::NumInfo numinfo);//Set_Num��Ϣ
GB_Msg CreateMsg(GSetType mode, GMType mtype);//Change_Mode��Ϣ
GB_Msg CreateMsg(GMType mtype);//��ͨ��Ϣ