#pragma once
#include "Game_Global.h"
//����һ�������� 
//���Զ������н�, �Զ�����, �Զ���ʾ����
class GMap
{
	//����GMap�����л�
	const char AngleChar = '*';
	const char HorizonChar = '-';
	const char VerticalChar = '|';
	const char BlockChar = 'N';

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
	//int map_info1[9][9] = { 0 };
public:
	GMap(GStatus hard, GStatus mode = GStatus::Choose_Classic) :Pmode(mode)
	{
		//��ʼ����ͼ
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
		return !(point.Vertical < 0 || point.Horizontal < 0 || point.Vertical >= Size() || point.Horizontal >= Size());
	}
	char NumtoChar(int num)
	{
		return char(num ? (abs(num) + '0') : BlockChar);
	}
public:

	GO_Msg Stringify();//���л�
	std::shared_ptr<int*>a;
	int GetVal(GPoint pos)
	{
		if (!InArea(pos))
		{
			cout << "\nGMap����Խ��\n";
			return 0;
		}
		return map_info[pos.Vertical][pos.Horizontal];
	}

	bool SetNumber(GPoint pos, int num)//���ز����Ƿ�ɹ�
	{
		//��������
		if (!InArea(pos))
			return false;
		if (num >= 0 || num <= 9)//��֤Ϊ��Ч����
		{
			if (map_info[pos.Vertical][pos.Vertical] < 0)//�涨С��0��Ϊ���������
				return false;
			map_info[pos.Vertical][pos.Horizontal] = num;
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