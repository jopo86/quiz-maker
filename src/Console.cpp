#include "Console.h"

using namespace Console;

#ifdef _WIN32
void Console::Clear() {
	system("CLS");
}

void Console::SetColor(int color)
{
	SetConsoleTextAttribute(hConsole, color);
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
	std::cout << "\033[" << color << ";1m";
}

void Console::Reset() {
	std::cout << "\033[0m";
}
#endif


void Console::SetItalic() {
	std::cout << "\033[3m";
}

void Console::SetUnderlined() {
	std::cout << "\033[4m";
}