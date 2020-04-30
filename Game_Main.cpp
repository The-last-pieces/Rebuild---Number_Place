#include "Game_Control.h"

int main(void)
{
	/*while (true)
	{
		GInput->Update();
		GOutput->moveto(GInput->Info.mouse_pos);
		Sleep(50);
	}*/

	try
	{
		
		GControl test;
		test.OnLoad();
	}
	catch (const std::exception&)
	{

	}
	return 0;
}