#include <iostream>
#include "Console.h"

using namespace Console;

int main()
{
	/*Console::SetColor(1);
	std::cout << "Red text\n";
	Console::SetColor(2);
	std::cout << "Green text\n";
	Console::SetColor(3);
	std::cout << "Yellow text\n";
	Console::SetColor(4);
	std::cout << "Blue text\n";
	Console::SetColor(5);
	std::cout << "Magenta text\n";
	Console::SetColor(6);
	std::cout << "Cyan text\n";
	Console::SetColor(Console::WHITE);
	std::cout << "White text\n";*/

	for (int i = 0; i < 16; i++)
	{
		Console::SetColor(i);
		std::cout << "Color " << i << "\n";
	}

	return 0;
}