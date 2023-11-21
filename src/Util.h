#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <windows.h>
#include <shellapi.h>

class Util {

private:
    static const char LOWER[];
    static const char UPPER[];

public:
    static const std::string FILE_NOT_FOUND_ERROR;

    template<typename T>
    static int Find(const T* arr, size_t len, T elem) {
        for (int i = 0; i < len; i++) {
            if (arr[i] == elem) return i;
        }
        return -1;
    }

    template<typename T>
    static int Find(std::vector<T> vec, T elem) {
        return Find(vec.data(), vec.size(), elem);
    }

    template<typename T>
    static bool Contains(const T* arr, size_t len, T elem) {
        return Find(arr, len, elem) != -1;
    }

    template<typename T>
    static bool Contains(std::vector<T> vec, T elem) {
        return Find(vec, elem) != -1;
    }

    static bool IsLower(const char c);
    static bool IsUpper(const char c);
    static bool IsLetter(const char c);
    static bool IsDigit(const char c);
    static bool IsAlpha(const char c);
    static bool IsWhitespace(const char c);
    static bool IsPunctuation(const char c);
    static bool IsSpecial(const char c);

    static char ToLower(const char c);
    static char ToUpper(const char c);
    static std::string ToLower(std::string str);
    static std::string ToUpper(std::string str);

    static char NumToLetter(int i);
    static int LetterToNum(char c);

    static bool EqualsIgnoreCase(std::string a, std::string b);

    static std::string Substr(std::string str, int start, int end);

    static void OpenLink(std::string link);

    static void WriteFile(std::string path, std::string text);
    static std::string ReadFile(std::string path);
};