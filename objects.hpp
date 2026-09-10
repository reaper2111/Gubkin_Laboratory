#pragma once

#include <string>

using namespace std;

struct Pipe {
    int diameter, length;
    string name;
    bool isRepair;
};

struct CompressStation {
    string name;
    int worker_count, worker_count_active;
    int station_class;
};

void startWorkstation(CompressStation& station);

void stopWorkstation(CompressStation& station);

void setRepairStatus(Pipe& pipe, bool status);

void createPipe(Pipe& pipe);

void createCSStation(CompressStation& station);

void printPipe(const Pipe& pipe);

void printCSstation(const CompressStation& station);

void saveFile(const Pipe& pipe, const CompressStation& station);

void loadFile(Pipe& pipe, CompressStation& station);

