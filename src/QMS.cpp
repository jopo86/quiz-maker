#include "QMS.h"

const int QMS::FILE_NOT_FOUND = 1;
const int QMS::FILE_NOT_QMS = 2;

std::string QMS::Save(Quiz quiz, std::string _path) {
    std::string path;
    if (!Util::Contains(_path, ".qms")) path = _path + ".qms";
    else path = _path;

    std::string contents = "# This is a file format used to save and load quizzes. \n# Editing this file manually may lead to undefined behavior.\n\n";
    contents += quiz.getName() + "\n";
    contents += quiz.showsCorrectAnswer() ? "scat\n" : "scaf\n";

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
    return path;
}

std::pair<Quiz, int> QMS::Load(std::string path) {
    if (!Util::Contains(path, ".qms")) return std::pair<Quiz, int>(Quiz(), FILE_NOT_QMS);

    Quiz quiz = Quiz();
    std::string contents = Util::ReadFile(path);
    if (contents == Util::FILE_NOT_FOUND_ERROR) return std::pair<Quiz, int>(Quiz(), FILE_NOT_FOUND);

    std::vector<std::string> lines = Util::Split(contents, '\n');
    int firstLine = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (Util::Contains(lines[i], '#') || lines[i] == "") {
            firstLine++;
            continue;
        }

        if (i == firstLine) {
            quiz.setName(lines[i]);
            quiz.setShowCorrectAnswer(lines[i] == "scat");
        }
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

    return std::pair<Quiz, int>(quiz, 0);
}