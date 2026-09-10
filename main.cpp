#include <iostream>
#include "objects.hpp"

using namespace std;

void printMenu() {
    cout << "1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход\n";
}

void clearConsole() {
    system("clear");
}


int main() {
    setlocale(LC_ALL, "RU");

    int choice;
    CompressStation station{};
    Pipe pipe{};

    while (true) {
        clearConsole();

        printMenu();
        cout << "\nВведите команду: ";
        cin >> choice;
 
        switch (choice) {
            case 1: {
                clearConsole();
                cout << "1. Добавление трубы\n\n";

                createPipe(pipe);

                cin.ignore();
                cin.get();
                break;
            }

            case 2: {
                clearConsole();
                cout << "2. Добавление КС\n\n";

                createCSStation(station);

                cin.ignore();
                cin.get();
                break;
            }

            case 3: {
                clearConsole();

                if (pipe.name.empty()) {
                    cout << "Труба не создана\n";
                } else {
                    printPipe(pipe);
                }

                if (station.name.empty()) {
                    cout << "Компрессорная станция не создана\n";
                } else {
                    printCSstation(station);
                }

                cin.ignore();
                cin.get();
                break;
            }

            case 4: {
                clearConsole();

                if (pipe.name.empty()) {
                    cout << "Труба не создана\n";

                    cin.ignore();
                    cin.get();
                    break;
                }

                int repairchoice;

                cout << "4. Редактировать трубу\n\n";
                cout << "1. Установить: в ремонте\n"
                    << "2. Установить: не в ремонте\n"
                    << "0. Назад\n\n";

                cout << "Введите команду: ";
                cin >> repairchoice;

                if (repairchoice == 1) {
                    setRepairStatus(pipe, true);
                    cout << "Статус трубы: в ремонте\n";

                } else if (repairchoice == 2) {
                    setRepairStatus(pipe, false);
                    cout << "Статус трубы: не в ремонте\n";

                } else if (repairchoice == 0) {
                    break;

                } else {
                    cout << "Ошибка ввода, введите число 0, 1 или 2.\n";
                }

                cin.ignore();
                cin.get();
                break;
            }

            case 5: {
                clearConsole();

                if (station.name.empty()) {
                    cout << "Компрессорная станция не создана\n";

                    cin.ignore();
                    cin.get();
                    break;
                }

                int stationchoice;

                cout << "5. Редактировать КС\n\n";
                cout << "1. Запустить цех\n"
                    << "2. Остановить цех\n"
                    << "0. Назад\n\n";

                cout << "Введите команду: ";
                cin >> stationchoice;

                if (stationchoice == 1) {
                    startWorkstation(station);

                    cout << "Работающих цехов: "
                        << station.worker_count_active
                        << " из "
                        << station.worker_count
                        << "\n";

                } else if (stationchoice == 2) {
                    stopWorkstation(station);

                    cout << "Работающих цехов: "
                        << station.worker_count_active
                        << " из "
                        << station.worker_count
                        << "\n";

                } else if (stationchoice == 0) {
                    break;

                } else {
                    cout << "Ошибка ввода, введите число 0, 1 или 2.\n";
                }

                cin.ignore();
                cin.get();
                break;
            }

            case 6: {
                clearConsole();
                cout << "6. Сохранить\n\n";

                saveFile(pipe, station);

                cin.ignore();
                cin.get();
                break;
            }

            case 7: {
                clearConsole();
                cout << "7. Загрузить\n\n";

                loadFile(pipe, station);

                cin.ignore();
                cin.get();
                break;
            }

            case 0: {
                return 0;
            }

            default: {
                clearConsole();
                cout << "Некорректный ввод\n\n";

                cin.ignore();
                cin.get();
                break;
            }
        }
    }

   return 0;
}