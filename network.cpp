#include "network.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>
#include <filesystem>

using namespace std;

static bool isLogFile(const string& path, const string& logFileName) {
    error_code error;
    bool same = filesystem::equivalent(path, logFileName, error);
    return !error && same;
}

int inputId(const map<int, Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "Трубы не созданы\n";
        return 0;
    }
    for (const auto& item : pipes) {
        cout << "ID: " << item.first << " | " << item.second.getName() << "\n";
    }
    cout << "Введите ID (0 - назад): ";
    int id;
    while (inputInt(id, 0)) {
        if (id == 0 || pipes.count(id)) return id;
        cout << "Такого ID нет. Введите ID (0 - назад): ";
    }
    return 0;
}

int inputId(const map<int, CompressStation>& stations) {
    if (stations.empty()) {
        cout << "КС не созданы\n";
        return 0;
    }
    for (const auto& item : stations) {
        cout << "ID: " << item.first << " | " << item.second.getName() << "\n";
    }
    cout << "Введите ID (0 - назад): ";
    int id;
    while (inputInt(id, 0)) {
        if (id == 0 || stations.count(id)) return id;
        cout << "Такого ID нет. Введите ID (0 - назад): ";
    }
    return 0;
}

void showObjects(const map<int, Pipe>& pipes, const map<int, CompressStation>& stations) {
    cerr << "Просмотр всех объектов" << '\n';
    if (pipes.empty()) {
        cout << "Трубы не созданы\n";
    }
    for (const auto& item : pipes) {
        item.second.printPipe();
    }

    if (stations.empty()) {
        cout << "Компрессорные станции не созданы\n";
    }
    for (const auto& item : stations) {
        item.second.printCS();
    }
}


set<int> findPipes(const map<int, Pipe>& pipes) {
    set<int> found;
    if (pipes.empty()) {
        cout << "Трубы не созданы\n";
        return found;
    }

    cout << "1. По названию\n2. По признаку ремонта\n0. Назад\nВведите команду: ";
    int choice;
    if (!inputInt(choice, 0, 2) || choice == 0) {
        return found;
    }

    string name;
    int repairStatus = 0;
    if (choice == 1) {
        cout << "Введите название или его часть (с учётом регистра): ";
        if (!inputString(name)) {
            return found;
        }
    } else {
        cout << "Труба в ремонте? (1 - да, 0 - нет): ";
        if (!inputInt(repairStatus, 0, 1)) {
            return found;
        }
    }

    for (const auto& item : pipes) {
        const Pipe& pipe = item.second;
        if ((choice == 1 && pipe.getName().find(name) != string::npos) ||
            (choice == 2 && pipe.getRepairStatus() == repairStatus)) {
            found.insert(pipe.getId());
            pipe.printPipe();
        }
    }

    cerr << "Поиск труб, найдено: " + to_string(found.size()) << '\n';
    cout << "Найдено труб: " << found.size() << "\n";
    return found;
}


void findCS(const map<int, CompressStation>& stations) {
    if (stations.empty()) {
        cout << "Компрессорные станции не созданы\n";
        return;
    }

    cout << "1. По названию\n2. По проценту незадействованных цехов\n0. Назад\nВведите команду: ";
    int choice;
    if (!inputInt(choice, 0, 2) || choice == 0) {
        return;
    }

    string name;
    double minimum = 0, maximum = 100;
    if (choice == 1) {
        cout << "Введите название или его часть (с учётом регистра): ";
        if (!inputString(name)) {
            return;
        }
    } else {
        cout << "Введите минимальный процент: ";
        if (!inputPercent(minimum)) {
            return;
        }
        cout << "Введите максимальный процент: ";
        if (!inputPercent(maximum, minimum)) {
            return;
        }
    }

    int count = 0;
    for (const auto& item : stations) {
        const CompressStation& station = item.second;
        double percent = station.getUnusedPercent();
        if ((choice == 1 && station.getName().find(name) != string::npos) ||
            (choice == 2 && percent >= minimum && percent <= maximum)) {
            station.printCS();
            cout << "Незадействованных цехов: " << percent << "%\n";
            count++;
        }
    }
    cerr << "Поиск КС, найдено: " + to_string(count) << '\n';
    cout << "Найдено КС: " << count << "\n";
}


