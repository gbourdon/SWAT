// Swat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "utilities.h"
#include "User.h"
#include "System.h"
#include "colors.h"

#include <iostream>
#include <string>
#include <vector>
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
	
	System localhost;
	Check testsA[] = {
		Check("Required Pasword Length", "characters", 8, localhost.min_pass_len()),
		Check("Maximum Password Age", "days", 90, localhost.max_pass_age())
	};
	std::vector<Check> tests(testsA, std::end(testsA));
	
	for (std::vector<Check>::iterator test = tests.begin(); test != tests.end(); ++test) {
		if (test->checkValue(test->expectedValue, test->actualValue)) {
			print_good();
			std::cout << test->name << " is within spec." << std::endl;
		} else {
			print_fail();
			std::cout << test->name << " should be " << test->expectedValue << ' ' << test->unit << ", not " << test->actualValue << ' ' << test->unit << '.' << std::endl;
		}
	}
	
	set_clear();
	std::cin.get();
    return 0;
}

