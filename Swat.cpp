// Swat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "utilities.h"
#include <iostream>
#include <string>
#include <stdlib.h>

#include <Windows.h>
#include <stdio.h>
#include <lm.h>

#pragma comment(lib, "netapi32.lib")


int main()
{
	/* Debuging relics
	std::cout << "ERROR_INVALID_LEVEL: " << ERROR_INVALID_LEVEL << std::endl;
	std::cout << "ERROR_ACCESS_DENIED: " << ERROR_ACCESS_DENIED << std::endl;
	std::cout << "ERROR_INVALID_PARAMETER: " << ERROR_INVALID_PARAMETER << std::endl;
	std::cout << "ERROR_MORE_DATA: " << ERROR_MORE_DATA << std::endl;
	std::cout << "ERROR_NOT_ENOUGH_MEMORY: " << ERROR_NOT_ENOUGH_MEMORY << std::endl;
	std::cout << "RPC_S_SERVER_UNAVAILABLE: " << RPC_S_SERVER_UNAVAILABLE << std::endl;*/
	/*
	std::vector<std::string> groups = get_groups("Gustav Bourdon");
	for (std::vector<std::string>::iterator group = groups.begin(); group != groups.end(); ++group) {
		std::cout << *group << std::endl;
	}
	*/
	PNET_DISPLAY_USER pBuff, p;
	DWORD res, dwRec, i = 0;
	//
	// You can pass a NULL or empty string
	//  to retrieve the local information.
	//
	TCHAR szServer[255] = TEXT("");

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
			for (; dwRec>0; dwRec--)
			{
				//
				// Print the retrieved group information.
				//
				printf("Name:      %S\n"
					"Comment:   %S\n"
					"User ID:  %u\n"
					"--------------------------------\n",
					p->usri1_name,
					p->usri1_comment,
					p->usri1_user_id
					);
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
    return 0;
}

