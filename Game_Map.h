#pragma once
#include "Game_Global.h"
//储存一个数独盘 
//有自动求所有解, 自动生成, 自动提示功能

#define Map_Size 9

class GMap
{
	//用于GMap的序列化
	const char AngleChar = '*';
	const char HorizonChar = '-';
	const char VerticalChar = '|';
	const char BlockChar = 'N';
public:
	//static const size_t Map_Size = 9;
	class GMapWorker
	{
	private:
		GStatus Gmode = GStatus::Choose_Classic;
		int anscounts = 0;

		array<array<bool, Map_Size>, Map_Size> blocks = { 0 };
		array<array<bool, Map_Size>, Map_Size> cols = { 0 };
		array<array<bool, Map_Size>, Map_Size> rows = { 0 };
		array<array<bool, 2 * Map_Size - 1>, 2 * Map_Size - 1> llines = { 0 };//左上右下
		array<array<bool, 2 * Map_Size - 1>, 2 * Map_Size - 1> rlines = { 0 };//右上左下

		array<array<int, Map_Size>, Map_Size> canans = { 0 };

	private:
		bool dealmap(array<array<int, Map_Size>, Map_Size>& minfo, int xs, int ys)
		{
			//cout << anscounts << endl;
			/*if (xs == Map_Size - 1 && ys == Map_Size - 1 && minfo[xs][ys])
			{
				++anscounts;
				return;
			}*/
			for (int x = 0; x < Map_Size; x++)
			{
				for (int y = 0; y < Map_Size; y++)
				{
					if (minfo[x][y] == 0)
					{
						int k = x / 3 * 3 + y / 3;
						for (int num = 0; num < 9; num++)
						{
							if (
								!cols[y][num] &&
								!rows[x][num] &&
								!blocks[k][num] &&
								(
									Gmode != GStatus::Choose_Classic ||
									(!rlines[x + y][num] && !llines[Map_Size - x + y][num])
									)
								)
							{
								// l对于的数字l+1没有在行列块中出现
								//rlines[x + y][num] =
									//llines[Map_Size - 1 - x + y][num] =
									rows[x][num] =
									cols[y][num] =
									blocks[k][num] = true;
								minfo[x][y] = 1 + num;// 下标加1

								if (dealmap(minfo, x, y))
								{
									anscounts++;
								}
								//rlines[x + y][num] =
									//llines[Map_Size - 1 - x + y][num] =
									rows[x][num] =
									cols[y][num] =
									blocks[k][num] = false;// 递进失败则回溯
								minfo[x][y] = 0;
							}
						}
						return false;// a[i][j]==0时，l发现都不能填进去
					}// the end of a[i][j]==0
				}
			}
			canans = minfo;
			return true;// 没有a[i][j]==0,则返回true
		}
		void predeal()
		{
			blocks.fill(array<bool, Map_Size >{0});
			cols.fill(array<bool, Map_Size >{0});
			rows.fill(array<bool, Map_Size >{0});
			llines.fill(array<bool, 2 * Map_Size - 1 >{0});
			rlines.fill(array<bool, 2 * Map_Size - 1 >{0});
		}
	public:
		GMapWorker(GStatus _mode):Gmode(_mode)
		{

		}
		bool canbe(const array<array<int, Map_Size>, Map_Size>& minfo)
		{
			predeal();

			for (int x = 0; x < 9; ++x)
			{
				for (int y = 0; y < 9; ++y)
				{
					if (minfo[x][y] != 0) {
						int k = x / 3 * 3 + y / 3;// 划分九宫格,行优先
						int val = abs(minfo[x][y]) - 1;

						if (rows[x][val])
							return false;
						rows[x][val] = true;

						if (cols[y][val])
							return false;
						cols[y][val] = true;

						if (blocks[k][val])
							return false;
						blocks[k][val] = true;

						if (Gmode == GStatus::Choose_Classic)
						{
							k = x + y;

							if (llines[k][val])
								return false;
							llines[k][val] = true;

							k = 8 - x + y;

							if (rlines[k][val])
								return false;
							rlines[k][val] = true;
						}
					}
				}
			}
			return true;
		}
		bool getanswer(array<array<int, Map_Size>, Map_Size>& minfo)
		{
			predeal();
			array<array<int, Map_Size>, Map_Size> temp = minfo;
			anscounts = 0;

			for (int x = 0; x < 9; ++x)
			{
				for (int y = 0; y < 9; ++y)
				{
					if (minfo[x][y] != 0) {
						int k = x / 3 * 3 + y / 3;// 划分九宫格,行优先
						int val = abs(minfo[x][y]) - 1;
						rows[x][val] = true;
						cols[y][val] = true;
						blocks[k][val] = true;
					}
				}
			}

			dealmap(temp, 0, 0);
			if (anscounts == 1)
			{
				minfo = temp;
				return true;
			}
			else
			{
				minfo = canans;
				minfo[0][0] = anscounts;
				return false;
			}

		}
	} worker;
private:
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
	};
	
	/*{
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
	};*/
public:
	GMap(GStatus hard, GStatus mode = GStatus::Choose_Standard) :worker(mode) 
	{
		//初始化地图
		srand(unsigned int(time(NULL)));
		//return;
		int base = (int)30;
		for (int i = 0; i < base; )
		{
			//while (true)
			{
				GPoint pos = { rand() % 9,rand() % 9 };
				//cout << pos.Horizontal << "  " << pos.Vertical << endl;
				if (map_info[pos.Horizontal][pos.Vertical] == 0)
				{
					map_info[pos.Horizontal][pos.Vertical] = -(rand() % 9 + 1);
					if (worker.canbe(map_info))
					{
						++i;
						continue;
					}
					map_info[pos.Horizontal][pos.Vertical] = 0;
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
	GO_Msg Stringify();//序列化
	int GetVal(GPoint pos)
	{
		if (!InArea(pos))
		{
			cout << "\nGMap访问越界\n";
			return 0;
		}
		return map_info[pos.Vertical][pos.Horizontal];
	}
	bool SetNumber(GPoint pos, int num)//返回操作是否成功
	{
		//输入数字
		if (!InArea(pos))
			return false;
		if (num >= 0 || num <= 9)//保证为有效数字
		{
			if (map_info[pos.Vertical][pos.Vertical] < 0)//规定小于0的为最初的数字
				return false;
			map_info[pos.Vertical][pos.Horizontal] = num;
			return true;
		}
		return false;
	}
	bool WorkOut()
	{
		return worker.getanswer(map_info);
	}
	bool IsWin()
	{

	}
};