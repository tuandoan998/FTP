#pragma once

#include "resource.h"
#include <string>
using namespace std;

const char CMD_STR_MGET[]	= "mget";
const char CMD_STR_CD[]		= "cd";
const char CMD_STR_LCD[]	= "lcd";
const char CMD_STR_DEL[]	= "delete";
const char CMD_STR_MDEL[]	= "mdelete";
enum cmd
{
	/*
	6.Download many files(mget) :
	7.Change path in server(cd) :
		"cwd director"

	8.Change path in client(lcd) :
	9.Delete a file in server(delete) :
	10.Delete many files in server(mdelete) :
	*/
	CMD_EN_MGET, 
	CMD_EN_CD,
	CMD_EN_LCD, 
	CMD_EN_DEL, 
	CMD_EN_MDEL
};

int getCmdCode(const string strCmd)
{
	if (strCmd.compare(CMD_STR_CD))
		return CMD_EN_CD;
	if (strCmd.compare(CMD_STR_DEL))
		return CMD_EN_DEL;
	if (strCmd.compare(CMD_STR_LCD))
		return CMD_EN_LCD;
	if (strCmd.compare(CMD_STR_MDEL))
		return CMD_EN_MDEL;
	if (strCmd.compare(CMD_STR_MGET))
		return CMD_EN_MGET;
	return -1;
}

void DisplayMessage(char*str)
{
	int i = strlen(str) - 1;
	for (; str[i] != '\n' && i >= 0; i--)
		;
	if (i > 0)
		str[i + 1] = 0;
	std::cout << str;
}


string getCommand(const string strCMD)
{
	int space_pos = strCMD.find_first_of(32);
	if (space_pos == string::npos)
	{
		space_pos = strCMD.length();
	}

	string orgCMD = strCMD.substr(0, space_pos);

	if (orgCMD.compare("cd") == 0)
		orgCMD = "CWD";

	orgCMD += strCMD.substr(space_pos, strCMD.length());

	return orgCMD;
}