set<int> selectPipes(const set<int>& found) {
    cout << "1. Все найденные\n2. Выбрать по ID\n0. Назад\nВведите команду: ";
    int choice;
    if (!inputInt(choice, 0, 2) || choice == 0) {
        return {};
    }
    if (choice == 1) {
        return found;
    }

    while (true) {
        cout << "Введите ID через пробел (0 - назад): ";
        string text;
        if (!readInput(text)) {
            return {};
        }
        istringstream line(text);
        set<int> selected;
        bool valid = true;
        line >> ws;
        while (!line.eof()) {
            int id;
            if (!(line >> id)) {
                valid = false;
                break;
            }
            if (id == 0 && selected.empty() && (line >> ws).eof()) {
                return {};
            }
            if (found.find(id) == found.end() || !selected.insert(id).second) {
                valid = false;
                break;
            }
            if (!line.eof() && line.peek() != ' ' && line.peek() != '\t') {
                valid = false;
                break;
            }
            line >> ws;
        }
        if (valid && !selected.empty()) {
            return selected;
        }
        cerr << "Ошибка выбора набора труб" << '\n';
        cout << "Ошибка. Укажите только найденные ID, без повторов и лишних символов\n";
    }
}


void editPipes(map<int, Pipe>& pipes) {
    set<int> found = findPipes(pipes);
    if (found.empty()) {
        return;
    }
    set<int> selected = selectPipes(found);
    if (selected.empty()) {
        return;
    }

    cout << "1. Установить: в ремонте\n"
         << "2. Установить: не в ремонте\n"
         << "3. Удалить\n"
         << "0. Назад\nВведите команду: ";
    int choice;
    if (!inputInt(choice, 0, 3) || choice == 0) {
        return;
    }

    for (int id : selected) {
        if (choice == 3) {
            pipes.erase(id);
            cerr << "Пакетное удаление трубы ID " + to_string(id) << '\n';
        } else {
            pipes.at(id).setRepairStatus(choice == 1);
        }
    }
    cout << "Обработано труб: " << selected.size() << "\n";
}


void saveFile(const map<int, Pipe>& pipes, const map<int, CompressStation>& stations, int nextId, const string& logFileName) {
    cout << "Введите имя файла: ";
    string filename;
    if (!inputString(filename)) {
        return;
    }
    if (isLogFile(filename, logFileName)) {
        cout << "Ошибка. Нельзя сохранять данные в журнал\n";
        cerr << "Отказ: попытка перезаписи журнала" << '\n';
        return;
    }
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла.\n";
        cerr << "Ошибка открытия файла: " + filename << '\n';
        return;
    }

    file << "LAB2\n" << nextId << "\n";
    file << pipes.size() << "\n";
    for (const auto& item : pipes) {
        item.second.savePipe(file);
    }
    file << stations.size() << "\n";
    for (const auto& item : stations) {
        item.second.saveCS(file);
    }
    file.close();
    if (file.fail()) {
        cout << "Ошибка записи данных в файл.\n";
        cerr << "Ошибка записи: " + filename << '\n';
        return;
    }
    cout << "Данные сохранены в файл.\n";
    cerr << "Данные сохранены: " + filename << '\n';
}


bool readObjects(ifstream& file, map<int, Pipe>& pipes, map<int, CompressStation>& stations, int& nextId) {
    string version;
    int count;
    if (!readFileLine(file, version) || version != "LAB2" ||
        !readFileInt(file, nextId, 1, numeric_limits<int>::max()) ||
        !readFileInt(file, count, 0, numeric_limits<int>::max())) {
        return false;
    }

    for (int i = 0; i < count; i++) {
        Pipe pipe{};
        if (!pipe.loadPipe(file) || pipe.getId() >= nextId || !pipes.emplace(pipe.getId(), pipe).second) {
            return false;
        }
    }

    if (!readFileInt(file, count, 0, numeric_limits<int>::max())) {
        return false;
    }
    for (int i = 0; i < count; i++) {
        CompressStation station{};
        if (!station.loadCS(file) || station.getId() >= nextId || pipes.find(station.getId()) != pipes.end() ||
            !stations.emplace(station.getId(), station).second) {
            return false;
        }
    }

    file >> ws;
    return file.eof() && !file.bad();
}


void loadFile(map<int, Pipe>& pipes, map<int, CompressStation>& stations, int& nextId) {
    cout << "Введите имя файла: ";
    string filename;
    if (!inputString(filename)) {
        return;
    }
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла.\n";
        cerr << "Ошибка открытия файла: " + filename << '\n';
        return;
    }

    map<int, Pipe> loadedPipes;
    map<int, CompressStation> loadedStations;
    int loadedNextId;
    if (!readObjects(file, loadedPipes, loadedStations, loadedNextId)) {
        cout << "Ошибка чтения данных из файла. Текущие данные сохранены.\n";
        cerr << "Отклонён некорректный файл: " + filename << '\n';
        return;
    }

    pipes.swap(loadedPipes);
    stations.swap(loadedStations);
    if (loadedNextId > nextId) {
        nextId = loadedNextId;
    }
    cout << "Данные загружены из файла.\n";
    cerr << "Данные загружены: " + filename << '\n';
}

