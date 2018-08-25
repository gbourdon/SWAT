#include "stdafx.h"
#include "System.h"

#include <vector>
#include <string>

#include <Windows.h>
#include <LM.h>

#include "utilities.h"

#pragma comment(lib, "netapi32.lib")

System::System()
{
	server = "";
}

System::System(std::string computer)
{
	server = computer;
}


System::~System()
{
}


// Returns a vector of psudo-normal accounts (Accounts that can be logged onto. This might accidentily include some system accounts)
std::vector<User> System::get_users()
{
	std::vector<User> users;
	PNET_DISPLAY_USER pBuff, p;
	DWORD res, dwRec, i = 0;
	//
	// You can pass a NULL or empty string
	//  to retrieve the local information.
	//
	std::wstring computerW = s_to_wide_s(server);
	LPCWSTR szServer = computerW.c_str();

	do // begin do
	{
		//
		// Call the NetQueryDisplayInformation function;
		//   specify information level 3 (group account information).
		//
		res = NetQueryDisplayInformation(szServer, 1, i, 1000, MAX_PREFERRED_LENGTH, &dwRec, (PVOID*)&pBuff);
		//
		// If the call succeeds,
		//
		if ((res == ERROR_SUCCESS) || (res == ERROR_MORE_DATA))
		{
			p = pBuff;
			for (; dwRec > 0; dwRec--)
			{
				//
				// Adds the user to the list of users.
				//
				User user(wchar_to_s(p->usri1_name));
				users.push_back(user);
				//
				// If there is more data, set the index.
				//
				i = p->usri1_next_index;
				p++;
			}
			//
			// Free the allocated memory.
			//
			NetApiBufferFree(pBuff);
		}
		else
			printf("Error: %u\n", res);
		//
		// Continue while there is more data.
		//
	} while (res == ERROR_MORE_DATA); // end do
	return users;
}


// Returns the minimum age of a password in seconds
int System::min_pass_age()
{
	int age;
	USER_MODALS_INFO_0 *pBuf = NULL;
	NET_API_STATUS nStatus;
	LPCTSTR pszServerName = NULL;
	if (server != "") {
		std::wstring serverW = s_to_wide_s(server);
		pszServerName = serverW.c_str();
	}

	//
	// Call the NetUserModalsGet function; specify level 0.
	//
	nStatus = NetUserModalsGet((LPCWSTR)pszServerName,
		0,
		(LPBYTE *)&pBuf);
	//
	// If the call succeeds, print the global information.
	//
	if (nStatus == NERR_Success)
		age = pBuf->usrmod0_min_passwd_age;
	// Otherwise, print the system error.
	else
		fprintf(stderr, "A system error has occurred: %d\n", nStatus);
	//
	// Free the allocated memory.
	//
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);
	return age;
}


// Returns how old a password can be before it needs to be changed in seconds
int System::max_pass_age()
{
	int age;
	USER_MODALS_INFO_0 *pBuf = NULL;
	NET_API_STATUS nStatus;
	LPCTSTR pszServerName = NULL;
	if (server != "") {
		std::wstring serverW = s_to_wide_s(server);
		pszServerName = serverW.c_str();
	}

	//
	// Call the NetUserModalsGet function; specify level 0.
	//
	nStatus = NetUserModalsGet((LPCWSTR)pszServerName,
		0,
		(LPBYTE *)&pBuf);
	//
	// If the call succeeds, print the global information.
	//
	if (nStatus == NERR_Success)
		age = pBuf->usrmod0_max_passwd_age;
	// Otherwise, print the system error.
	else
		fprintf(stderr, "A system error has occurred: %d\n", nStatus);
	//
	// Free the allocated memory.
	//
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);
	return age;
}

// Returns the minimum password length
int System::min_pass_len()
{
	int len;
	USER_MODALS_INFO_0 *pBuf = NULL;
	NET_API_STATUS nStatus;
	LPCTSTR pszServerName = NULL;
	if (server != "") {
		std::wstring serverW = s_to_wide_s(server);
		pszServerName = serverW.c_str();
	}

	//
	// Call the NetUserModalsGet function; specify level 0.
	//
	nStatus = NetUserModalsGet((LPCWSTR)pszServerName,
		0,
		(LPBYTE *)&pBuf);
	//
	// If the call succeeds, print the global information.
	//
	if (nStatus == NERR_Success)
		len = pBuf->usrmod0_min_passwd_len;
	// Otherwise, print the system error.
	//
	else
		fprintf(stderr, "A system error has occurred: %d\n", nStatus);
	//
	// Free the allocated memory.
	//
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);
	return len;
}

int System::pass_hist_len()
{
	int len;
	USER_MODALS_INFO_0 *pBuf = NULL;
	NET_API_STATUS nStatus;
	LPCTSTR pszServerName = NULL;
	if (server != "") {
		std::wstring serverW = s_to_wide_s(server);
		pszServerName = serverW.c_str();
	}

	//
	// Call the NetUserModalsGet function; specify level 0.
	//
	nStatus = NetUserModalsGet((LPCWSTR)pszServerName,
		0,
		(LPBYTE *)&pBuf);
	//
	// If the call succeeds, print the global information.
	//
	if (nStatus == NERR_Success)
		len = pBuf->usrmod0_password_hist_len;
	// Otherwise, print the system error.
	//
	else
		fprintf(stderr, "A system error has occurred: %d\n", nStatus);
	//
	// Free the allocated memory.
	//
	if (pBuf != NULL)
		NetApiBufferFree(pBuf);
	return len;
}



/*
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
*/