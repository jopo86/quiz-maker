#pragma once

#include "Util.h"
#include "Quiz.h"
#include "Question.h"

class QMS {
public:
    static void Save(Quiz quiz, std::string path);
    static Quiz Load(std::string path);
};