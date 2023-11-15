#pragma once

#include <iostream>
#include <string>
#include <vector>

class Command {
private:
    const std::string cmd;
    const std::vector<std::string> args;

public:
    Command();
    Command(std::string cmd);
    Command(std::string cmd, std::vector<std::string> args);

    bool hasArg(std::string arg);

    static Command Parse(std::string str);

    std::string getCmd();
    std::vector<std::string> getArgs();
};