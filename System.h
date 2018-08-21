#pragma once
#include "User.h"
#include <string>
#include <vector>

class System
{
public:
	System();
	System(std::string computer);
	~System();
	// Returns a vector of psudo-normal accounts (Accounts that can be logged onto. This might accidentily include some system accounts)
	std::vector<User> get_users();
	// Returns the minimum age of a password in seconds
	int min_pass_age();
	// Returns how old a password can be before it needs to be changed in seconds
	int max_pass_age();
	// Returns the minimum password length
	int min_pass_len();
	// Returns the length of the password history
	int pass_hist_len();
	/*
	// Returns if passwords have to be complex
	bool complex_pass_req();
	// Returns if passwords are stored using reversable encryption
	bool unsafe_pass_storage();
	// Returns if the administrator account can be logged onto
	bool admin_account_on();
	// Returns if the guest account can be logged onto
	bool guest_account_on();
	*/
private:
	std::string server;
};

