#pragma once
#include "Game_Input.h"

int vertical();
int horizontal();
void moveto(GPoint pos);
GB_Msg CreateMsg(double sleeptime);//Sleep��Ϣ
GB_Msg CreateMsg(GResType ptr);//Change_View��Ϣ
GB_Msg CreateMsg(GSetType mode, GMType mtype);//Change_Mode��Ϣ
GB_Msg CreateMsg(GMType mtype);//��ͨ��Ϣ

#ifdef debug
template <typename T>
void DebugLog(T what);
#endif // debug