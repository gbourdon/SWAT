#include "stdafx.h"
#include "System.h"


System::System()
{
}


System::~System()
{
}


// Returns a vector of psudo-normal accounts (Accounts that can be logged onto. This might accidentily include some system accounts)
std::vector<User> System::get_users()
{
	// TODO: Add your implementation code here.
	return std::vector<User>();
}


// Returns the minimum age of a password in seconds
int System::min_pass_age()
{
	// TODO: Add your implementation code here.
	return 0;
}


// Returns how old a password can be before it needs to be changed in seconds
int System::max_pass_age()
{
	// TODO: Add your implementation code here.
	return 0;
}


// Returns if passwords have to be complex
bool System::complex_pass_req()
{
	// TODO: Add your implementation code here.
	return false;
}


// Returns if passwords are stored using reversable encryption
bool System::unsafe_pass_storage()
{
	// TODO: Add your implementation code here.
	return false;
}


// Returns if the administrator account can be logged onto
bool System::admin_account_on()
{
	// TODO: Add your implementation code here.
	return false;
}


// Returns if the guest account can be logged onto
bool System::guest_account_on()
{
	// TODO: Add your implementation code here.
	return false;
}
