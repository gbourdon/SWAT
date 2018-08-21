#include "utilities.h"
#include "stdafx.h"

#include <string>
#include <sstream>
#include <vector>

#include <windows.h>
#include <lm.h>
#pragma comment(lib, "netapi32.lib")

// Converts a wchar array to a std::string
std::string wchar_to_s(const wchar_t *s, char dfault = '?', const std::locale& loc = std::locale())
{
	std::ostringstream stm;

	while (*s != L'\0') {
		stm << std::use_facet< std::ctype<wchar_t> >(loc).narrow(*s++, dfault);
	}
	return stm.str();
}

// Converts a std::string to a wchar array, unstable / have to assign to something, can't use in function
const wchar_t* s_to_wchar(std::string str)
{
	std::wstring wstr(str.begin(), str.end());
	const WCHAR * wcharStr = wstr.c_str();
	return wcharStr;
}

// Widens a string
std::wstring s_to_wide_s(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
// Gets all the groups user user is in on server
std::vector<std::string> get_groups(std::string user, std::string server)
{
	std::wstring userW = s_to_wide_s(user);
	LPCWSTR userStr = userW.c_str();
	// How to convert a string to a lpcwstr:
	// Create a wstring via s_to_wide_s
	// Create a LPCWSTR from the c_str of the wstring
	std::wstring serverW = s_to_wide_s(server);
	LPCWSTR serverStr = serverW.c_str();

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
	nStatus = NetUserGetLocalGroups(serverStr,
		userStr,
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
		//
		// If all available entries were
		//  not enumerated, print the number actually 
		//  enumerated and the total number available.
		//
		//if (dwEntriesRead < dwTotalEntries)
			//fprintf(stderr, "\nTotal entries: %d", dwTotalEntries);
		//
		// Otherwise, just print the total.
		//
		//printf("\nEntries enumerated: %d\n", dwTotalCount);


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

int sec_to_day(int day)
{
	return day / 86400;;
}

int day_to_sec(int sec)
{
	return  sec * 86400;;
}
