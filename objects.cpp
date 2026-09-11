#include <iostream>
#include <fstream>
#include "objects.hpp"

using namespace std;


// Проверка ввода целого числа
int inputInt() {
    int value;

    cin >> value;

    while (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Ошибка. Введите число: ";
        cin >> value;
    }

    return value;
}


// Запуск одного цеха
void startWorkstation(CompressStation& station) {
    if (station.worker_count == 0) {
        cout << "Компрессорная станция не создана\n";
        return;
    }

    if (station.worker_count_active < station.worker_count) {
        station.worker_count_active++;
    } else {
        cout << "Все цеха уже запущены\n";
    }
}


// Остановка одного цеха
void stopWorkstation(CompressStation& station) {
    if (station.worker_count == 0) {
        cout << "Компрессорная станция не создана\n";
        return;
    }

    if (station.worker_count_active > 0) {
        station.worker_count_active--;
    } else {
        cout << "Все цеха уже остановлены\n";
    }
}


// Изменение статуса ремонта трубы
void setRepairStatus(Pipe& pipe, bool status) {
    pipe.isRepair = status;
}


// Создание трубы
void createPipe(Pipe& pipe) {
    cout << "Введите название трубы: ";
    cin >> pipe.name;

    cout << "Введите длину трубы: ";
    pipe.length = inputInt();

    while (pipe.length <= 0) {
        cout << "Ошибка. Длина должна быть больше 0: ";
        pipe.length = inputInt();
    }

    cout << "Введите диаметр трубы: ";
    pipe.diameter = inputInt();

    while (pipe.diameter <= 0) {
        cout << "Ошибка. Диаметр должен быть больше 0: ";
        pipe.diameter = inputInt();
    }

    int repairStatus;

    cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    repairStatus = inputInt();

    while (repairStatus != 0 && repairStatus != 1) {
        cout << "Ошибка. Введите 0 или 1: ";
        repairStatus = inputInt();
    }

    pipe.isRepair = repairStatus;
}


// Создание компрессорной станции
void createCS(CompressStation& station) {
    cout << "Введите название КС: ";
    cin >> station.name;

    cout << "Введите количество цехов: ";
    station.worker_count = inputInt();

    while (station.worker_count <= 0) {
        cout << "Ошибка. Количество цехов должно быть больше 0: ";
        station.worker_count = inputInt();
    }

    cout << "Введите количество работающих цехов: ";
    station.worker_count_active = inputInt();

    while (
        station.worker_count_active < 0 ||
        station.worker_count_active > station.worker_count
    ) {
        cout << "Ошибка. Работающих цехов должно быть от 0 до "
             << station.worker_count << ": ";

        station.worker_count_active = inputInt();
    }

    cout << "Введите класс станции (1 или 2): ";
    station.station_class = inputInt();

    while (station.station_class < 1 || station.station_class > 2) {
        cout << "Ошибка. Класс станции должен быть 1 или 2: ";
        station.station_class = inputInt();
    }
}


// Вывод трубы
void printPipe(const Pipe& pipe) {
    cout << "------------------------------\n";
    cout << "Название: " << pipe.name << "\n";
    cout << "Диаметр:  " << pipe.diameter << "\n";
    cout << "Длина:    " << pipe.length << "\n";
    cout << "Ремонт:   " << (pipe.isRepair ? "Да" : "Нет") << "\n";
    cout << "------------------------------\n";
}


// Вывод компрессорной станции
void printCS(const CompressStation& station) {
    cout << "------------------------------\n";
    cout << "Название:            " << station.name << "\n";
    cout << "Всего цехов:         " << station.worker_count << "\n";
    cout << "Работающих цехов:    " << station.worker_count_active << "\n";
    cout << "Класс станции:       " << station.station_class << "\n";
    cout << "------------------------------\n";
}


// Просмотр всех объектов
void showObjects(const Pipe& pipe, const CompressStation& station) {
    if (pipe.name.empty()) {
        cout << "Труба не создана\n";
    } else {
        printPipe(pipe);
    }

    if (station.name.empty()) {
        cout << "Компрессорная станция не создана\n";
    } else {
        printCS(station);
    }
}


// Редактирование трубы
void editPipe(Pipe& pipe) {
    if (pipe.name.empty()) {
        cout << "Труба не создана\n";
        return;
    }

    cout << "4. Редактировать трубу\n\n";

    cout << "1. Установить: в ремонте\n"
         << "2. Установить: не в ремонте\n"
         << "0. Назад\n\n";

    cout << "Введите команду: ";
    int choice = inputInt();

    while (choice < 0 || choice > 2) {
        cout << "Ошибка. Введите число от 0 до 2: ";
        choice = inputInt();
    }

    if (choice == 1) {
        setRepairStatus(pipe, true);
        cout << "Статус трубы: в ремонте\n";

    } else if (choice == 2) {
        setRepairStatus(pipe, false);
        cout << "Статус трубы: не в ремонте\n";
    }
}


// Редактирование КС
void editCS(CompressStation& station) {
    if (station.name.empty()) {
        cout << "Компрессорная станция не создана\n";
        return;
    }

    cout << "5. Редактировать КС\n\n";

    cout << "1. Запустить цех\n"
         << "2. Остановить цех\n"
         << "0. Назад\n\n";

    cout << "Введите команду: ";
    int choice = inputInt();

    while (choice < 0 || choice > 2) {
        cout << "Ошибка. Введите число от 0 до 2: ";
        choice = inputInt();
    }

    if (choice == 1) {
        startWorkstation(station);

        cout << "Работающих цехов: "
             << station.worker_count_active
             << " из "
             << station.worker_count
             << "\n";

    } else if (choice == 2) {
        stopWorkstation(station);

        cout << "Работающих цехов: "
             << station.worker_count_active
             << " из "
             << station.worker_count
             << "\n";
    }
}


// Сохранение в файл
void saveFile(const Pipe& pipe, const CompressStation& station) {
    string filename;

    cout << "Введите имя файла: ";
    cin >> filename;

    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла.\n";
        return;
    }

    file << pipe.name << "\n";
    file << pipe.length << "\n";
    file << pipe.diameter << "\n";
    file << pipe.isRepair << "\n";

    file << station.name << "\n";
    file << station.worker_count << "\n";
    file << station.worker_count_active << "\n";
    file << station.station_class << "\n";

    file.close();

    cout << "Данные сохранены в файл.\n";
}


// Загрузка из файла
void loadFile(Pipe& pipe, CompressStation& station) {
    string filename;

    cout << "Введите имя файла: ";
    cin >> filename;

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла.\n";
        return;
    }

    file >> pipe.name;
    file >> pipe.length;
    file >> pipe.diameter;
    file >> pipe.isRepair;

    file >> station.name;
    file >> station.worker_count;
    file >> station.worker_count_active;
    file >> station.station_class;

    if (file.fail()) {
        cout << "Ошибка чтения данных из файла.\n";
        return;
    }

    file.close();

    cout << "Данные загружены из файла.\n";
}