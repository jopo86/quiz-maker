#include "Util.h"

bool Util::Contains(std::vector<std::string> vec, std::string elem) {
    for (std::string _elem : vec) {
        if (_elem == elem) return true;
    }
    return false;
}