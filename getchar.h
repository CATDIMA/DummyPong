#ifndef _MYGETCHAR_H
#define _MYGETCHAR_H

#include <Windows.h>

/*
return values:
1. A-Za-z symbol
2. \r when backspace was pressed
3. \n when enter was pressed
*/
static char myGetChar()
{
	bool isUpper = false;
	char ch = '\0';

	/*check enter*/
	if (GetAsyncKeyState(VK_RETURN) & 1)
	{
		ch = '\n';
		return ch;
	}

	/*check backspace*/
	if (GetAsyncKeyState(VK_BACK) & 1)
	{
		ch = '\r';
		return ch;
	}

	/*check shift*/
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
	{
		isUpper = true;
	}
	else
	{
		isUpper = false;
	}

	if (GetAsyncKeyState(0x41) & 1) /*A*/
	{
		if (isUpper)
		{
			ch = 'A';
		}
		else
		{
			ch = 'a';
		}
	}
	if (GetAsyncKeyState(0x42) & 1) /*B*/
	{
		if (isUpper)
		{
			ch = 'B';
		}
		else
		{
			ch = 'b';
		}
	}
	if (GetAsyncKeyState(0x43) & 1) /*C*/
	{
		if (isUpper)
		{
			ch = 'C';
		}
		else
		{
			ch = 'c';
		}
	}
	if (GetAsyncKeyState(0x44) & 1) /*D*/
	{
		if (isUpper)
		{
			ch = 'D';
		}
		else
		{
			ch = 'd';
		}
	}
	if (GetAsyncKeyState(0x45) & 1) /*E*/
	{
		if (isUpper)
		{
			ch = 'E';
		}
		else
		{
			ch = 'e';
		}
	}
	if (GetAsyncKeyState(0x46) & 1) /*F*/
	{
		if (isUpper)
		{
			ch = 'F';
		}
		else
		{
			ch = 'f';
		}
	}
	if (GetAsyncKeyState(0x47) & 1) /*G*/
	{
		if (isUpper)
		{
			ch = 'G';
		}
		else
		{
			ch = 'g';
		}
	}
	if (GetAsyncKeyState(0x48) & 1) /*H*/
	{
		if (isUpper)
		{
			ch = 'H';
		}
		else
		{
			ch = 'h';
		}
	}
	if (GetAsyncKeyState(0x49) & 1) /*I*/
	{
		if (isUpper)
		{
			ch = 'I';
		}
		else
		{
			ch = 'i';
		}
	}
	if (GetAsyncKeyState(0x4A) & 1) /*J*/
	{
		if (isUpper)
		{
			ch = 'J';
		}
		else
		{
			ch = 'j';
		}
	}
	if (GetAsyncKeyState(0x4B) & 1) /*K*/
	{
		if (isUpper)
		{
			ch = 'K';
		}
		else
		{
			ch = 'k';
		}
	}
	if (GetAsyncKeyState(0x4C) & 1) /*L*/
	{
		if (isUpper)
		{
			ch = 'L';
		}
		else
		{
			ch = 'l';
		}
	}
	if (GetAsyncKeyState(0x4D) & 1) /*M*/
	{
		if (isUpper)
		{
			ch = 'M';
		}
		else
		{
			ch = 'm';
		}
	}
	if (GetAsyncKeyState(0x4E) & 1) /*N*/
	{
		if (isUpper)
		{
			ch = 'N';
		}
		else
		{
			ch = 'n';
		}
	}
	if (GetAsyncKeyState(0x4F) & 1) /*O*/
	{
		if (isUpper)
		{
			ch = 'O';
		}
		else
		{
			ch = 'o';
		}
	}
	if (GetAsyncKeyState(0x50) & 1) /*P*/
	{
		if (isUpper)
		{
			ch = 'P';
		}
		else
		{
			ch = 'p';
		}
	}
	if (GetAsyncKeyState(0x51) & 1) /*Q*/
	{
		if (isUpper)
		{
			ch = 'Q';
		}
		else
		{
			ch = 'q';
		}
	}
	if (GetAsyncKeyState(0x52) & 1) /*R*/
	{
		if (isUpper)
		{
			ch = 'R';
		}
		else
		{
			ch = 'r';
		}
	}
	if (GetAsyncKeyState(0x53) & 1) /*S*/
	{
		if (isUpper)
		{
			ch = 'S';
		}
		else
		{
			ch = 's';
		}
	}
	if (GetAsyncKeyState(0x54) & 1) /*T*/
	{
		if (isUpper)
		{
			ch = 'T';
		}
		else
		{
			ch = 't';
		}
	}
	if (GetAsyncKeyState(0x55) & 1) /*U*/
	{
		if (isUpper)
		{
			ch = 'U';
		}
		else
		{
			ch = 'u';
		}
	}
	if (GetAsyncKeyState(0x56) & 1) /*V*/
	{
		if (isUpper)
		{
			ch = 'V';
		}
		else
		{
			ch = 'v';
		}
	}
	if (GetAsyncKeyState(0x57) & 1) /*W*/
	{
		if (isUpper)
		{
			ch = 'W';
		}
		else
		{
			ch = 'w';
		}
	}
	if (GetAsyncKeyState(0x58) & 1) /*X*/
	{
		if (isUpper)
		{
			ch = 'X';
		}
		else
		{
			ch = 'x';
		}
	}
	if (GetAsyncKeyState(0x59) & 1) /*Y*/
	{
		if (isUpper)
		{
			ch = 'Y';
		}
		else
		{
			ch = 'y';
		}
	}
	if (GetAsyncKeyState(0x5A) & 1) /*Z*/
	{
		if (isUpper)
		{
			ch = 'Z';
		}
		else
		{
			ch = 'z';
		}
	}
	if (GetAsyncKeyState(0x30) & 1) /*0*/
	{
		ch = '0';
	}
	if (GetAsyncKeyState(0x31) & 1) /*1*/
	{
		ch = '1';
	}
	if (GetAsyncKeyState(0x32) & 1) /*2*/
	{
		ch = '2';
	}
	if (GetAsyncKeyState(0x33) & 1) /*3*/
	{
		ch = '3';
	}
	if (GetAsyncKeyState(0x34) & 1) /*4*/
	{
		ch = '4';
	}
	if (GetAsyncKeyState(0x35) & 1) /*5*/
	{
		ch = '5';
	}
	if (GetAsyncKeyState(0x36) & 1) /*6*/
	{
		ch = '6';
	}
	if (GetAsyncKeyState(0x37) & 1) /*7*/
	{
		ch = '7';
	}
	if (GetAsyncKeyState(0x38) & 1) /*8*/
	{
		ch = '8';
	}
	if (GetAsyncKeyState(0x39) & 1) /*9*/
	{
		ch = '9';
	}
	if (GetAsyncKeyState(VK_OEM_MINUS) & 1) /*_*/
	{
		if (isUpper)
		{
			ch = '_';
		}
		else
		{
			ch = '-';
		}
	}

	return ch;
}

#endif