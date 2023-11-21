#include "Application.h"

std::string Application::dir = "";
Quiz Application::workingQuiz = Quiz();

void Application::Start() {
    dir = "";
    Console::Reset();
    Console::Clear();

    Console::SetColor(Console::CYAN);
    std::string title = " Quiz Maker v" + std::string(VERSION) + " ";
    Console::Print(title + "\n");
    Console::Reset();
    for (int i = 0; i < title.length(); i++) {
        Console::Print("~");
    };
    Console::Print("\n\nEnter 'help' for a list of commands.\n\n");

    PollCommand();
}

void Application::PollCommand() {
    const int color = Console::GetColor();
    Console::SetColor(Console::BLUE);
    Console::Print(dir + "> ");
    RunCommand(Command::Parse(Console::Input()));
    Console::SetColor(color);
}

void Application::RunCommand(Command command) {
    Console::Reset();

    if (!CommandHandler::Verify(command)) {
        Err(CommandHandler::GetErr(), false);
        PollCommand();
        return;
    }

    CommandHandler::Run(command);
}

void Application::SuccessMsg(std::string msg) {
    Console::SetColor(Console::GREEN);
    Console::Print(msg);
    Console::Reset();
}

void Application::Help() {
    Console::SetColor(Console::GREEN);
    Console::Print("COMMANDS:\n");
    Console::Print("q / quit   : quit program\n");
    Console::Print("q! / quit! : force quit program\n");
    Console::Print("root       : go to root directory\n");
    Console::Print("help       : display this help message\n");
    Console::Print("docs       : open documentation in browser");
    Console::Print("create     : create new quiz\n");
    Console::Print("rename     : rename quiz\n");
    Console::Print("addq       : add question\n");
    Console::Print("take       : take quiz\n");
    Console::Print("clr        : clear screen\n");
    Console::Print("save       : save quiz to path\n");
    Console::Print("load       : load quiz from path\n");
    Console::Print("\n");
    Console::Reset();
    PollCommand();
}

void Application::HelpMore() {
    Console::SetColor(Console::GREEN);
    Console::Print("(may have to expand window to see table correctly)\n");
    Console::Print("-------------------------------------------------------------------------------------------------------------------------------\n");
    Console::Print("|     COMMAND     |          EXPLANATION          |     ARGUMENTS    |             ARGS EXPLANATION             |  DIRECTORY  |\n");
    Console::Print("|-----------------------------------------------------------------------------------------------------------------------------|\n");
    Console::Print("|     q / quit    |         quit program          |       none       |                   N/A                    |     any     |\n");
    Console::Print("|    q! / quit!   |       force quit program      |       none       |                   N/A                    |     any     |\n");
    Console::Print("|      root       |      go to root directory     |       none       |                   N/A                    |     any     |\n");
    Console::Print("|      help       |      display help message     |       -more      |       more detailed help msg (this)      |     any     |\n");
    Console::Print("|      docs       | open documentation in browser |       none       |                   N/A                    |     any     |\n");
    Console::Print("|     create      |        create new quiz        |       none       |                   N/A                    |     Root    |\n");
    Console::Print("|     rename      |          rename quiz          |       none       |                   N/A                    |     Quiz    |\n");
    Console::Print("|      addq       |          add question         |   -mc, -wr, -tf  |   multiple choice, written, true/false   |     Quiz    |\n");
    Console::Print("|      take       |           take quiz           |  -autosect, -clr |   auto make quiz sections, clear screen  |     Quiz    |\n");
    Console::Print("|      clr        |          clear screen         |       none       |                   N/A                    |     Root    |\n");
    Console::Print("|      save       |       save quiz to path       |       none       |                   N/A                    |     Quiz    |\n");
    Console::Print("|      load       |      load quiz from path      |       none       |                   N/A                    |     Root    |\n");
    Console::Print("|                 |                               |                  |                                          |             |\n");
    Console::Print("-------------------------------------------------------------------------------------------------------------------------------\n");
    Console::Print("Use 'docs' to see full documentation.\n");
    Console::Reset();
    PollCommand();
}

