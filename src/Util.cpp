#include "Util.h"

template<typename T>
bool Util::Contains(T arr[], size_t size, T elem) {
    for (int  i = 0; i < size; i++) {
        if (arr[i] == elem) return true;
    }
    return false;
}

char Util::ToUpperCase(char c) {

}

bool Util::EqualsIgnoreCase(std::string a, std::string b)
{

}