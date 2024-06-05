#include <iostream>
#include <Windows.h>
#include <cstring>
#include <string>

using namespace std;

// Определяем тип функции указателя
typedef bool(*FindSymbol)(const char*, const char*);

int main() {
    // Устанавливаем русскую локаль
    setlocale(LC_ALL, "Russian");

    // Загружаем динамическую библиотеку
    HINSTANCE hLibrary = LoadLibrary(L"library2.dll");

    // Проверяем, успешно ли загружена библиотека
    if (!hLibrary)
    {
        cout << "Библиотека не загружается" << endl;
        return 1;
    }

    // Получаем указатель на функцию из библиотеки
    FindSymbol findSymbolFunc = (FindSymbol)GetProcAddress(hLibrary, "FindLetters");

    // Проверяем, удалось ли получить указатель на функцию
    if (!findSymbolFunc)
    {
        cout << "Функция не найдена в библиотеке" << endl;
        // Выгружаем библиотеку и завершаем программу
        FreeLibrary(hLibrary);
        return 1;
    }

    // Объявляем переменные для ввода строки и символа для поиска
    string inputString, symbolToFind;

    // Цикл для ввода строки пользователем
    do
    {
        cout << "Введите строку: ";
        getline(cin, inputString);
    } while (inputString.empty());

    // Запрашиваем символ для поиска
    cout << "Что тебе найти?";
    cin >> symbolToFind;

    // Вызываем функцию из библиотеки для поиска символа в строке
    bool result = findSymbolFunc(inputString.c_str(), symbolToFind.c_str());

    // Выводим результат поиска
    if (result)
    {
        cout << "Есть такая буква";
    }
    else
    {
        cout << "Нет такого символа";
    }

    // Выгружаем библиотеку
    FreeLibrary(hLibrary);
    return 0;
}