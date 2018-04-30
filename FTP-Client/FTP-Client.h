#pragma once

#include "resource.h"

void DisplayMessage(char*str)
{
	int i = strlen(str) - 1;
	for (; str[i] != '\n' && i >= 0; i--)
		;
	if (i > 0)
		str[i + 1] = 0;
	std::cout << str;
}
