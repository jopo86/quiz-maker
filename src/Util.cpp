#include "Util.h"

const char Util::LOWER[] = "abcdefghijklmnopqrstuvwxyz";
const char Util::UPPER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

bool Util::IsLower(char c) {
    return Contains(LOWER, sizeof(LOWER) / sizeof(char), c);
}

bool Util::IsUpper(char c) {
    return Contains(UPPER, sizeof(LOWER) / sizeof(char), c);
}

bool Util::IsLetter(char c) {
    return IsLower(c) || IsUpper(c);
}

bool Util::IsDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Util::IsAlpha(char c) {
    return IsLetter(c) || IsDigit(c);
}

bool Util::IsWhitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

bool Util::IsPunctuation(char c) {
    return c == '.' || c == ',' || c == '!' || c == '?' || c == ';' || c == ':' || c == '\'' || c == '\"';
}

bool Util::IsSpecial(char c) {
    return IsWhitespace(c) || IsPunctuation(c);
}

std::string Util::ToLower(std::string str) {
    std::string lower = "";
    for (int i = 0; i < str.length(); i++) {
        if (IsUpper(str[i])) lower += LOWER[Find(UPPER, sizeof(UPPER) / sizeof(char), str[i])];
        else lower += str[i];
    }
    return lower;
}

std::string Util::ToUpper(std::string str) {
    std::string upper = "";
    for (int i = 0; i < str.length(); i++) {
        if (IsLower(str[i])) upper += UPPER[Find(LOWER, sizeof(LOWER) / sizeof(char), str[i])];
        else upper += str[i];
    }
    return upper;
}

bool Util::EqualsIgnoreCase(std::string a, std::string b) {
    return ToLower(a) == ToLower(b);
}