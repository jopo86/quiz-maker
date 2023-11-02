#pragma once

#include <iostream>
#include <string>
#include <map>

class Utils
{
private:
    Utils() = delete;
    ~Utils() = delete;
    
    static constexpr char upperCases[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
        'J', 'K' ,'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T' ,'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    static constexpr char lowerCases[] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
        'j', 'k' ,'l', 'm', 'n', 'o', 'p', 'q', 'r',
        's', 't' ,'u', 'v', 'w', 'x', 'y', 'z'
    };

    static char ToUpperCase(char c);
    static char ToLowerCase(char c);

public:
    static bool ToUpperCase(std::string str);
    static bool ToLowerCase(std::string str);
    static bool EqualsIgnoreCase(std::string a, std::string b);
};