void Application::Docs() {
    Util::OpenLink("https://github.com/jopo86/QuizMaker/wiki/Documentation");
    SuccessMsg("Attempted to open link in browser. If it doesn't open, use this link:\n");
    Console::SetColor(Console::CYAN);
    Console::Print("https://github.com/jopo86/QuizMaker/wiki/Documentation\n\n");
    Console::Reset();
    PollCommand();
}

void Application::CreateQuiz() {
    dir = "Quiz";
    Console::Reset();
    Console::Print("Enter quiz name: ");
    workingQuiz = Quiz(Console::Input());
    SuccessMsg("Created empty quiz '" + workingQuiz.getName() + "'.\n\n");
    PollCommand();
}

void Application::RenameQuiz() {
    Console::Print("Enter new quiz name:\n");
    std::string name = Console::Input();
    workingQuiz.setName(name);
    SuccessMsg("Quiz name set to '" + name + "'.\n\n");
    PollCommand();
}

void Application::AddQuestion() {
    Console::Reset();
    Console::Reset();
    Console::Print("Enter Question type ('mc' for multiple choice, 'wr' for written, 'tf' for true/false):\n");
    std::string type = Console::Input();
    if (Util::EqualsIgnoreCase(type, "mc")) {
        AddQuestionMC();
    }
    else if (Util::EqualsIgnoreCase(type, "wr")) {
        AddQuestionWR();
    }
    else if (Util::EqualsIgnoreCase(type, "tf")) {
        AddQuestionTF();
    }
    else {
        Err("unrecognized response: '" + type + "', question creation aborted", false);
    }
}

void Application::AddQuestionMC() {
    Question mcq(Question::MULTIPLE_CHOICE);
    Console::Print("Enter Question: \n");
    mcq.setQuestion(Console::Input());
    Console::Print("Enter choices (enter '-' when finished):\n");
    std::string choice;
    while (choice != "-") {
        choice = Console::Input();
        if (choice != "-") {
            mcq.addChoice(choice);
        }
    }
    Console::Print("Enter correct choice:\n");
    std::string ans = Console::Input();
    if (!mcq.isChoice(ans)) {
        Err("answer '" + ans + "' not found in choices, question creation aborted", false);
        dir = "Quiz";
        return;
    }
    mcq.setAnswer(ans);
    workingQuiz.addQuestion(mcq);
    SuccessMsg("Question created.\n\n");
    PollCommand();
}

void Application::AddQuestionWR() {
    Question wq(Question::WRITTEN);
    Console::Print("Enter Question: \n");
    wq.setQuestion(Console::Input());
    Console::Print("Enter answer:\n");
    wq.setAnswer(Console::Input());
    workingQuiz.addQuestion(wq);
    SuccessMsg("Question created.\n\n");
    PollCommand();
}

void Application::AddQuestionTF() {
    Question tfq(Question::TRUE_FALSE);
    Console::Print("Enter Question: \n");
    tfq.setQuestion(Console::Input());
    Console::Print("Enter answer (T/F): ");
    const char ans = Util::ToLower(Console::Input()[0]);
    if (!(ans == 't' || ans == 'f')) {
        Err("response must start with T/t or F/f, question creation aborted", false);
        return;
    }
    tfq.setAnswer({ ans });
    workingQuiz.addQuestion(tfq);
    SuccessMsg("Question created.\n\n");
    PollCommand();
}

