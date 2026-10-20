#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>

#include "cstation.hpp"
#include "utils.hpp"

using namespace std;

CompressStation::CompressStation(int id) : id(id) {}

int CompressStation::getId() const {
    return id;
}

const string& CompressStation::getName() const {
    return name;
}

double CompressStation::getUnusedPercent() const {
    if (worker_count == 0) {
        return 0;
    }
    return 100.0 * (worker_count - worker_count_active) / worker_count;
}

void CompressStation::startWorkstation() {
    if (worker_count == 0) {
        cout << "Компрессорная станция не создана\n";
        return;
    }

    if (worker_count_active < worker_count) {
        worker_count_active++;
        cerr << "Запущен цех КС ID " + to_string(id) << '\n';
    } else {
        cout << "Все цеха уже запущены\n";
        cerr << "Отказ: все цеха уже запущены" << '\n';
    }
}

void CompressStation::stopWorkstation() {
    if (worker_count == 0) {
        cout << "Компрессорная станция не создана\n";
        return;
    }

    if (worker_count_active > 0) {
        worker_count_active--;
        cerr << "Остановлен цех КС ID " + to_string(id) << '\n';
    } else {
        cout << "Все цеха уже остановлены\n";
        cerr << "Отказ: все цеха уже остановлены" << '\n';
    }
}

bool CompressStation::createCS() {
    cout << "Введите название КС: ";
    if (!inputString(name)) {
        return false;
    }

    cout << "Введите количество цехов: ";
    if (!inputInt(worker_count, 1)) {
        return false;
    }

    cout << "Введите количество работающих цехов: ";
    if (!inputInt(worker_count_active, 0, worker_count)) {
        return false;
    }

    cout << "Введите класс станции (1 или 2): ";
    return inputInt(station_class, 1, 2);
}

void CompressStation::printCS() const {
    cout << "------------------------------\n";
    cout << "ID: " << id << "\n";
    cout << "Название:            " << name << "\n";
    cout << "Всего цехов:         " << worker_count << "\n";
    cout << "Работающих цехов:    " << worker_count_active << "\n";
    cout << "Класс станции:       " << station_class << "\n";
    cout << "------------------------------\n";
}

void CompressStation::editCS() {
    if (name.empty()) {
        cout << "Компрессорная станция не создана\n";
        return;
    }

    cout << "5. Редактировать КС\n\n";

    cout << "1. Запустить цех\n"
         << "2. Остановить цех\n"
         << "0. Назад\n\n";

    cout << "Введите команду: ";
    int choice;
    if (!inputInt(choice, 0, 2)) {
        return;
    }

    if (choice == 1) {
        startWorkstation();

        cout << "Работающих цехов: "
             << worker_count_active
             << " из "
             << worker_count
             << "\n";

    } else if (choice == 2) {
        stopWorkstation();

        cout << "Работающих цехов: "
             << worker_count_active
             << " из "
             << worker_count
             << "\n";
    }
}

void CompressStation::saveCS(ofstream& file) const {
    file << id << "\n";
    file << name << "\n";
    file << worker_count << "\n";
    file << worker_count_active << "\n";
    file << station_class << "\n";
}

bool CompressStation::loadCS(ifstream& file) {
    CompressStation loaded;
    if (!readFileInt(file, loaded.id, 1, numeric_limits<int>::max() - 1) ||
        !readFileLine(file, loaded.name) || !validString(loaded.name) ||
        !readFileInt(file, loaded.worker_count, 1, numeric_limits<int>::max()) ||
        !readFileInt(file, loaded.worker_count_active, 0, loaded.worker_count) ||
        !readFileInt(file, loaded.station_class, 1, 2)) {
        return false;
    }
    *this = loaded;
    return true;
}

