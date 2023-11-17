#pragma once

#include <string>
#include <vector>
#include <map>

#include "Application.h"
#include "Util.h"
#include "Command.h"

class CommandHandler {
private:
    static const std::vector<std::string> DIR_ANY;
    static const std::vector<std::string> DIR_ROOT;
    static const std::vector<std::string> DIR_QUIZ;
    static const std::vector<std::string> DIR_QUESTION;
    static const std::vector<std::string> DIR_CHOICES;
    static const std::vector<std::string> DIR_ANSWER;

    static const std::vector<std::string> VALID_COMMANDS;
    static const std::map<std::string, std::vector<std::string>> VALID_ARGS;
    static const std::map<std::string, std::vector<std::string>> VALID_DIRS;

    static std::string err;

public:

    static bool Verify(Command command);

    static void Run(Command command);
    
    static std::string GetErr();
};