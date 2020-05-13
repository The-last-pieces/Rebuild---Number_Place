#pragma once
#include "Game_Output.h"
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
	class GMapWorker
	{
	public:
		array<array<int, Map_Size>, Map_Size> canans;
		int anscounts = 0;
	private:
		GSetType Gmode = GSetType::Choose_Standard;

		array<array<bool, Map_Size>, Map_Size> blocks;
		array<array<bool, Map_Size>, Map_Size> cols;
		array<array<bool, Map_Size>, Map_Size> rows;
		array<array<bool, 2 * Map_Size - 1>, 2 * Map_Size - 1> llines;//左上右下
		array<array<bool, 2 * Map_Size - 1>, 2 * Map_Size - 1> rlines;//右上左下

	private:
		bool dealmap(array<array<int, Map_Size>, Map_Size>& minfo)
		{
			if (anscounts > 1)
				return false;

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
								!blocks[k][num]
								)
							{
								/*if (Gmode == GSetType::Choose_Classic)
								{
									if (rlines[x + y][num] || llines[Map_Size - 1 - x + y][num])
									{
										continue;
									}
								}*/

								// l对于的数字l+1没有在行列块中出现
								rlines[x + y][num] =
									llines[Map_Size - 1 - x + y][num] =
									rows[x][num] =
									cols[y][num] =
									blocks[k][num] = true;
								minfo[x][y] = 1 + num;// 下标加1

								if (dealmap(minfo))
								{
									anscounts++;
								}
								rlines[x + y][num] =
									llines[Map_Size - 1 - x + y][num] =
									rows[x][num] =
									cols[y][num] =
									blocks[k][num] = false;// 递进失败则回溯
								minfo[x][y] = 0;
							}
						}
						return false;// a[i][j]==0时，l发现都不能填进去
					}
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

		bool tryset(int& pos, int x, int y)
		{
			if (pos == 0)
			{
				int val = 0, num = 0, k = 0;
				int rdnum[9] = { 1,2,3,4,5,6,7,8,9 };
				for (int i = 0; i < 20; ++i)
				{
					swap(rdnum[rand() % 9], rdnum[rand() % 9]);
				}
				for (int i = 0; i < 9; ++i)
				{
					val = -rdnum[i], num = abs(val) - 1, k = x / 3 * 3 + y / 3;
					if (!(
						rows[x][num] ||
						cols[y][num] ||
						blocks[k][num]))
					{
						/*if (GSetType::Choose_Classic == Gmode)
						{
							if (rlines[x + y][num] || llines[Map_Size - 1 - x + y][num])
							{
								continue;
							}
						}*/
						rlines[x + y][num] =
							llines[Map_Size - 1 - x + y][num] =
							rows[x][num] =
							cols[y][num] =
							blocks[k][num] = true;

						pos = val;
						return true;
					}
				}
				pos = 0;
			}
			return false;
		}
	public:
		GMapWorker(GSetType _mode) :Gmode(_mode)
		{
            predeal();
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

						/*if (Gmode == GSetType::Choose_Classic)
						{
							k = x + y;

							if (llines[k][val])
								return false;
							llines[k][val] = true;

							k = 8 - x + y;

							if (rlines[k][val])
								return false;
							rlines[k][val] = true;
						}*/
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

			dealmap(temp);
			if (anscounts == 1)
			{
				minfo = canans;
				return true;
			}
			else
			{
				return false;
			}

		}

		bool getamap(array<array<int, Map_Size>, Map_Size>& mp, int base)
		{
			int mload = 1000;
			if (base < 30)
				mload = 100;
			while (1)
			{
				srand((unsigned int)(time(NULL)));
				for (int mt = 0; mt < mload; ++mt)
				{
					mp.fill({ 0 });
					predeal();
					GO_Msg msg;
					for (int i = 0; i < base; )
					{
						GPoint pos = { rand() % 9,rand() % 9 };

						if (tryset(mp[pos.Horizontal][pos.Vertical], pos.Horizontal, pos.Vertical))
						{
							++i;
						}
					}

					stringstream tempstr;
					tempstr << "正在尝试生成数据:" << string(mt / (mload / 20), '#') << string(((mload - mt) / (mload / 20)), ' ') << "<>"[(mt / 50) % 2] << "    初始数:" << base << "个   ";
					msg.AllStrings.push_back({ tempstr.str() ,{1,1},GOType::SelfDef });
					msg.AllStrings.push_back({ "//初始数小于30时生成速度会明显降低,请耐心等待" ,{2,2},GOType::SelfDef });

					GOutput->Render(msg);


					auto temp = mp;
					if (getanswer(temp))
					{
						canans = temp;
						return true;
					}
				}
			}
		}
	} worker;

	GSetType hard;
	GSetType mode;

	array<array<int, Map_Size>, Map_Size> map_info = {};
private:
	array<array<int, Map_Size>, Map_Size> answer = {};
public:
	GMap() :worker(GSetType::Choose_Standard), hard(GSetType::Choose_Normal), mode(GSetType::Choose_Standard)
	{

	}
	GMap(GSetType _hard, GSetType _mode = GSetType::Choose_Standard) :worker(_mode), hard(GSetType::Choose_Normal), mode(_mode)
	{
		//初始化地图
		worker.getamap(map_info, int(_hard));
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

	stack<pair<GPoint, int>> history;

	void Gcanans()
	{
		auto temp = map_info;
		if (worker.canans[0][0] != 0)
			return;
		worker.getanswer(temp);
	}
public:
	bool Back()
	{
		if (history.empty())
			return false;
		auto temp = history.top();
		history.pop();
		map_info[temp.first.Vertical][temp.first.Horizontal] = temp.second;
		return true;
	}

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
			if (map_info[pos.Vertical][pos.Horizontal] < 0)//规定小于0的为最初的数字
				return false;
			if (map_info[pos.Vertical][pos.Horizontal] == num)
				return false;

			history.push({ pos,map_info[pos.Vertical][pos.Horizontal] });
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
		Gcanans();
		return map_info == worker.canans;
	}
};
