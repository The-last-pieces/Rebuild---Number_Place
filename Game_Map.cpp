#include "Game_Map.h"

//GMap���ֹ��ܵ�ʵ��
GO_Msg GMap::Stringify()
{
	GO_Msg info;
	//info.AllStrings.push_back({ "\033[32m" ,{},GOType::GameTable });
	for (int x = 0; x < 13; ++x)
	{
		string temp;
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
					temp.push_back(NumtoChar(GetVal({ x - x / 4 - 1,y - y / 4 - 1 })));
			}
		}
		info.AllStrings.push_back({ temp ,{},GOType::GameTable });
	}
	//info.AllStrings.push_back({ "\033[0m" ,{},GOType::GameTable });
	return info;
}