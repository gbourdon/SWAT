# User Class
## The user class provides an interface for modifying and viewing user data

## username()
Returns the username of the user (string)

## is_admin()
Return if the user is an administrator (bool)

## is_pass_blank()
Returns if the user's password is blank (bool)

void main(int argc, char *argv[])
{
	PNET_DISPLAY_USER pBuff, p;
	DWORD res, dwRec, i = 0;
	//
	// You can pass a NULL or empty string
	//  to retrieve the local information.
	//
	TCHAR szServer[255] = TEXT("");

	if (argc > 1)
		//
		// Check to see if a server name was passed;
		//  if so, convert it to Unicode.
		//
		MultiByteToWideChar(CP_ACP, 0, argv[1], -1, szServer, 255);

	do // begin do
	{
		//
		// Call the NetQueryDisplayInformation function;
		//   specify information level 3 (group account information).
		//
		res = NetQueryDisplayInformation(NULL, 1, i, 1000, MAX_PREFERRED_LENGTH, &dwRec, (PVOID*)&pBuff);
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
					"Flags: %u\n"
					"--------------------------------\n",
					p->usri1_name,
					p->usri1_comment,
					p->usri1_user_id,
					p->usri1_flags);
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
	std::cin.get();
	return;
}