void Application::TakeQuiz(bool autosect) {
    // TODO: handle autosect arg

    std::string header = " TAKING QUIZ: '" + workingQuiz.getName() + "' ";
    Console::SetColor(Console::BLUE);
    Console::Print("\n" + header + "\n");
    Console::Reset();
    for (int i = 0; i < header.length(); i++) {
        Console::Print("-");
    }
    Console::Print("\n\n");

    int qNum = 1;
    int score = 0;
    int maxScore = workingQuiz.getQuestions().size();

    for (int i = 0; i < workingQuiz.getQuestions().size(); i++) {
        Question q = workingQuiz.getQuestions()[i];
        Console::Print("- QUESTION " + std::to_string(qNum) + " -\n");
        Console::SetColor(Console::CYAN);
        Console::Print(q.getQuestion() + "\n\n");
        Console::Reset();
        if (q.getType() == Question::WRITTEN) {
            Console::Print("Enter answer: ");
            std::string answer = Console::Input();
            if (q.check(answer)) {
                Console::SetColor(Console::GREEN);
                Console::Print("Correct!\n\n");
                Console::Reset();
                score++;
            }
            else {
                Console::SetColor(Console::RED);
                Console::Print("Incorrect!\n\n");
                Console::Reset();
            }
        }

        else if (q.getType() == Question::MULTIPLE_CHOICE) {
            Console::Print("Choices:\n");
            Console::SetColor(Console::CYAN);
            for (int j = 0; j < q.getChoices().size(); j++) {
                Console::Print(std::string(1, Util::NumToLetter(j)) + ") " + q.getChoices()[j] + "\n");
            }
            Console::Reset();
            Console::Print("Enter (letter) choice: ");
            char letterChoice = Console::Input()[0];
            if (q.check(q.getChoices()[Util::LetterToNum(letterChoice)])) {
                Console::SetColor(Console::GREEN);
                Console::Print("Correct!\n\n");
                Console::Reset();
                score++;
            }
            else {
                Console::SetColor(Console::RED);
                Console::Print("Incorrect!\n\n");
                Console::Reset();
            }
        }

        else if (q.getType() == Question::TRUE_FALSE) {
            Console::Print("Enter answer (T/F): ");
            char ans = Util::ToLower(Console::Input()[0]);
            if (q.check({ ans })) {
                Console::SetColor(Console::GREEN);
                Console::Print("Correct!\n\n");
                Console::Reset();
                score++;
            }
            else {
                Console::SetColor(Console::RED);
                Console::Print("Incorrect!\n\n");
                Console::Reset();
            }
        }
        qNum++;
    }

    SuccessMsg("Quiz Finsihed. Score: " + std::to_string(score) + "/" + std::to_string(maxScore) + " (" + std::to_string((int)((float)score / maxScore * 100)) + "%)" + "\n\n");
    PollCommand();
}

void Application::SaveQuiz() {
    Console::Print("Enter path to save quiz to (relative to location of QuizMaker.exe, or absolute):\n");
    std::string path = Console::Input();
    QMS::Save(workingQuiz, path);
    SuccessMsg("Quiz saved to '" + path + "'.\n\n");
    PollCommand();
}

void Application::LoadQuiz() {
    Console::Print("Enter path to load quiz from (relative to location of QuizMaker.exe, or absolute):\n");
    std::string path = Console::Input();
    if (Util::ReadFile(path) == Util::FILE_NOT_FOUND_ERROR) {
        Err("path '" + path + "' not found, quiz loading aborted", false);
        return;
    }
    else {
        workingQuiz = QMS::Load(path);
        dir = "Quiz";
    }
    SuccessMsg("Quiz loaded from '" + path + "'.\n\n");
    PollCommand();
}

void Application::Root() {
    Console::Print("Are you sure you want to go back to root directory? Progress may be lost. (y/n)\n");
    std::string response = Console::Input();
    Console::Print("\n");
    if (response == "y") {
        workingQuiz = Quiz();
        dir = "";
        PollCommand();
    }
    else if (response == "n") {
        Console::Print("\n");
        PollCommand();
    }
    else {
        Err("unhandled response '" + response + "'\n\n", false);
        PollCommand();
    }
}

void Application::Clr() {
    Console::Clear();
    PollCommand();
}

void Application::Err(std::string msg, bool terminate) {
    Console::SetColor(Console::RED);
    Console::Print("ERROR: " + msg + "\n\n");
    Console::Reset();
    if (terminate) exit(1);
}

void Application::Quit() {
    Console::Reset();
    Console::Print("Are you sure you want to quit? Progress may be lost. (y/n)\n");
    std::string response = Console::Input();
    if (response == "y") {
        ForceQuit();
    }
    else if (response == "n") {
        Console::Print("\n");
        PollCommand();
    }
    else {
        Err("unhandled response '" + response + "'\n\n", false);
        PollCommand();
    }
}

void Application::ForceQuit() {
    return;
}

std::string Application::GetDir() {
    return dir;
}