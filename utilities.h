#pragma once
#include <vector>
#include <string>
#include <locale>
#include <sstream>

#include <windows.h>

std::string wchar_to_s(const wchar_t *s, char dfault = '?', const std::locale& loc = std::locale());
const wchar_t* s_to_wchar(std::string str);
std::wstring s_to_wide_s(const std::string& s);

std::vector<std::string> get_groups(std::string user, std::string server = "");

int sec_to_day(int day);
int day_to_sec(int sec);
