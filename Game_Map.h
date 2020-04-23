#pragma once
#include "Game_Global.h"
//����һ�������� 
//���Զ������н�, �Զ�����, �Զ���ʾ����
class GMap
{
private:
	static const size_t Map_Size = 9;
	GStatus Pmode;
	int base = 0;
	array<array<bool, Map_Size>, Map_Size> blocks = { 0 };
	array<array<bool, Map_Size>, Map_Size> cols = { 0 };
	array<array<bool, Map_Size>, Map_Size> rows = { 0 };
	array<array<int, Map_Size>, Map_Size> map_info = {
		{
		0,0,0,1,0,0,0,0,0,
		0,4,0,0,7,0,0,2,3,
		6,0,0,4,0,2,0,0,1,
		0,3,0,0,0,0,0,0,7,
		0,0,8,0,0,4,0,3,0,
		0,6,0,0,1,0,4,0,0,
		0,0,0,0,6,3,9,1,0,
		7,0,0,5,0,0,0,0,2,
		0,8,0,0,2,0,0,4,0
		}
	};//��ͼԴ����,�̶�9��9
	int map_info1[9][9] = { 0 };
public:
	GMap(int hard, GStatus mode = GStatus::Choose_Classic) :Pmode(mode)
	{
		//��ʼ����ͼ
		hard;
		for (int x = 0; x < 9; ++x)
		{
			for (int y = 0; y < 9; ++y)
			{
				//std::cin >> map_info[x][y];
				if (map_info[x][y] != 0) {
					int k = x / 3 * 3 + y / 3;// ���־Ź���,������
					int val = map_info[x][y] - 1;
					rows[x][val] = true;
					cols[y][val] = true;
					blocks[k][val] = true;
				}

				if (map_info[x][y])
				{
					base++;
				}
			}
		}
	}
private:
	int Size()
	{
		return Map_Size;
	}
	bool InArea(GPoint point)
	{
		return !(point.x < 0 || point.y < 0 || point.x >= Size() || point.y >= Size());
	}
public:

	vector<string>Stringify();//���л�

	int GetVal(GPoint pos)
	{
		if (!InArea(pos))
		{
			cout << "\nGMap����Խ��\n";
			return 0;
		}
		return map_info[pos.x][pos.y];
	}

	bool SetNumber(GPoint pos, int num)//���ز����Ƿ�ɹ�
	{
		//��������
		if (!InArea(pos))
			return false;
		if (num >= 0 || num <= 9)//��֤Ϊ��Ч����
		{
			if (map_info[pos.x][pos.x] < 0)//�涨С��0��Ϊ���������
				return false;
			map_info[pos.x][pos.y] = num;
			return true;
		}
		return false;
	}
	bool IsWin()
	{
		//�ж��Ƿ����
	}
	GMap Answer()
	{

	}
public:
	bool DFS();
};