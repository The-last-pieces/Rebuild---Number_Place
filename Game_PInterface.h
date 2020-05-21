#pragma once
#include "Game_Input.h"

int vertical();
int horizontal();
void moveto(GPoint pos);
GB_Msg CreateMsg(double sleeptime);//Sleep��Ϣ
GB_Msg CreateMsg(GResType ptr);//Change_View��Ϣ
GB_Msg CreateMsg(GSetType mode, GMType mtype);//Change_Mode��Ϣ
GB_Msg CreateMsg(GMType mtype);//��ͨ��Ϣ

//welcome menu play victory  .mp3
void PlayMusic(const wstring& msc, bool ifrepeat = 1, double start = 2.0);

#ifdef debug
template <typename T>
void DebugLog(T what);
#endif // debug