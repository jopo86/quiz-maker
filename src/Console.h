#pragma once
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Console
{
#ifdef _WIN32
	static const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	static const int WHITE = 7;
	static const int RED = 12;
	static const int YELLOW = 6;
	static const int GREEN = 10;
	static const int CYAN = 11;
	static const int BLUE = 3;
	static const int MAGENTA = 13;

#else
	static const int WHITE = 37;
	static const int RED = 31;
	static const int YELLOW = 33;
	static const int GREEN = 32;
	static const int CYAN = 36;
	static const int BLUE = 34;
	static const int MAGENTA = 35;
#endif

	static int currentColor = -1;

	void Clear();
	void Print(std::string msg);
	std::string Input();
	void SetColor(int color);
	int GetColor();
	void SetItalic();
	void SetUnderlined();
	void Reset();
};