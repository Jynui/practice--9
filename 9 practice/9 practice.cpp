#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

// Define the function pointer type for the external function
typedef bool(*FindSymbol)(const char*, const char*);

int main() {
    // Set the Russian locale
    setlocale(LC_ALL, "Russian");

    // Load the dynamic library
    HINSTANCE hLibrary = LoadLibrary(L"library2.dll");

    // Check if the library was successfully loaded
    if (!hLibrary) {
        cout << "Не удалось загрузить библиотеку: " << GetLastError() << endl;
        return 1;
    }

    // Get the pointer to the function from the library
    FindSymbol findSymbolFunc = (FindSymbol)GetProcAddress(hLibrary, "FindLetters");

    // Check if the function pointer was successfully obtained
    if (!findSymbolFunc) {
        cout << "Не удалось найти функцию в библиотеке: " << GetLastError() << endl;
        // Unload the library and exit
        FreeLibrary(hLibrary);
        return 1;
    }

    // Declare variables for input string and the symbol to find
    string inputString, symbolToFind;

    // Loop for user input string
    do {
        cout << "Введите строку: ";
        getline(cin, inputString);
    } while (inputString.empty());

    // Request the symbol to find, ensure it's a single character
    do {
        cout << "Что тебе найти (один символ)? ";
        cin >> symbolToFind;
    } while (symbolToFind.length() != 1);

    // Call the function from the library to find the symbol in the string
    bool result = findSymbolFunc(inputString.c_str(), symbolToFind.c_str());

    // Output the search result
    if (result) {
        cout << "Есть такая буква" << endl;
    }
    else {
        cout << "Нет такого символа" << endl;
    }

    // Unload the library
    FreeLibrary(hLibrary);
    return 0;
}
