// FTP-Client.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "FTP-Client.h"
#include <afxsock.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#define MAX 1000
#endif


#define _CRT_SECURE_NO_WARNINGS

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

				char ClientMsg[1000];
				int MsgSize = 0;
				char *temp;
				string str_tmp;
				//Receive welcome message
				temp = new char[MAX];
				MsgSize=Client.Receive((char*)temp, MAX, 0);
				temp[MsgSize + 1] = '\0';
				cout << "Server: " << temp << endl;


				cout << "- Input Username: ";
				cin.getline(temp, 24);
				str_tmp = "USER " + string(temp);
		
				Client.Send(str_tmp.c_str(), str_tmp.length() + 1, 0);
				//Receive message
				temp = new char[MAX];
				MsgSize = Client.Receive((char*)temp, MsgSize, 0);

				// In thong diep ra
				temp[MsgSize] = '\0';
				cout << "Server: " << temp << endl;

				cout << "Input password: ";
				cin.getline(temp, 24);
				str_tmp = "PASS " + string(temp);

				Client.Send(str_tmp.c_str(), str_tmp.length() + 1, 0);

				//Receive message
				temp = new char[MAX];
				MsgSize = Client.Receive((char*)temp, MsgSize, 0);
				temp[MsgSize] = '\0';
				cout << temp;

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
