#pragma once

#include <string>
#include <vector>
#include <map>

#include "Application.h"
#include "Console.h"
#include "Command.h"

class CommandHandler {
private:
    static const std::vector<std::string> validCommands;
    static const std::map<std::string, std::vector<std::string>> validArgs;

    static std::string err;

public:

    static bool Verify(Command command);

    static void Run(Command command);
    
    static std::string GetErr();
};