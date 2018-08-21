// Swat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "utilities.h"
#include "User.h"
#include "System.h"

#include <iostream>
#include <string>
#include <stdlib.h>

#include <Windows.h>
#include <stdio.h>
#include <lm.h>

#pragma comment(lib, "netapi32.lib")


int main()
{
	/*
	User gustavBourdon("Gustav Bourdon");
	std::cout << "Name: " << gustavBourdon.username() << std::endl
		<< "Is Password Blank: " << gustavBourdon.is_pass_blank()
		<< std::endl << "Is Administrator: " << gustavBourdon.is_admin() << std::endl << std::endl;

	User blank("Blank");
	std::cout << "Name: " << blank.username() << std::endl
		<< "Is Password Blank: " << blank.is_pass_blank()
		<< std::endl << "Is Administrator: " << blank.is_admin() << std::endl;
	*/
	std::string spacer(40, '-');
	System localhost;
	std::vector<User> users = localhost.get_users();
	for (std::vector<User>::iterator user = users.begin(); user != users.end(); ++user) {
		std::cout << user->username() << ':' << std::endl;
		std::vector<std::string> groups = user->groups();
		for (std::vector<std::string>::iterator group = groups.begin(); group != groups.end(); ++group) {
			std::cout << '\t' << *group << std::endl;
		}
		std::cout << spacer << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Maximum Password Age: "	 << sec_to_day(localhost.max_pass_age()) << " days"		  << std::endl;
	std::cout << "Minimum Password Age: "	 << sec_to_day(localhost.min_pass_age()) << " days"	   	  << std::endl;
	std::cout << "Minimum Password Length: " << localhost.min_pass_len()			 << " characters" << std::endl;
	std::cout << "Password History: "		 << localhost.pass_hist_len()			 << " passwords"  << std::endl;
	
	std::cin.get();
    return 0;
}

