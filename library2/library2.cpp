#include <string>

extern "C" __declspec(dllexport) bool FindLetters(const char* inputString, const char* symbolsToFind) {
    std::string str(inputString);
    std::string symbols(symbolsToFind);

    for (char c : symbols) {
        if (str.find(c) == std::string::npos) {
            return false;
        }
    }
    return true;
}
