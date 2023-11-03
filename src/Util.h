#pragma once

#include <iostream>
#include <string>
#include <map>

class Util
{
private:
    
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

    // static const std::map<char, int> letterIndices = {
    //     { 'A',  0 }, { 'a',  0 }, { 'B',  1 }, { 'b',  1 },
    //     { 'C',  2 }, { 'c',  2 }, { 'D',  3 }, { 'd',  3 },
    //     { 'E',  4 }, { 'e',  4 }, { 'F',  5 }, { 'f',  5 },
    //     { 'G',  6 }, { 'g',  6 }, { 'H',  7 }, { 'h',  7 },
    //     { 'I',  8 }, { 'i',  8 }, { 'J',  9 }, { 'j',  9 },
    //     { 'K', 10 }, { 'k', 10 }, { 'L', 11 }, { 'l', 11 },
    //     { 'M', 12 }, { 'm', 12 }, { 'N', 13 }, { 'n', 13 },
    //     { 'O', 14 }, { 'o', 14 }, { 'P', 15 }, { 'p', 15 },
    //     { 'Q', 16 }, { 'q', 16 }, { 'R', 17 }, { 'r', 17 },
    //     { 'S', 18 }, { 's', 18 }, { 'T', 19 }, { 't', 19 },
    //     { 'U', 20 }, { 'u', 20 }, { 'V', 21 }, { 'v', 21 },
    //     { 'W', 22 }, { 'w', 22 }, { 'X', 23 }, { 'x', 23 },
    //     { 'Y', 24 }, { 'y', 24 }, { 'Z', 25 }, { 'z', 25 }
    // };

    static char ToUpperCase(char c);
    static char ToLowerCase(char c);

public:
    template<typename T>
    static bool Contains(T arr[], size_t size, T elem);

    static std::string ToUpperCase(std::string str);
    static std::string ToLowerCase(std::string str);
    static bool EqualsIgnoreCase(std::string a, std::string b);
};