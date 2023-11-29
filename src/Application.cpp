#include "Application.h"

std::string Application::dir = "";
Quiz Application::workingQuiz = Quiz();
std::string Application::workingPath = "";
std::string Application::lastCommand = "";

std::string Application::GetVersionStr() {
    return std::to_string((int)VERSION / 100) + "." + std::to_string((int)VERSION % 100 / 10) + "." + std::to_string((int)VERSION % 100 % 10);
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
        Err(CommandHandler::GetErr() + "\n\n", false);
        PollCommand();
        return;
    }

    if (!Util::EqualsIgnoreCase(command.getCmd(), "q") && !Util::EqualsIgnoreCase(command.getCmd(), "clr")) lastCommand = command.getCmd();
    CommandHandler::Run(command);
}

void Application::SuccessMsg(std::string msg) {
    Console::SetColor(Console::GREEN);
    Console::Print(msg);
    Console::Reset();
}

std::string Application::VerifyQuestionNumInput(std::string inp) {
    if (!Util::IsNumber(inp)) {
        return "response must be a number.";
    }
    int num = std::stoi(inp);
    size_t size = workingQuiz.getQuestions().size();
    if (num > size) {
        return "too large, quiz only has " + std::to_string(size) + " questions.";
    }

    return "";
}

void Application::Start() {
    dir = "";
    Console::Clear();
    Console::SetColor(Console::CYAN);
    std::string title = "          Quiz Maker v" + GetVersionStr() + "          ";
    std::string bar;
    for (int i = 0; i < title.length(); i++) {
        bar += "=";
    };
    Console::Print(bar + "\n");
    Console::Print(title + "\n");
    Console::Print(bar);
    Console::Reset();
    Console::Print("\n\nEnter 'help' for a list of commands.\nEnter 'docs' for full documentation.\nEnter 'tut' for the tutorial.\n\n");

    PollCommand();
}

void Application::Help() {
    Console::SetColor(Console::GREEN);
    Console::Print("COMMANDS:\n");
    Console::Print("q / quit    : quit program\n");
    Console::Print("q! / quit!  : force quit program\n");
    Console::Print("v / version : show app version\n");
    Console::Print("root        : go to root directory\n");
    Console::Print("help        : display this help message\n");
    Console::Print("docs        : open documentation in browser\n");
    Console::Print("tut         : open tutorial in browser\n");
    Console::Print("create      : create new quiz\n");
    Console::Print("sca         : show correct answer setting\n");
    Console::Print("rename      : rename quiz\n");
    Console::Print("addq        : add question\n");
    Console::Print("insq        : insert question at #\n");
    Console::Print("listq       : list all questions\n");
    Console::Print("editq       : edit a question\n");
    Console::Print("delq        : delete a question\n");
    Console::Print("swapq       : swaps 2 questions\n");
    Console::Print("take        : take quiz\n");
    Console::Print("clr         : clear screen\n");
    Console::Print("save        : save quiz to path\n");
    Console::Print("load        : load quiz from path\n");
    Console::Print("\nUse 'help -more' for more detail\n\n");
    Console::Reset();
    PollCommand();
}

