// Swat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "utilities.h"
#include "User.h"
#include "System.h"
#include "colors.h"

#include <iostream>
#include <string>
#include <functional>
#include <stdlib.h>

#include <Windows.h>
#include <stdio.h>
#include <lm.h>

#pragma comment(lib, "netapi32.lib")

void print_fail() {
	std::cout << '<'; set_red(); std::cout << "Fail"; set_clear(); std::cout << "> ";
}

void print_good() {
	std::cout << '<'; set_green(); std::cout << "Good"; set_clear(); std::cout << "> ";
}

bool greater_than(int expected, int actual) {
	return actual >= expected;
}

struct Check {
	Check(std::string checkName, std::string checkUnit, int eValue, int aValue, bool checkVal(int, int) = greater_than) {
		name = checkName;
		unit = checkUnit;
		expectedValue = eValue;
		actualValue = aValue;
		checkValue = checkVal;
	}
	std::string name;
	std::string unit;
	int expectedValue;
	int actualValue;
	bool (*checkValue)(int, int);
};

int main()
{
	SetConsoleTitle(_T("SWAT: Super Windows Audit Tool")); // Sets the title of the window to something useful
	//set_red();
	/*
	User gustavBourdon("Gustav Bourdon");
	std::cout << "Name: " << gustavBourdon.username() << std::endl
		<< "Is Password Blank: " << gustavBourdon.is_pass_blank()
		<< std::endl << "Is Administrator: " << gustavBourdon.is_admin() << std::endl << std::endl;

	User blank("Blank");
	std::cout << "Name: " << blank.username() << std::endl
		<< "Is Password Blank: " << blank.is_pass_blank()
		<< std::endl << "Is Administrator: " << blank.is_admin() << std::endl;
	
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
	*/
	System localhost;
	Check test("Required Pasword Length", "characters", 8, localhost.min_pass_len());
	/*
	if (localhost.min_pass_len() < 8) {
		print_fail();
		std::cout << "Required Password Length should be 8 characters, not " << localhost.min_pass_len() << " characters." << std::endl;
	} else {
		print_good();
		std::cout << "Required Password Length is within spec.";
	}
	*/
	if (test.checkValue(test.expectedValue, test.actualValue)) {
		print_good();
		std::cout << test.name << " is within spec." << std::endl;
	}
	else {
		print_fail();
		std::cout << test.name << " should be " << test.expectedValue << ' ' << test.unit << ", not " << test.actualValue << ' ' << test.unit << '.' << std::endl;
	}
	if (sec_to_day(localhost.max_pass_age()) < 90) {
		print_fail();
		std::cout << "Maximum Password Age should be 90 days, not " << sec_to_day(localhost.max_pass_age()) << " days." << std::endl;
	} else {
		print_good();
		std::cout << "Maximum Password Age is within spec.";
	}
	set_clear();
	std::cin.get();
    return 0;
}

