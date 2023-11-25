#include "Util.h"

const char Util::LOWER[] = "abcdefghijklmnopqrstuvwxyz";
const char Util::UPPER[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

const std::string Util::FILE_NOT_FOUND_ERROR = "L7YVPT6KNZBGKAMRXJUGVVTRDDSZTPU6GBQPS6WCZMGTV4BF9KAWW6D7JPJN6ASV";

int Util::Find(std::string str, char c) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == c) return i;
    }
    return -1;
}

int Util::Find(std::string str, std::string substr) {
    for (int i = 0; i < str.length() - substr.length() + 1; i++) {
        bool found = true;
        for (int j = 0; j < substr.length(); j++) {
            if (str[i + j] != substr[j]) found = false;
        }
        if (found) return i;
    }
    return -1;
}

bool Util::Contains(std::string str, char c) {
    return Find(str, c) != -1;
}

bool Util::Contains(std::string str, std::string substr) {
    return Find(str, substr) != -1;
}

bool Util::IsLower(const char c) {
    return Contains(LOWER, sizeof(LOWER) / sizeof(char), c);
}

bool Util::IsUpper(const char c) {
    return Contains(UPPER, sizeof(LOWER) / sizeof(char), c);
}

bool Util::IsLetter(const char c) {
    return IsLower(c) || IsUpper(c);
}

bool Util::IsDigit(const char c) {
    return c >= '0' && c <= '9';
}

bool Util::IsNumber(std::string str) {
    for (int i = 0; i < str.length(); i++) {
        if (!IsDigit(str[i])) return false;
    }
    return true;
}

bool Util::IsAlpha(const char c) {
    return IsLetter(c) || IsDigit(c);
}

bool Util::IsWhitespace(const char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

bool Util::IsPunctuation(const char c) {
    return c == '.' || c == ',' || c == '!' || c == '?' || c == ';' || c == ':' || c == '\'' || c == '\"';
}

bool Util::IsSpecial(const char c) {
    return IsWhitespace(c) || IsPunctuation(c);
}

char Util::ToLower(const char c) {
    if (IsUpper(c)) return LOWER[Find(UPPER, sizeof(UPPER) / sizeof(char), c)];
    else return c;
}

char Util::ToUpper(const char c) {
    if (IsLower(c)) return UPPER[Find(LOWER, sizeof(LOWER) / sizeof(char), c)];
    else return c;
}

std::string Util::ToLower(std::string str) {
    std::string lower = "";
    for (int i = 0; i < str.length(); i++) {
        lower += ToLower(str[i]);
    }
    return lower;
}

std::string Util::ToUpper(std::string str) {
    std::string upper = "";
    for (int i = 0; i < str.length(); i++) {
        upper += ToUpper(str[i]);
    }
    return upper;
}

char Util::NumToLetter(int i) {
    if (i >= sizeof(LOWER) / sizeof(char) || i < 0) throw "index out of bounds for letter array";
    return LOWER[i];
}

int Util::LetterToNum(char c) {
    return Find(LOWER, sizeof(LOWER) / sizeof(char), c);
}

std::string Util::RemoveAllSpaces(std::string str) {
    std::string newstr;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') newstr += str[i];
    }
    return newstr;
}

bool Util::EqualsIgnoreCase(std::string a, std::string b) {
    return ToLower(a) == ToLower(b);
}

std::string Util::Substr(std::string str, int start, int end) {
    std::string substr;
    for (int i = start; i < end; i++) {
        substr += str[i];
    }
    return substr;
}

std::vector<std::string> Util::Split(std::string str, char delim) {
    std::vector<std::string> split;
    std::string curr = "";
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delim) {
            split.push_back(curr);
            curr = "";
        }
        else curr += str[i];
    }
    split.push_back(curr);
    return split;
}

#ifdef _WIN32
void Util::OpenLink(std::string link) {
    ShellExecuteA(NULL, "open", link.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
#else
void Util::OpenLink(std::string link) {
    std::string cmd = "xdg-open " + link;
    system(cmd.c_str());
}
#endif

void Util::WriteFile(std::string contents, std::string path) {
    std::ofstream file;
    file.open(path);
    file << contents;
    file.close();
}

std::string Util::ReadFile(std::string path) {
    std::string whole;
    std::string line;
    std::ifstream file(path);
    if (file.is_open()) {
        while (std::getline(file, line)) {
            whole += line + '\n';
        }
        file.close();
        return whole;
    }
    else return FILE_NOT_FOUND_ERROR;
}