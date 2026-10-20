#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

bool readInput(string& text) {
    if (!getline(cin, text)) {
        cerr << "Конец ввода\n";
        return false;
    }
    cerr << "Ввод: " << text << '\n';
    return true;
}

bool validString(const string& value) {
    if (value.empty() || value.size() > 240 || value.find_first_not_of(' ') == string::npos) {
        return false;
    }
    for (unsigned char symbol : value) {
        if (symbol < 32 || symbol == 127) {
            return false;
        }
    }
    return true;
}

bool inputString(string& value) {
    while (readInput(value)) {
        if (validString(value)) {
            return true;
        }
        cerr << "Ошибка ввода строки" << '\n';
        cout << "Ошибка. Введите непустую строку до 240 байт без управляющих символов: ";
    }
    return false;
}

bool inputInt(int& value, int minimum, int maximum) {
    string text;
    while (readInput(text)) {
        istringstream line(text);
        int number;
        if (line >> number && (line >> ws).eof() && number >= minimum && number <= maximum) {
            value = number;
            return true;
        }
        cerr << "Ошибка ввода целого числа" << '\n';
        cout << "Ошибка. Введите целое число от " << minimum << " до " << maximum << ": ";
    }
    return false;
}

bool inputPercent(double& value, double minimum) {
    string text;
    while (readInput(text)) {
        istringstream line(text);
        double number;
        if (line >> number && (line >> ws).eof() && isfinite(number) && number >= minimum && number <= 100) {
            value = number;
            return true;
        }
        cerr << "Ошибка ввода процента" << '\n';
        cout << "Ошибка. Введите процент от " << minimum << " до 100 (дробная часть через точку): ";
    }
    return false;
}

bool readFileLine(ifstream& file, string& line) {
    if (!getline(file, line)) {
        return false;
    }
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }
    return true;
}

bool readFileInt(ifstream& file, int& value, int minimum, int maximum) {
    string text;
    if (!readFileLine(file, text)) {
        return false;
    }
    istringstream line(text);
    return (line >> value) && (line >> ws).eof() && value >= minimum && value <= maximum;
}

