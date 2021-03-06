// Swat.cpp : Checking compliance to CyberPatriot Standards
//

#include "stdafx.h"
#include "utilities.h"
#include "User.h"
#include "System.h"
#include "colors.h"

#include <iostream>
#include <string>
#include <vector>
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

struct Check {
	Check(std::string checkName, std::string checkUnit, int eValue, int aValue, bool checkVals(int, int) = [](int expected, int actual) {return actual >= expected; }) {
		name = checkName;
		unit = checkUnit;
		expectedValue = eValue;
		actualValue = aValue;
		checkValues = checkVals;
	}
	std::string name;
	std::string unit;
	int expectedValue;
	int actualValue;
	bool (*checkValues)(int, int);
};

struct VectorCheck{
	VectorCheck(std::string checkName, std::vector<User> in, int max, bool checkVals(User)) {
		name = checkName;
		users = in;
		threshold = max;
		isMatch = checkVals;
	}
	
	std::vector<User> getMatches() {
		matches.clear();
		for (std::vector<User>::iterator user = users.begin(); user != users.end(); ++user)
			if (isMatch(*user))
				matches.push_back(*user);
		return matches;
	}

	std::string name;
	std::vector<User> users;
	std::vector<User> matches;
	int threshold;
	bool (*isMatch)(User);
};

int main()
{
	SetConsoleTitle(_T("SWAT: Super Windows Audit Tool")); // Sets the title of the window to something useful
	
	System localhost;
	std::vector<User> users = localhost.get_users();
	// To add a check, add it to this array. The syntax for creating a check is:
	// String: Name of Check, String: Unit of check,
	// Integer: Expected value (The recomended value),
	// Integer: Actual Value (The current setting of the value on the system),
	// and Check Values bool(int Expected Value ,int Actual Value) (Takes the expected and actual values, and returns if they pass the check)
	Check testsA[] = {
		Check("Required Pasword Length", "characters", 8, localhost.min_pass_len()),
		Check("Maximum Password Age", "days", 90, localhost.max_pass_age(), [](int expected, int actual) {return actual <= expected; }),
		Check("Minimum Password Age", "days", 10, localhost.min_pass_age()),
		Check("Password History Length", "passwords", 5, localhost.pass_hist_len())
	};

	// To add a check on all users, add it to this array. The syntax for creating a check is:
	// String: Name of check (What would you say after "There are users with ..."?)
	// Vector<Users>: The users you want to check. Usually you can just use "users"
	// Int: Threshold (After more than x users have this, it's a problem)
	// bool(User): The check to run on each user (It would be easier if C++ was functional...)
	std::vector<Check> tests(testsA, std::end(testsA));
	VectorCheck userTestsA[] = {
		VectorCheck("Blank Passwords", users, 1, [](User user) {return (user.is_real() && user.is_pass_blank()); }),
		VectorCheck("Administrator Access", users, 2, [](User user) {return user.is_admin(); })
	};
	std::vector<VectorCheck> userTests(userTestsA, std::end(userTestsA));
	
	// Runs the checks and tells if they passed or failed
	for (auto test: tests) {
		if (test.checkValues(test.expectedValue, test.actualValue)) {
			print_good();
			std::cout << test.name << " is within spec. (Expected " 
				<< test.expectedValue << ' ' << test.unit << ", recieved " << test.actualValue << ' ' << test.unit << ')' << std::endl;
		} else {
			print_fail();
			std::cout << test.name << " should be " << test.expectedValue << ' ' << test.unit << ", not " << test.actualValue << ' ' << test.unit << '.' << std::endl;
		}
	}
	
	// Runs the checks on the users and tells if they passed or failed
	for (auto test: userTests) {
		if (test.getMatches().size() > test.threshold) {
			print_fail();
			std::cout << "There are more than " << test.threshold << " users with " << test.name << " They are:" << std::endl;
			for (auto user: test.matches)
				std::cout << '\t' << user.username() << std::endl;
		} else {
			print_good();
			std::cout << "There are less than " << test.threshold << " users with " << test.name << '.' << std::endl;
		}
	}

	set_clear(); // Clears any remaining color settings
	std::cin.get(); // Pauses the program (This is designed to be run from the desktop)
    return 0;
}
