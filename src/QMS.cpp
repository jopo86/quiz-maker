#include "QMS.h"

void QMS::Save(Quiz quiz, std::string path) {
    std::string contents = "# This is a file format used to save and load quizzes. \n# Editing this file manually may lead to undefined behavior.\n";
    contents += quiz.getName() + "\n";

    for (int i = 0; i < quiz.getQuestions().size(); i++) {
        contents += "^\n";
        Question q = quiz.getQuestions()[i];
        if (q.getType() == Question::WRITTEN) contents += "wr\n";
        else if (q.getType() == Question::MULTIPLE_CHOICE) contents += "mc\n";
        else if (q.getType() == Question::TRUE_FALSE) contents += "tf\n";
        contents += q.getQuestion() + "\n";
        if (q.getType() == Question::MULTIPLE_CHOICE) {
            contents += "-\n";
            for (int j = 0; j < q.getChoices().size(); j++) {
                contents += q.getChoices()[j] + "\n";
            }
            contents += "-\n";
        }
        contents += q.getAnswer() + "\n";
    }

    Util::WriteFile(contents, path);
}

Quiz QMS::Load(std::string path) {
    Quiz quiz = Quiz();
    std::string contents = Util::ReadFile(path);
    std::vector<std::string> lines = Util::Split(contents, '\n');
    int firstLine = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (Util::Contains(lines[i], '#')) {
            firstLine++;
            continue;
        }

        if (i == firstLine) quiz.setName(lines[i]);
        else if (lines[i] == "^") {
            int j = i + 1;
            std::string type = lines[j];
            j++;
            std::string question = lines[j];
            j++;
            if (type == "mc") {
                j++;
                std::vector<std::string> choices;
                while (lines[j] != "-") {
                    choices.push_back(lines[j]);
                    j++;
                }
                j++;
                std::string answer = lines[j];
                Question q(Question::MULTIPLE_CHOICE, question, answer);
                q.setChoices(choices);
                quiz.addQuestion(q);
            }
            else {
                std::string answer = lines[j];
                if (type == "wr") quiz.addQuestion(Question(Question::WRITTEN, question, answer));
                else if (type == "tf") quiz.addQuestion(Question(Question::TRUE_FALSE, question, answer));
            }
            i = j;
        }

    }

    return quiz;
}