#include "console.hpp"
#include "network.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <ctime>
#include <iomanip>

using namespace std;

class redirect_output_wrapper {
    ostream& stream;
    streambuf* oldBuffer;

public:
    redirect_output_wrapper(ostream& source) : stream(source), oldBuffer(source.rdbuf()) {}
    ~redirect_output_wrapper() { stream.rdbuf(oldBuffer); }
    void redirect(ostream& file) { stream.rdbuf(file.rdbuf()); }
};

void printMenu() {
    cout << "1. Добавить трубу\n"
         << "2. Добавить КС\n"
         << "3. Просмотр всех объектов\n"
         << "4. Редактировать трубу\n"
         << "5. Редактировать КС\n"
         << "6. Сохранить\n"
         << "7. Загрузить\n"
         << "8. Удалить трубу\n"
         << "9. Удалить КС\n"
         << "10. Поиск труб\n"
         << "11. Поиск КС\n"
         << "12. Пакетное редактирование труб\n"
         << "0. Выход\n";
}

int runConsole() {
    map<int, Pipe> pipes;
    map<int, CompressStation> stations;
    int nextId = 1;

    time_t now = time(nullptr);
    ostringstream name;
    name << "log_" << put_time(localtime(&now), "%d_%m_%Y_%H_%M_%S") << ".txt";
    string logFileName = name.str();
    ofstream logfile(logFileName, ios::app);
    if (!logfile) {
        cerr << "Ошибка открытия журнала\n";
        return 1;
    }
    redirect_output_wrapper cerrOut(cerr);
    cerrOut.redirect(logfile);
    cerr << "Запуск программы\n";

    while (cin) {
        printMenu();
        cout << "\nВведите команду: ";
        int choice;
        if (!inputInt(choice, 0, 12)) {
            break;
        }

        cerr << "Команда меню: " + to_string(choice) << '\n';
        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1: {
                if (nextId == numeric_limits<int>::max()) {
                    cout << "Нет свободных ID\n";
                    break;
                }
                Pipe pipe(nextId);
                if (!pipe.createPipe()) {
                    break;
                }
                nextId++;
                pipes.emplace(pipe.getId(), pipe);
                cout << "Добавлена труба. ID: " << pipe.getId() << "\n";
                cerr << "Добавлена труба ID " + to_string(pipe.getId()) << '\n';
                break;
            }

            case 2: {
                if (nextId == numeric_limits<int>::max()) {
                    cout << "Нет свободных ID\n";
                    break;
                }
                CompressStation station(nextId);
                if (!station.createCS()) {
                    break;
                }
                nextId++;
                stations.emplace(station.getId(), station);
                cout << "Добавлена КС. ID: " << station.getId() << "\n";
                cerr << "Добавлена КС ID " + to_string(station.getId()) << '\n';
                break;
            }

            case 3:
                showObjects(pipes, stations);
                break;

            case 4: {
                int id = inputId(pipes);
                if (id != 0) {
                    pipes.at(id).editPipe();
                }
                break;
            }

            case 5: {
                int id = inputId(stations);
                if (id != 0) {
                    stations.at(id).editCS();
                }
                break;
            }

            case 6:
                saveFile(pipes, stations, nextId, logFileName);
                break;

            case 7:
                loadFile(pipes, stations, nextId);
                break;

            case 8: {
                int id = inputId(pipes);
                if (id != 0) {
                    pipes.erase(id);
                    cerr << "Удалена труба ID " + to_string(id) << '\n';
                    cout << "Труба удалена\n";
                }
                break;
            }

            case 9: {
                int id = inputId(stations);
                if (id != 0) {
                    stations.erase(id);
                    cerr << "Удалена КС ID " + to_string(id) << '\n';
                    cout << "КС удалена\n";
                }
                break;
            }

            case 10:
                findPipes(pipes);
                break;

            case 11:
                findCS(stations);
                break;

            case 12:
                editPipes(pipes);
                break;
        }

        if (!cin) {
            break;
        }

        cout << "\nНажмите Enter для продолжения...";
        string line;
        while (readInput(line) && !line.empty()) {
            cout << "Ошибка. Для продолжения нажмите Enter без других символов: ";
        }
    }

    if (!cin) {
        cout << "\nВвод завершён. Выход из программы.\n";
    }
    cerr << "Выход из программы\n";
    logfile.flush();
    if (!logfile.good()) {
        cout << "Ошибка записи в журнал\n";
        return 1;
    }
    return 0;
}
