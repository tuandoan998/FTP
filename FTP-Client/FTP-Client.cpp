// FTP-Client.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include "FTP-Client.h"
#include <afxsock.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#define MAX_LENGTH 500
#endif


#define _CRT_SECURE_NO_WARNINGS

// The one and only application object

CWinApp theApp;



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
			
			int	dataPort = 0;
			CSocket Client;
			CSocket dataClient;
			Client.Create(0, SOCK_STREAM, NULL);//auto choose client port, TCP type,  CAsyncSocket instance should listen for client activity on all network interfaces.
			dataClient.Create(0, SOCK_STREAM, NULL); 
			// Ket noi den Server
			if (Client.Connect(_T("127.0.0.1"), 21) != 0)
			{
				
				cout << "Ket noi toi Server thanh cong !!!" << endl << endl;
				CString addr;

				char ClientMsg[MAX_LENGTH];
				char *temp;
				string str_tmp;

				//Receive welcome message
				temp = new char[MAX_LENGTH + 1];
				Client.Receive((char*)temp, MAX_LENGTH, 0);
				DisplayMessage(temp);
				
				cout << "username: ";
				cin.getline(temp, 24);
				str_tmp = "USER " + string(temp);
				Client.Send(str_tmp.c_str(), str_tmp.length() + 1, 0);
				temp = new char[MAX_LENGTH + 1];
				Client.Receive((char*)temp, MAX_LENGTH, 0);
				DisplayMessage(temp);

				cout << "password: ";
				cin.getline(temp, 24);
				str_tmp = "PASS " + string(temp);
				Client.Send(str_tmp.c_str(), str_tmp.length() + 1, 0);
				temp = new char[MAX_LENGTH + 1];
				Client.Receive((char*)temp, MAX_LENGTH, 0);
				DisplayMessage(temp);

				
				//PASV mode establish
				str_tmp = "pasv";
				Client.Send(str_tmp.c_str(), str_tmp.length() + 1, 0);
				temp = new char[MAX_LENGTH + 1];
				Client.Receive((char*)temp, MAX_LENGTH, 0);
				DisplayMessage(temp);
				dataPort = getDataPort(temp);
				dataClient.Connect(_T("127.0.0.1"), dataPort);
				

				//ls
				str_tmp = "NLST\r\n";
				Client.Send(str_tmp.c_str(), str_tmp.length() + 1, 0);
				temp = new char[MAX_LENGTH + 1];
				Client.Receive((char*)temp, MAX_LENGTH, 0);
				DisplayMessage(temp);
				temp = new char[MAX_LENGTH + 1];
				dataClient.Receive((char*)temp, MAX_LENGTH, 0);
				DisplayMessage(temp);

				//pwd
				str_tmp = "PWD";
				Client.Send(str_tmp.c_str(), str_tmp.length() + 1, 0);
				temp = new char[MAX_LENGTH + 1];
				Client.Receive((char*)temp, MAX_LENGTH, 0);
				DisplayMessage(temp);

				//quit
				str_tmp = "QUIT";
				Client.Send(str_tmp.c_str(), str_tmp.length() + 1, 0);
				temp = new char[MAX_LENGTH + 1];
				Client.Receive((char*)temp, MAX_LENGTH, 0);
				DisplayMessage(temp);
				Sleep(5000);		// Dung lai de xem thoi
				Client.Close();
				dataClient.Close();

				/*while (1) {
					temp = new char[MAX_LENGTH + 1];
					Client.Receive((char*)temp, MAX_LENGTH, 0);
					DisplayMessage(temp);
				}*/
				
				//do
				//{
				//	//code here
				//	cout << "ftp > ";
				//	getline(cin, str_tmp);

				//	str_tmp = getCommand(str_tmp);

				//	Client.Send(str_tmp.c_str(), str_tmp.length() + 1, 0);
				//	temp = new char[MAX_LENGTH + 1];
				//	Client.Receive((char*)temp, MAX_LENGTH, 0);
				//	DisplayMessage(temp);

				//	
				//} while (str_tmp.compare("bye")!=0);
			}
			else
			{
				cout << "Khong the ket noi den Server !!!" << endl;
			}
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
