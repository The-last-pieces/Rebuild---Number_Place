#include "Game_Control.h"

template<typename type,typename vtype>
vector<type>split(type info, vtype val)
{
	type temp;
	vector<type>result;
	for (auto node : info)
	{
		if (node == val)
		{
			if (temp.size())
				result.push_back(temp);
			temp.clear();
		}
		else
		{
			temp.push_back(node);
		}
	}
	return result;
}

int main(void)
{

	GControl test;
	test.OnLoad();
	return 0;
}