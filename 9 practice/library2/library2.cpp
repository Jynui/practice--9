#include <string>

extern "C" __declspec(dllexport) bool FindLetters(const char* inputString, const char* symbolToFind) {
    std::string str(inputString);
    std::string chars(symbolToFind);

    for (char c : chars) {
        if (str.find(c) == std::string::npos) {
            return false;
        }
    }
    return true;
}
