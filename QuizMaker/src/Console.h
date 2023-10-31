#pragma once
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace Console
{
#ifdef _WIN32
	static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	static int RED = 12;
	static int GREEN = 10;
	static int YELLOW = 6;
	static int BLUE = 3;
	static int MAGENTA = 13;
	static int CYAN = 11;
	static int WHITE = 7;

#else
	static int RED = 31;
	static int GREEN = 32;
	static int YELLOW = 33;
	static int BLUE = 34;
	static int MAGENTA = 35;
	static int CYAN = 36;
	static int WHITE = 37;
#endif

	void Clear();
	void SetColor(int color);
	void SetItalic();
	void SetUnderlined();
	void Reset();
};