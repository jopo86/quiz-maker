#pragma once

#include "Util.h"
#include "Quiz.h"

class QMSave {
public:
    static void Save(Quiz quiz, std::string path);
    static Quiz Load(std::string path);
};