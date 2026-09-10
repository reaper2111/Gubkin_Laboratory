#include <iostream>
#include <fstream>
#include "objects.hpp"

using namespace std;

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

void setRepairStatus(Pipe& pipe, bool status) {
    pipe.isRepair = status;
}

void createPipe(Pipe& pipe) {
    cout << "Введите название трубы: ";
    cin >> pipe.name;

    cout << "Введите длину трубы: ";
    cin >> pipe.length;

    while (pipe.length <= 0) {
        cout << "Ошибка. Длина должна быть больше 0: ";
        cin >> pipe.length;
    }

    cout << "Введите диаметр трубы: ";
    cin >> pipe.diameter;

    while (pipe.diameter <= 0) {
        cout << "Ошибка. Диаметр должен быть больше 0: ";
        cin >> pipe.diameter;
    }

    int repairStatus;

    cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    cin >> repairStatus;

    while (repairStatus != 0 && repairStatus != 1) {
        cout << "Ошибка. Введите 0 или 1: ";
        cin >> repairStatus;
    }

    pipe.isRepair = repairStatus;
}

void createCS(CompressStation& station) {
    cout << "Введите название КС: ";
    cin >> station.name;

    cout << "Введите количество цехов: ";
    cin >> station.worker_count;

    while (station.worker_count <= 0) {
        cout << "Ошибка. Количество цехов должно быть больше 0: ";
        cin >> station.worker_count;
    }

    cout << "Введите количество работающих цехов: ";
    cin >> station.worker_count_active;

    while (
        station.worker_count_active < 0 ||
        station.worker_count_active > station.worker_count
    ) {
        cout << "Ошибка. Работающих цехов должно быть от 0 до "
            << station.worker_count << ": ";

        cin >> station.worker_count_active;
    }

    cout << "Введите класс станции: ";
    cin >> station.station_class;

    while (station.station_class <= 0 && station.station_class > 2) {
        cout << "Ошибка. Класс станции должен быть 1 или 2: ";
        cin >> station.station_class;
    }
}

void printPipe(const Pipe& pipe) { 
    cout << "------------------------------\n";
    cout << "Название: " << pipe.name << "\n";
    cout << "Диаметр:  " << pipe.diameter << "\n";
    cout << "Длина:    " << pipe.length << "\n";
    cout << "Ремонт:   " << (pipe.isRepair ? "Да" : "Нет") << "\n";
    cout << "------------------------------\n";
}

void printCS(const CompressStation& station) {
    cout << "------------------------------\n";
    cout << "Название:            " << station.name << "\n";
    cout << "Всего цехов:         " << station.worker_count << "\n";
    cout << "Работающих цехов:    " << station.worker_count_active << "\n";
    cout << "Класс станции:       " << station.station_class << "\n";
    cout << "------------------------------\n";
}

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

    file.close();

    cout << "Данные загружены из файла.\n";
}