#pragma once
#include "Base_Lib.h"

//��Ϸ��ͼ

class GView
{
public:
	virtual GO_Msg Stringify() = 0;
	virtual bool Behavior() = 0;
};

//һ��ѡ��,ָ��һ��GView ָ�� 
//����������GMenu */GPlay *
class GChoose :public GView
{
private:
	string Column;
	string Explanation;
private:
	GView* Link = nullptr;
};

//��������û����õĲ���
class GLable :public GView
{
	int Select = 0;
	typedef struct {
		string Column;
		string Explanation;
		GStatus Mode;
	}GSet;
private:
	vector<GSet>AllSettings;
};

//ר������Ϸ��������
class GPlay :public GView
{
	
};

//��ϷĿ¼ 
//�������GChoose
class GMenu :public GView
{
private:
	vector<GChoose*>AllLinks;
public:
	const int length;
};