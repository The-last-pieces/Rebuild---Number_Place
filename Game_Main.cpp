#include "Game_Control.h"

int main(void)
{
	try
	{
		GControl test;
		test.OnLoad();
	}
	catch (const std::exception& err)
	{
		fstream fs(R"(.\data\log.txt)", std::ios_base::app);
		if (fs)
			fs << err.what() << endl << "Ê±¼ä:" << clock() << endl << endl;
		fs.close();
	}
	return 0;
}