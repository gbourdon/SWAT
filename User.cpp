#include "stdafx.h"
#include "User.h"

#include <string>
#include <vector>
#include <algorithm>

#include <windows.h>
#include <lm.h>

#include "utilities.h"

#pragma comment(lib, "netapi32.lib")


User::User()
{
}

User::User(std::string username, std::string server)
{
	user = username;
	serv = server;
}

User::User(LPCWSTR username, LPCWSTR server)
{
	user = wchar_to_s(username);
	serv = wchar_to_s(server);
}


User::~User()
{
}


// Returns the username of the user
std::string User::username()
{
	return user;
}


// Return if the user is an administrator
bool User::is_admin()
{
	std::vector<std::string> group = groups();
	if (std::find(group.begin(), group.end(), "Administrators") != group.end())
		return true;
	return false;
}


// Returns if the user's password is blank
bool User::is_pass_blank()
{
	LPCSTR username = user.c_str();
	LPCSTR server = serv.c_str();
	HANDLE out;
	if (server == "")
		server = ".";
	if (LogonUserA(username, server, "", LOGON32_LOGON_NETWORK, LOGON32_PROVIDER_DEFAULT, &out) != 0)
		return true;
	else {
		DWORD error = GetLastError();
		if (error == ERROR_LOGON_FAILURE)
			return false;
		//else
			//fprintf(stderr, "A system error has occurred: %d\n", error);
	}
	return true;
}

bool User::is_real()
{
	std::vector<std::string> group = groups();
	if (std::find(group.begin(), group.end(), "Administrators") != group.end() || std::find(group.begin(), group.end(), "Users") != group.end())
		return true;
	return false;
}

std::vector<std::string> User::groups()
{
	std::wstring userW = s_to_wide_s(user);
	LPCWSTR username = userW.c_str();
	// How to convert a string to a lpcwstr:
	// Create a wstring via s_to_wide_s
	// Create a LPCWSTR from the c_str of the wstring
	std::wstring serverW = s_to_wide_s(serv);
	LPCWSTR server = serverW.c_str();

	std::vector<std::string> out;

	LPLOCALGROUP_USERS_INFO_0 pBuf = NULL;
	DWORD dwLevel = 0;
	DWORD dwFlags = LG_INCLUDE_INDIRECT;
	DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
	DWORD dwEntriesRead = 0;
	DWORD dwTotalEntries = 0;
	NET_API_STATUS nStatus;
	//
	// Call the NetUserGetLocalGroups function
	//  specifying information level 0.
	//
	//  The LG_INCLUDE_INDIRECT flag specifies that the
	//   function should also return the names of the local
	//   groups in which the user is indirectly a member.
	//
	nStatus = NetUserGetLocalGroups(server,
		username,
		dwLevel,
		dwFlags,
		(LPBYTE *)&pBuf,
		dwPrefMaxLen,
		&dwEntriesRead,
		&dwTotalEntries);
	//
	// If the call succeeds,
	//
	if (nStatus == NERR_Success)
	{
		LPLOCALGROUP_USERS_INFO_0 pTmpBuf;
		DWORD i;
		DWORD dwTotalCount = 0;




		if ((pTmpBuf = pBuf) != NULL)
		{
			//fprintf(stderr, "\nLocal group(s):\n");
			//
			// Loop through the entries and 
			//  print the names of the local groups 
			//  to which the user belongs. 
			//
			for (i = 0; i < dwEntriesRead; i++)
			{
				//assert(pTmpBuf != NULL);

				if (pTmpBuf == NULL)
				{
					fprintf(stderr, "An access violation has occurred\n");
					break;
				}

				//wprintf(L"\t-- %s\n", pTmpBuf->lgrui0_name);
				out.push_back(wchar_to_s(pTmpBuf->lgrui0_name));

				pTmpBuf++;
				dwTotalCount++;
			}
		}
	}
	else {
		fprintf(stderr, "A system error has occurred: %d\n", nStatus);
	}

	//
	// Free the allocated memory.
	//
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);

	return out;
}
