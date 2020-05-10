#include "Game_Map.h"

GO_Msg GMap::Stringify()
{
	GO_Msg info;
	for (int x = 0; x < 13; ++x)
	{
		string temp;
		int cs = 0;
		for (int y = 0; y < 13; ++y)
		{
			if (x % 4 == 0 && y % 4 == 0)
			{
				temp.push_back(AngleChar);
			}
			else
			{
				if (x % 4 == 0)
				{
					temp.push_back(HorizonChar);
				}
				else if (y % 4 == 0)
				{
					temp.push_back(VerticalChar);
				}
				else
				{
					auto val = GetVal({ x - x / 4 - 1,y - y / 4 - 1 });
					if (val >= 0)
						temp.push_back(NumtoChar(val));
					else
					{
						temp += string("\033[43;31m") + NumtoChar(val) + "\033[0m";
						++cs;
					}
				}
			}
		}
		info.AllStrings.push_back({ temp ,{},GOType::GameTable ,12 * cs });
	}
	return info;
}