#include "colors.h"
#include "stdafx.h"
#include <Windows.h>

void set_green() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, 0x0A);
}

void set_red() {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, 0x0c);
}
void set_clear(CONSOLE_SCREEN_BUFFER_INFO csbi) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, csbi.wAttributes);
}
void set_clear(int color = 0x07) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(out, color);
}