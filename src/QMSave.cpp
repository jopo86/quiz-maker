#include "QMSave.h"

void QMSave::Save(Quiz quiz, std::string path) {
    std::string contents = "";
    contents += "name = \"" + quiz.getName() + "\";\nquestions = {\n";

    for (int i = 0; i < quiz.getQuestions().size(); i++) {
        Question q = quiz.getQuestions()[i];
        contents += "\t{\n\t\ttype = \"";
        if (q.getType() == Question::WRITTEN) contents += "wr";
        else if (q.getType() == Question::MULTIPLE_CHOICE) contents += "mc";
        else if (q.getType() == Question::TRUE_FALSE) contents += "tf";
        contents += "\";\n\t\t";
        contents += "question = \"" + q.getQuestion() + "\";\n\t\t";
        if (q.getType() == Question::MULTIPLE_CHOICE) {
            contents += "choices = {\n\t\t\t";
            for (int j = 0; j < q.getChoices().size(); j++) {
                std::string choice = q.getChoices()[j];
                contents += "\"" + choice + "\"";
                if (j != q.getChoices().size() - 1) contents += ", ";
            }
            contents += "\n\t\t};\n\t\t";
        }
        contents += "ans = \"" + q.getAnswer() + "\";\n\t}";
        if (i != quiz.getQuestions().size() - 1) contents += ",";
        contents += "\n";
    }
    contents += "};";

    Util::WriteFile(contents, path);
}

Quiz QMSave::Load(std::string path) {
    Quiz quiz();
    std::string contents = Util::ReadFile(path);
    int quoteStart = 0;
    int quoteEnd = 0;
    std::vector<std::string> quotes;
    for (int i = 0; i < contents.length(); i++) {
        if (contents[i] == '\"') {
            quoteStart = 0;
            for (int j = i; j < contents.length(); j++) {
                if (contents[j] == '\"') {
                    quoteEnd = 0;
                    i = j + 1;
                    break;
                }
            }
        }
        quotes.push_back(Util::Substr(contents, quoteStart + 1, quoteEnd));
    }
    for (std::string quote : quotes) {
        std::cout << quote << "\n";
    }
}