#pragma once
#include "Game_Global.h"
class GMessageQueue
{
	friend class autodelete;//自动销毁
private:
	//唯一实例化对象,编译期确定
	static GMessageQueue* Instance;
private:
	//防止意外的修改对象
	GMessageQueue()
	{
		//将update加入子线程中
	}
	~GMessageQueue()
	{
		//释放线程资源
	}
	GMessageQueue(const GMessageQueue&) = delete;
public:
	//消息队列
	queue<GB_Msg> MQueue;

	//调试所用的日志函数
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
				"Exit_Process,//退出进程",
				"Clear,//清空画面",
				"Rend,//添加画面(不覆盖)",
				"Change_View,//切换OnView",
				"Change_Hard,//切换Hard",
				"Change_PMode,//切换PMode",
				"GetAnswer,//获取答案",
				"Save,//存档",
				"Load,//读档",
				"Sleep,//休眠",
				"NOP//空操作"
		};
		DebugLog(sts[int(what.type)]);
	}
#endif // debug

public:
	static GMessageQueue* getInstance()
	{
		//保持每个GInput同步
		if (!Instance)
			Instance = new GMessageQueue;
		return Instance;
	}
	void AddMsg(GB_Msg info);
	GB_Msg PopMsg();
};

#define GMsg GMessageQueue::getInstance()

GB_Msg CreateMsg(double sleeptime);//Sleep信息
GB_Msg CreateMsg(GResType ptr);//Change_View信息
GB_Msg CreateMsg(ExInfo::NumInfo numinfo);//Set_Num信息
GB_Msg CreateMsg(GSetType mode, GMType mtype);//Change_Mode信息
GB_Msg CreateMsg(GMType mtype);//普通信息