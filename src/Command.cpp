#include "Command.h"

Command::Command() : cmd(""), args({}) {}

Command::Command(std::string cmd) : cmd(cmd), args({}) {}

Command::Command(std::string cmd, std::vector<std::string> args) : cmd(cmd), args(args) {}

bool Command::hasArg(std::string arg) {
    for (int i = 0; i < args.size(); i++) {
        if (args[i] == arg) return true;
    }
    return false;
}

Command Command::Parse(std::string str) {
    std::string cmd = "";
    std::vector<std::string> args = {};

    int argIndex = -1;

    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (c == ' ') continue;
        if (c == '-') {
            args.push_back("");
            argIndex++;
            continue;
        }
        
        if (argIndex == -1) cmd.append({c});
        else {
            args[argIndex].append({c});
        }
    }

    return Command(cmd, args);
}

std::string Command::getCmd() {
    return cmd;
}

std::vector<std::string> Command::getArgs() {
    return args;
}