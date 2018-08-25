#pragma once
#include <Windows.h>
void set_green();
void set_red();
void set_clear(CONSOLE_SCREEN_BUFFER_INFO csbi);
void set_clear(int color = 0x07);