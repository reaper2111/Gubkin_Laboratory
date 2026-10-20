#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cmath>

#include "pipe.hpp"
#include "utils.hpp"

using namespace std;

Pipe::Pipe(int id) : id(id) {}

int Pipe::getId() const {
    return id;
}

const string& Pipe::getName() const {
    return name;
}

bool Pipe::getRepairStatus() const {
    return isRepair;
}

void Pipe::setRepairStatus(bool status) {
    isRepair = status;
    cerr << "Труба ID " << id << ", ремонт: " << status << '\n';
}

bool Pipe::createPipe() {
    cout << "Введите название трубы: ";
    if (!inputString(name)) {
        return false;
    }

    cout << "Введите длину трубы: ";
    if (!inputInt(length, 1)) {
        return false;
    }

    cout << "Введите диаметр трубы: ";
    if (!inputInt(diameter, 1)) {
        return false;
    }

    int repairStatus;
    cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    if (!inputInt(repairStatus, 0, 1)) {
        return false;
    }
    isRepair = repairStatus;
    return true;
}

void Pipe::printPipe() const {
    cout << "------------------------------\n";
    cout << "ID: " << id << "\n";
    cout << "Название: " << name << "\n";
    cout << "Диаметр:  " << diameter << "\n";
    cout << "Длина:    " << length << "\n";
    cout << "Ремонт:   " << (isRepair ? "Да" : "Нет") << "\n";
    cout << "------------------------------\n";
}

void Pipe::editPipe() {
    if (name.empty()) {
        cout << "Труба не создана\n";
        return;
    }

    cout << "4. Редактировать трубу\n\n";

    cout << "1. Установить: в ремонте\n"
         << "2. Установить: не в ремонте\n"
         << "0. Назад\n\n";

    cout << "Введите команду: ";
    int choice;
    if (!inputInt(choice, 0, 2)) {
        return;
    }

    if (choice == 1) {
        setRepairStatus(true);
        cout << "Статус трубы: в ремонте\n";

    } else if (choice == 2) {
        setRepairStatus(false);
        cout << "Статус трубы: не в ремонте\n";
    }
}

void Pipe::savePipe(ofstream& file) const {
    file << id << "\n";
    file << name << "\n";
    file << length << "\n";
    file << diameter << "\n";
    file << isRepair << "\n";
}

bool Pipe::loadPipe(ifstream& file) {
    Pipe loaded;
    int repairStatus;
    if (!readFileInt(file, loaded.id, 1, numeric_limits<int>::max() - 1) ||
        !readFileLine(file, loaded.name) || !validString(loaded.name) ||
        !readFileInt(file, loaded.length, 1, numeric_limits<int>::max()) ||
        !readFileInt(file, loaded.diameter, 1, numeric_limits<int>::max()) ||
        !readFileInt(file, repairStatus, 0, 1)) {
        return false;
    }
    loaded.isRepair = repairStatus;
    *this = loaded;
    return true;
}

