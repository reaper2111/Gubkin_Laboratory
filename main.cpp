#include <iostream>
#include "objects.hpp"

using namespace std;

void printMenu() {
    cout << "1. Добавить трубу\n"
         << "2. Добавить КС\n"
         << "3. Просмотр всех объектов\n"
         << "4. Редактировать трубу\n"
         << "5. Редактировать КС\n"
         << "6. Сохранить\n"
         << "7. Загрузить\n"
         << "0. Выход\n";
}

void clearConsole() {
    system("clear");
}

int main() {
    setlocale(LC_ALL, "RU");

    Pipe pipe{};
    CompressStation station{};

    while (true) {
        clearConsole();

        printMenu();

        cout << "\nВведите команду: ";
        int choice = inputInt();

        while (choice < 0 || choice > 7) {
            cout << "Ошибка. Введите число от 0 до 7: ";
            choice = inputInt();
        }

        clearConsole();

        switch (choice) {
            case 1:
                createPipe(pipe);
                break;

            case 2:
                createCS(station);
                break;

            case 3:
                showObjects(pipe, station);
                break;

            case 4:
                editPipe(pipe);
                break;

            case 5:
                editCS(station);
                break;

            case 6:
                saveFile(pipe, station);
                break;

            case 7:
                loadFile(pipe, station);
                break;

            case 0:
                return 0;
        }

        cin.ignore(1000, '\n');

        cout << "\nНажмите Enter для продолжения...";
        cin.get();
    }
}