void Application::HelpMore() {
    Console::SetColor(Console::GREEN);
    Console::Print("(may have to expand window to see table correctly)\n");
    Console::Print("-------------------------------------------------------------------------------------------------------------------------------\n");
    Console::Print("|     COMMAND     |          EXPLANATION          |     ARGUMENTS    |             ARGS EXPLANATION             |  DIRECTORY  |\n");
    Console::Print("|-----------------------------------------------------------------------------------------------------------------------------|\n");
    Console::Print("|     q / quit    |         quit program          |         -        |                    -                     |     any     |\n");
    Console::Print("|    q! / quit!   |       force quit program      |         -        |                    -                     |     any     |\n");
    Console::Print("|   v / version   |        show app version       |         -        |                    -                     |     any     |\n");
    Console::Print("|      root       |      go to root directory     |         -        |                    -                     |     any     |\n");
    Console::Print("|      help       |      display help message     |       -more      |       more detailed help msg (this)      |     any     |\n");
    Console::Print("|      docs       | open documentation in browser |         -        |                    -                     |     any     |\n");
    Console::Print("|       tut       |   open tutorial in browser    |         -        |                    -                     |     any     |\n");
    Console::Print("|     create      |        create new quiz        |         -        |                    -                     |     Root    |\n");
    Console::Print("|       sca       |  show correct answer setting  |         -        |                    -                     |     Quiz    |\n");
    Console::Print("|     rename      |          rename quiz          |         -        |                    -                     |     Quiz    |\n");
    Console::Print("|      addq       |          add question         |   -mc, -wr, -tf  |   multiple choice, written, true/false   |     Quiz    |\n");
    Console::Print("|      insq       |     insert question at #      |   -mc, -wr, -tf  |   multiple choice, written, true/false   |     Quiz    |\n");
    Console::Print("|     listq       |       list all questions      |       -more      |            more detailed list            |     Quiz    |\n");
    Console::Print("|     editq       |        edit a question        |    -q, -c, -a    |   edit question, choices, and/or answer  |     Quiz    |\n");
    Console::Print("|      delq       |       delete a question       |         -        |                    -                     |     Quiz    |\n");
    Console::Print("|     swapq       |       swap 2 questions        |         -        |                    -                     |     Quiz    |\n");
    Console::Print("|      take       |           take quiz           |         -        |                    -                     |     Quiz    |\n");
    Console::Print("|      clr        |          clear screen         |         -        |                    -                     |     Root    |\n");
    Console::Print("|      save       |       save quiz to path       |       -new       |             save to new file             |     Quiz    |\n");
    Console::Print("|      load       |      load quiz from path      |         -        |                    -                     |     Root    |\n");
    Console::Print("|                 |                               |                  |                                          |             |\n");
    Console::Print("-------------------------------------------------------------------------------------------------------------------------------\n");
    Console::Print("Use 'docs' to see full documentation, or 'tut' to see the tutorial.\n\n");
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

void Application::Tut() {
    Util::OpenLink("https://github.com/jopo86/QuizMaker/wiki/Tutorial");
    SuccessMsg("Attempted to open link in browser. If it doesn't open, use this link:\n");
    Console::SetColor(Console::CYAN);
    Console::Print("https://github.com/jopo86/QuizMaker/wiki/Tutorial\n\n");
    Console::Reset();
    PollCommand();
}

void Application::Version() {
    Console::Print("Quiz Maker v" + GetVersionStr() + "\n\n");
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

void Application::SetSCA() {
    Console::Print("Show correct answer when incorrect? (y/n): ");
    char response = Util::ToLower(Console::Input()[0]);
    if (response == 'y') workingQuiz.setShowCorrectAnswer(true);
    else if (response == 'n') workingQuiz.setShowCorrectAnswer(false);
    else {
        Err("unrecognized response: '" + std::string(1, response) + "'\n\n", false);
        PollCommand();
        return;
    }
    Console::Print("\n");
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
    Console::Print("Enter Question type ('mc' for multiple choice, 'wr' for written, 'tf' for true/false): ");
    std::string type = Console::Input();
    if (Util::EqualsIgnoreCase(type, "wr")) {
        AddQuestion(Question::WRITTEN);
    }
    else if (Util::EqualsIgnoreCase(type, "mc")) {
        AddQuestion(Question::MULTIPLE_CHOICE);
    }
    else if (Util::EqualsIgnoreCase(type, "tf")) {
        AddQuestion(Question::TRUE_FALSE);
    }
    else {
        Err("unrecognized response: '" + type + "'. (aborted)\n\n", false);
        PollCommand();
        return;
    }
}

void Application::AddQuestion(const int type) {
    switch(type) {
        case Question::WRITTEN: {
            Question wq(Question::WRITTEN);
            Console::Print("Enter Question: ");
            wq.setQuestion(Console::Input());
            Console::Print("Enter answers (type '-' when done):\n");
            std::string answer;
            while (answer != "-") {
                answer = Console::Input();
                if (answer != "-") {
                    wq.addAnswer(answer);
                }
            }
            workingQuiz.addQuestion(wq);
            break;
        }
        case Question::MULTIPLE_CHOICE: {
            Question mcq(Question::MULTIPLE_CHOICE);
            Console::Print("Enter Question: ");
            mcq.setQuestion(Console::Input());
            Console::Print("Enter choices (enter '-' when finished):\n");
            std::string choice;
            int i = 0;
            while (choice != "-") {
                Console::Print(std::string(1, Util::NumToLetter(i)) + ") ");
                choice = Console::Input();
                if (choice != "-") {
                    mcq.addChoice(choice);
                }
                i++;
                if (i >= 26) {
                    Console::Print("Reached end of alphabet, no more choices allowed.\n");
                    break;
                }
            }
            Console::Print("Enter correct (letter) choice: ");
            char response = Util::ToLower(Console::Input()[0]);
            if (!Util::IsLetter(response)) {
                Err("'" + std::string(1, response) + "' is not a letter. (aborted)\n\n", false);
                PollCommand();
                return;
            }
            i = Util::LetterToNum(response);
            if (i >= mcq.getChoices().size()) {
                Err("choice '" + std::string(1, response) + "' does not exist. (aborted)\n\n", false);
                PollCommand();
                return;
            }
            std::string ans = mcq.getChoices()[i];
            mcq.setAnswer(ans);
            workingQuiz.addQuestion(mcq);
            break;
        }
        case Question::TRUE_FALSE: {
            Question tfq(Question::TRUE_FALSE);
            Console::Print("Enter Question: ");
            tfq.setQuestion(Console::Input());
            Console::Print("Enter answer (T/F): ");
            const char ans = Util::ToLower(Console::Input()[0]);
            if (!(ans == 't' || ans == 'f')) {
                Err("response must start with T/t or F/f. (aborted)\n\n", false);
                PollCommand();
                return;
            }
            tfq.setAnswer({ ans });
            workingQuiz.addQuestion(tfq);
            break;
        }
    }
    
    SuccessMsg("Question created.\n\n");
    PollCommand();
}

void Application::InsertQuestion() {
    Console::Reset();
    Console::Print("Enter Question type ('mc' for multiple choice, 'wr' for written, 'tf' for true/false): ");
    std::string type = Console::Input();
    if (Util::EqualsIgnoreCase(type, "wr")) {
        InsertQuestion(Question::WRITTEN);
    }
    else if (Util::EqualsIgnoreCase(type, "mc")) {
        InsertQuestion(Question::MULTIPLE_CHOICE);
    }
    else if (Util::EqualsIgnoreCase(type, "tf")) {
        InsertQuestion(Question::TRUE_FALSE);
    }
    else {
        Err("unrecognized response: '" + type + "'. (aborted)\n\n", false);
        PollCommand();
        return;
    }
}

void Application::InsertQuestion(const int type) {
    Console::Reset();

    if (workingQuiz.getQuestions().size() == 0) {
        Console::Print("Quiz has no questions.\n\n");
        PollCommand();
        return;
    }

    Console::Print("Question # to insert to (use 'listq' to see question #s): ");
    std::string response = Console::Input();
    std::string verif = VerifyQuestionNumInput(response);
    if (verif != "") {
        Err(verif + " (aborted)\n\n", false);
        PollCommand();
        return;
    }
    
    int qNum = std::stoi(response);
    std::vector<Question> questions;
    for (int i = 0; i < qNum - 1; i++) {
        questions.push_back(workingQuiz.getQuestions()[i]);
    }

    Question q;

    switch(type) {
        case Question::WRITTEN: {
            q = Question(Question::WRITTEN);
            Console::Print("Enter Question: ");
            q.setQuestion(Console::Input());
            Console::Print("Enter answers (type '-' when done):\n");
            std::string answer;
            while (answer != "-") {
                answer = Console::Input();
                if (answer != "-") {
                    q.addAnswer(answer);
                }
            }
            break;
        }
        case Question::MULTIPLE_CHOICE: {
            q = Question(Question::MULTIPLE_CHOICE);
            Console::Print("Enter Question: ");
            q.setQuestion(Console::Input());
            Console::Print("Enter choices (enter '-' when finished):\n");
            std::string choice;
            int i = 0;
            while (choice != "-") {
                Console::Print(std::string(1, Util::NumToLetter(i)) + ") ");
                choice = Console::Input();
                if (choice != "-") {
                    q.addChoice(choice);
                }
                i++;
            }
            Console::Print("Enter correct (letter) choice: ");
            char response = Util::ToLower(Console::Input()[0]);
            if (!Util::IsLetter(response)) {
                Err("'" + std::string(1, response) + "' is not a letter. (aborted)\n\n", false);
                PollCommand();
                return;
            }
            i = Util::LetterToNum(response);
            if (i >= q.getChoices().size()) {
                Err("choice '" + std::string(1, response) + "' does not exist. (aborted)\n\n", false);
            }
            std::string ans = q.getChoices()[i];
            q.setAnswer(ans);
            break;
        }
        case Question::TRUE_FALSE: {
            q = Question(Question::TRUE_FALSE);
            Console::Print("Enter Question: ");
            q.setQuestion(Console::Input());
            Console::Print("Enter answer (T/F): ");
            const char ans = Util::ToLower(Console::Input()[0]);
            if (!(ans == 't' || ans == 'f')) {
                Err("response must start with T/t or F/f. (aborted)\n\n", false);
                return;
            }
            q.setAnswer({ ans });
            break;
        }
    }

    questions.push_back(q);
    for (int i = qNum - 1; i < workingQuiz.getQuestions().size(); i++) {
        questions.push_back(workingQuiz.getQuestions()[i]);
    }

    workingQuiz.setQuestions(questions);

    SuccessMsg("Question inserted at #" + std::to_string(qNum) + ".\n\n");
    PollCommand();
}

void Application::ListQuestions(bool more) {
    Console::Reset();

    if (workingQuiz.getQuestions().size() == 0) {
        Console::Print("Quiz has no questions.\n\n");
        PollCommand();
        return;
    }

    Console::Print("\n");
    for (int i = 0; i < workingQuiz.getQuestions().size(); i++) {
        Console::Reset();
        Question q = workingQuiz.getQuestions()[i];
        int qNum = i + 1;
        Console::Print(std::to_string(qNum) + ") " + q.getQuestion() + "\n");

        if (more) {
            int _type = q.getType();
            std::string type;
            if (_type == Question::WRITTEN) type = "written";
            else if (_type == Question::MULTIPLE_CHOICE) type = "multiple choice";
            else if (_type == Question::TRUE_FALSE) type = "true/false";
            Console::Print("Type: ");
            Console::SetColor(Console::CYAN);
            Console::Print(type + "\n");
            Console::Reset();
            if (_type == Question::MULTIPLE_CHOICE) {
                Console::Print("Choices: \n");
                Console::SetColor(Console::CYAN);
                for (int j = 0; j < q.getChoices().size(); j++) {
                    Console::Print(std::string(1, Util::NumToLetter(j)) + ") " + q.getChoices()[j] + "\n");
                }
                Console::Reset();
            }
            if (_type == Question::WRITTEN) {
                Console::Print("Answers:\n");
                Console::SetColor(Console::CYAN);
                for (int j = 0; j < q.getAnswers().size(); j++) {
                    Console::Print(q.getAnswers()[j] + "\n");
                }
                Console::Print("\n");
                Console::Reset();
            }
            else {
                Console::Print("Answer: ");
                Console::SetColor(Console::CYAN);
                if (_type == Question::MULTIPLE_CHOICE) Console::Print(std::string(1, Util::NumToLetter(Util::Find(q.getChoices(), q.getAnswer()))) + ") ");
                Console::Print(q.getAnswer() + "\n\n");
                Console::Reset();
            }
        }
    }
    if (!more) Console::Print("\n");
    PollCommand();
}

void Application::EditQuestion(bool q, bool c, bool a, int qNum) {
    Console::Reset();

    if (workingQuiz.getQuestions().size() == 0) {
        Console::Print("Quiz has no questions.\n\n");
        PollCommand();
        return;
    }

    if (qNum == -1) {
        Console::Print("Question # to edit (use 'listq' to see question #s): ");
        std::string response = Console::Input();
        if (response == "" || !Util::IsNumber(response)) {
            Err("'" + response + "' is not a number. (aborted)\n\n", false);
            return;
        }
        qNum = std::stoi(response);
    }
    size_t size = workingQuiz.getQuestions().size();
    if (qNum > size) {
        Err("too large, quiz only has " + std::to_string(size) + " questions. (aborted)\n\n", false);
        return;
    }

    Question oldQuestion = workingQuiz.getQuestions()[qNum - 1];
    if (oldQuestion.getType() != Question::MULTIPLE_CHOICE && c) {
        Err("requested to edit choices, but question is not multiple choice. (aborted)\n\n", false);
        return;
    }

    if (!q && !c && !a) {
        bool _q, _c, _a = false;

        Console::Print("\nEdit question? (y/n): ");
        if (Console::Input()[0] == 'y') _q = true;

        if (oldQuestion.getType() == Question::MULTIPLE_CHOICE) {
            Console::Print("Edit choices? (y/n): ");
            if (Console::Input()[0] == 'y') _c = true;
        }

        Console::Print("Edit answer? (y/n): ");
        if (Console::Input()[0] == 'y') _a = true;

        if (!_q && !_c && !_a) {
            Console::Print("\n");
            PollCommand();
            return;
        }
        EditQuestion(_q, _c, _a, qNum);
    }
    else {
        // create new quiz, add questions before current qNum
        Quiz newQuiz;
        newQuiz.setName(workingQuiz.getName());
        for (int i = 0; i < qNum - 1; i++) {
            newQuiz.addQuestion(workingQuiz.getQuestions()[i]);
        }

        // create new question to replace current qNum
        Question newQuestion(workingQuiz.getQuestions()[qNum - 1].getType());

        if (q) {
            Console::Print("\nOld question: ");
            Console::SetColor(Console::CYAN);
            Console::Print(oldQuestion.getQuestion());
            Console::Reset();
            Console::Print("\nEnter new question: ");
            newQuestion.setQuestion(Console::Input());
            SuccessMsg("Question updated.\n");
        }
        else newQuestion.setQuestion(oldQuestion.getQuestion());

        if (c) {
            Console::Print("\nOld choices: \n");
            Console::SetColor(Console::CYAN);
            for (int j = 0; j < oldQuestion.getChoices().size(); j++) {
                Console::Print(std::string(1, Util::NumToLetter(j)) + ") " + oldQuestion.getChoices()[j] + "\n");
            }
            Console::Reset();
            Console::Print("Enter new choices (type '-' when done): \n");
            std::string choice;
            int i = 0;
            while (choice != "-") {
                Console::Print(std::string(1, Util::NumToLetter(i)) + ") ");
                choice = Console::Input();
                if (choice != "-") {
                    newQuestion.addChoice(choice);
                }
                i++;
                if (i >= 26) {
                    Console::Print("Reached end of alphabet, no more choices allowed.\n");
                    break;
                }
            }
            SuccessMsg("Choices updated.\n");
        }
        else if (oldQuestion.getType() == Question::MULTIPLE_CHOICE) {
            newQuestion.setChoices(oldQuestion.getChoices());
        }

        if (a) {
            if (newQuestion.getType() != Question::WRITTEN) {
                Console::Print("\nOld answer: ");
                Console::SetColor(Console::CYAN);
                Console::Print(oldQuestion.getAnswer());
                Console::Reset();
                Console::Print("\nEnter new answer: ");
                newQuestion.setAnswer(Console::Input());
                SuccessMsg("Answer updated.\n");
            }
            else {
                Console::Print("\nOld answers:\n");
                Console::SetColor(Console::CYAN);
                for (int j = 0; j < oldQuestion.getAnswers().size(); j++) {
                    Console::Print(oldQuestion.getAnswers()[j] + "\n");
                }
                Console::Reset();
                Console::Print("\nEnter new answers (type '-' when done):\n");
                std::string answer;
                while (answer != "-") {
                    answer = Console::Input();
                    if (answer != "-") {
                        newQuestion.addAnswer(answer);
                    }
                }
                SuccessMsg("Answers updated.\n");
            }
        }
        else newQuestion.setAnswer(oldQuestion.getAnswer());

        // add new question
        newQuiz.addQuestion(newQuestion);

        // add the rest of the questions
        for (int i = qNum; i < size; i++) {
            newQuiz.addQuestion(workingQuiz.getQuestions()[i]);
        }
        workingQuiz = newQuiz;

        Console::Print("\n");
        PollCommand();
    }
}

void Application::DeleteQuestion() {
    Console::Reset();

    if (workingQuiz.getQuestions().size() == 0) {
        Console::Print("Quiz has no questions.\n\n");
        PollCommand();
        return;
    }

    Console::Print("Question # to delete (use 'listq' to see question #s): ");
    std::string response = Console::Input();
    std::string verif = VerifyQuestionNumInput(response);
    if (verif != "") {
        Err(verif + " (aborted)\n\n", false);
        PollCommand();
        return;
    }
    int qNum = std::stoi(response);
    

    std::vector<Question> oldQuestions = workingQuiz.getQuestions();
    std::vector<Question> newQuestions;
    for (int i = 0; i < workingQuiz.getQuestions().size(); i++) {
        if (i != qNum - 1) newQuestions.push_back(oldQuestions[i]);
    }
    workingQuiz.setQuestions(newQuestions);
    SuccessMsg("Deleted question #" + std::to_string(qNum) + ".\n\n");
    PollCommand();
}

void Application::SwapQuestions() {
    Console::Print("Swap question #");
    std::string response = Console::Input();
    std::string verif = VerifyQuestionNumInput(response);
    if (verif != "") {
        Err(verif + " (aborted)\n\n", false);
        PollCommand();
        return;
    }
    int num1 = std::stoi(response);

    Console::Print("with question #");
    response = Console::Input();
    verif = VerifyQuestionNumInput(response);
    if (verif != "") {
        Err(verif + " (aborted)\n\n", false);
        PollCommand();
        return;
    }
    int num2 = std::stoi(response);

    if (num1 == num2) {
        Err("cannot swap the same question. (aborted)\n\n", false);
        PollCommand();
        return;
    }
    else if (num1 < 1 || num2 < 1) {
        Err("question # must be 1 or greater. (aborted)\n\n", false);
        PollCommand();
        return;
    }

    Question temp = workingQuiz.getQuestions()[num1 - 1];
    workingQuiz.setQuestion(workingQuiz.getQuestions()[num2 - 1], num1 - 1);
    workingQuiz.setQuestion(temp, num2 - 1);

    SuccessMsg("Swapped questions #" + std::to_string(num1) + " and #" + std::to_string(num2) + ".\n\n");
    PollCommand();
}

void Application::TakeQuiz() {
    Console::Reset();

    if (workingQuiz.getQuestions().size() == 0) {
        Console::Print("Quiz has no questions.\n\n");
        PollCommand();
        return;
    }
    
    Console::Clear();

    std::string header = Util::ToUpper(workingQuiz.getName());
    Console::SetColor(Console::MAGENTA);
    Console::Print("TAKING QUIZ: " + workingQuiz.getName() + "\n");
    Console::Reset();
    Console::Print("Use '[exit]' as an answer at any time to stop taking quiz.\n");
    Console::Print("Enter to continue.\n");
    Console::Input();
    Console::Print("\n");

    int qNum = 1;
    int score = 0;
    int maxScore = workingQuiz.getQuestions().size();

    for (int i = 0; i < workingQuiz.getQuestions().size(); i++) {
        Question q = workingQuiz.getQuestions()[i];
        Console::Print("QUESTION " + std::to_string(qNum) + ":\n");
        Console::SetColor(Console::CYAN);
        Console::Print(q.getQuestion() + "\n\n");
        Console::Reset();
        if (q.getType() == Question::WRITTEN) {
            Console::Print("Enter answer: ");
            std::string answer = Console::Input();
            if (Util::RemoveAllSpaces(answer) == "[exit]")  {
                Console::Print("\n");
                PollCommand();
                return;
            }
            if (q.check(answer)) {
                Console::SetColor(Console::GREEN);
                Console::Print("Correct! Enter to continue.\n");
                Console::Input();
                Console::Print("\n");
                Console::Reset();
                score++;
            }
            else {
                Console::SetColor(Console::RED);
                Console::Print("Incorrect! Enter to continue.\n");
                if (workingQuiz.showsCorrectAnswer()) { 
                    Console::Print("[Correct Answer(s): ");
                    for (int i = 0; i < q.getAnswers().size(); i++) {
                        Console::Print("'" +  q.getAnswers()[i] + "'");
                        if (i != q.getAnswers().size() - 1) Console::Print(", ");
                    }
                    Console::Print("]\n");
                }
                Console::Input();
                Console::Print("\n");
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

        enter_choice:
            Console::Reset();
            Console::Print("\nEnter (letter) choice: ");
            std::string response = Console::Input();
            if (Util::RemoveAllSpaces(response) == "[exit]")  {
                Console::Print("\n");
                PollCommand();
                return;
            }
            char letterChoice = response[0];
            int numChoice = Util::LetterToNum(letterChoice);
            if (numChoice >= q.getChoices().size() || numChoice == -1) {
                Err("choice does not exist, re-enter.", false);
                goto enter_choice;
            }
            if (q.check(q.getChoices()[numChoice])) {
                Console::SetColor(Console::GREEN);
                Console::Print("Correct! Enter to continue.\n");
                Console::Input();
                Console::Print("\n");
                Console::Reset();
                score++;
            }
            else {
                Console::SetColor(Console::RED);
                Console::Print("Incorrect! Enter to continue.\n");
                if (workingQuiz.showsCorrectAnswer()) Console::Print("[Correct Answer: " + std::string(1, Util::NumToLetter(Util::Find(q.getChoices(), q.getAnswer()))) + ") " + q.getAnswer() + "]\n");
                Console::Input();
                Console::Print("\n");
                Console::Reset();
            }
        }

        else if (q.getType() == Question::TRUE_FALSE) {
            Console::Print("Enter answer (T/F): ");
            std::string response = Console::Input();
            if (Util::RemoveAllSpaces(response) == "[exit]")  {
                Console::Print("\n");
                PollCommand();
                return;
            }
            char ans = Util::ToLower(response[0]);
            if (q.check({ ans })) {
                Console::SetColor(Console::GREEN);
                Console::Print("Correct! Enter to continue.\n");
                Console::Input();
                Console::Print("\n");
                Console::Reset();
                score++;
            }
            else {
                Console::SetColor(Console::RED);
                Console::Print("Incorrect! Enter to continue.\n");
                if (workingQuiz.showsCorrectAnswer()) Console::Print("[Correct Answer: " + q.getAnswer() + "]\n");
                Console::Input();
                Console::Print("\n");
                Console::Reset();
            }
        }
        qNum++;
    }

    SuccessMsg("Quiz Finished. Score: " + std::to_string(score) + "/" + std::to_string(maxScore) + " (" + std::to_string((int)((float)score / maxScore * 100)) + "%)" + "\n\n");
    PollCommand();
}

void Application::SaveQuiz(bool newSave) {
    if (newSave) {
        Console::Print("Save As: ");
        std::string path = Console::Input();
        path = QMS::Save(workingQuiz, path);
        workingPath = path;
        SuccessMsg("Quiz saved to '" + workingPath + "'.\n\n");
    }
    else {
        if (workingPath == "") {
            Err("no current path to save to. (aborted)\nUse 'save -new' to save to a new file.\n\n", false);
            PollCommand();
            return;
        }
        QMS::Save(workingQuiz, workingPath);
        SuccessMsg("Changes saved to '" + workingPath + "'.\n\n");
    }

    PollCommand();
}

void Application::LoadQuiz() {
    Console::Print("Path: ");
    std::string path = Console::Input();
    std::pair<Quiz, int> loadpair = QMS::Load(path);
    if (loadpair.second == QMS::FILE_NOT_QMS) {
        Err("not a .qms file. (aborted)\n\n", false);
        PollCommand();
        return;
    }
    else if (loadpair.second == QMS::FILE_NOT_FOUND) {
        Err("path '" + path + "' not found. (aborted)\n\n", false);
        PollCommand();
        return;
    }
    workingQuiz = loadpair.first;
    dir = "Quiz";
    SuccessMsg("Quiz loaded from '" + path + "'.\n\n");
    workingPath = path;
    PollCommand();
}

void Application::Root() {
    Console::Print("Are you sure you want to go back to root directory? Progress may be lost. (y/n): ");
    std::string response = Console::Input();
    if (response == "y") {
        workingQuiz = Quiz();
        dir = "";
        Console::Print("\n");
        PollCommand();
    }
    else if (response == "n") {
        Console::Print("\n");
        PollCommand();
    }
    else {
        Err("unrecognized response '" + response + "'\n\n", false);
        PollCommand();
    }
}

void Application::Clr() {
    Console::Clear();
    PollCommand();
}

void Application::Err(std::string msg, bool fatal) {
    Console::SetColor(Console::RED);
    if (fatal) {
        Console::Print("FATAL ERROR: " + msg + "\nEnter to quit.");
        Console::Input();
        exit(0);
    }
    else {
        Console::Print("ERROR: " + msg);
    }
}

void Application::Quit() {
    if (Util::EqualsIgnoreCase(lastCommand, "save")) ForceQuit();

    Console::Reset();
    Console::Print("Are you sure you want to quit? Progress may be lost. (y/n): ");
    std::string response = Console::Input();
    if (response == "y") {
        ForceQuit();
    }
    else if (response == "n") {
        Console::Print("\n");
        PollCommand();
    }
    else {
        Err("unrecognized response '" + response + "'\n\n", false);
        PollCommand();
    }
}

void Application::ForceQuit() {
    exit(0);
}

std::string Application::GetDir() {
    return dir;
}
