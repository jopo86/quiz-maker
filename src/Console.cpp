#include "Console.h"

#ifdef _WIN32
void Console::Clear() {
	system("CLS");
}

void Console::SetColor(int color)
{
	if (color == -1) {
		Reset();
		return;
	}
	SetConsoleTextAttribute(hConsole, color);
	currentColor = color;
}

void Console::Reset() {
	SetConsoleTextAttribute(hConsole, WHITE);
	std::cout << "\033[0m";
}
#else
void Console::Clear() {
	system("clear");
}
void Console::SetColor(int color)
{
	if (color == -1) {
		Reset();
		return;
	}
	std::cout << "\033[" << color << ";1m";
	currentColor = color;
}

void Console::Reset() {
	std::cout << "\033[0m";
}
#endif

int Console::GetColor() {
	return currentColor;
}

void Console::SetItalic() {
	std::cout << "\033[3m";
}

void Console::SetUnderlined() {
	std::cout << "\033[4m";
}