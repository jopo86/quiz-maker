#include "CommandHandler.h"

const std::vector<std::string> CommandHandler::validCommands = {
    "quit!",
    "q!",
    "quit",
    "q",
    "help",
    "create",
    "name",
    "addq",
    "take"
};

const std::map<std::string, std::vector<std::string>> CommandHandler::validArgs = {
    { "quit!", { "" } },
    { "q!", { "" } },
    { "quit", { "" } },
    { "q", { "" } },
    { "help", { "more" } },
    { "create", { "" } },
    { "name", { "" } },
    { "addq", { "mc", "wr", "tf" } },
    { "take", { "autosect" } }
};

std::string CommandHandler::err = "";

bool CommandHandler::Verify(Command command) {
    std::string cmd = command.getCmd();
    std::vector<std::string> args = command.getArgs();


    // check if command exists
    bool exists = false;

    for (int i = 0; i < validCommands.size(); i++) {
        if (cmd == validCommands[i]) {
            exists = true;
        }
    }

    if (!exists) {
        err = "unrecognized command '" + cmd + "'\nUse 'help' to get a list of commands.";
        return false;
    }

    // check if command has valid args
    std::vector<bool> valid(args.size(), false);

    for (int i = 0; i < args.size(); i++) {
        for (int j = 0; j < validArgs.size(); j++) {
            if (args[i] == validArgs.at(cmd)[j]) {
                valid[i] = true;
            }
        }
    }

    bool allArgsValid = true;
    err = "unrecognized argument(s): ";
    for (int i = 0; i < args.size(); i++) {
        if (!valid[i]) {
            allArgsValid = false;
            err += "'" + args[i] + "' ";
        }
    }
    err += "for command '" + cmd + "'\nUse 'help -more' to get a list of commands with their arguments.";

    if (!allArgsValid) return false;

    err = "";
    return true;
}

void CommandHandler::Run(Command command) {
    std::string dir = Application::GetDir();
    std::string cmd = command.getCmd();
    std::vector<std::string> args = command.getArgs();

    if (cmd == "quit!" || cmd =="q!") {
        Application::ForceQuit();
    }
    else if (cmd == "quit" || cmd == "q") {
        Application::Quit();
    }
    else if (cmd == "help") {
        Application::Help();
    } 
    else if (cmd == "create") {
        if (dir == "") {
            Application::CreateQuiz();
        }
        else {
            Application::Err("'create' can only be called from root directory.", false);
            Application::PollCommand();
            return;
        }
    }
    else if (cmd == "name") {
        if (dir == "Quiz ") {
            Application::NameQuiz();
        }
        else {
            Application::Err("'name' can only be called from within Quiz directory", false);
            Application::PollCommand();
            return;
        
        }
    }
    else if (cmd == "addq") {
        if (dir == "Quiz ") {
            Application::AddQuestion();
        }
        else {
            Application::Err("'addq' can only be called from within Quiz directory", false);
            Application::PollCommand();
            return;
        }
    }
    else if (cmd == "take") {
        if (dir == "Quiz ") {
            // Application::QuizTaker::Take(workingQuiz);
            Application::PollCommand();
        }
        else {
            Application::Err("'take' can only be called from within Quiz directory", false);
            Application::PollCommand();
            return;
        }
    }
    else {
        Application::Err("unrecognized command '" + cmd + "'", false);
        Application::PollCommand();
    }

    // TODO: cover directory errors in Verify(), not here
}

std::string CommandHandler::GetErr() {
    return err;
}