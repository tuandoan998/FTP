// FTP-Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FTP-Client.h"
#include <afxsock.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			_tprintf(_T("Fatal Error: MFC initialization failed\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			cout << "FPT-Client" << endl;
			if (AfxSocketInit() == FALSE)
			{
				cout << "Khong the khoi tao Socket Libraray";
				return FALSE;
			}
			
			CSocket Client;
			Client.Create(0, SOCK_STREAM, NULL);//auto choose client port, TCP type, default clinet IP
			// Ket noi den Server
			if (Client.Connect(_T("127.0.0.1"), 21) != 0)
			{
				cout << "Ket noi toi Server thanh cong !!!" << endl << endl;

				char ClientMsg[100];
				int MsgSize;

				do
				{
					cin >> ClientMsg;
				} while (1);

			}
			else
			{
				cout << "Khong the ket noi den Server !!!" << endl;
			}

			// Dong ket noi
			Client.Close();
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: GetModuleHandle failed\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
