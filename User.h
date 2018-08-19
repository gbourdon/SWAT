#pragma once
#include <string>
#include <vector>
#include <Windows.h>
class User
{
public:
	User();
	User(std::string username, std::string server = "");
	User(LPCWSTR username, LPCWSTR server = TEXT(""));
	~User();
	// Returns the username of the user
	std::string username();
	// Return if the user is an administrator
	bool is_admin();
	// Returns if the user's password is blank
	bool is_pass_blank();
	// Returns the groups the user is in
	std::vector<std::string> groups();
private:
	std::string user;
	std::string serv;
};

