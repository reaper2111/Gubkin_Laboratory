#pragma once

#include <string>
#include <fstream>

struct Pipe {
    int diameter, length;
    std::string name;
    bool isRepair;
};

struct CompressStation {
    std::string name;
    int worker_count, worker_count_active;
    int station_class;
};

int inputInt();

void startWorkstation(CompressStation& station);

void stopWorkstation(CompressStation& station);

void setRepairStatus(Pipe& pipe, bool status);

void createPipe(Pipe& pipe);

void createCS(CompressStation& station);

void printPipe(const Pipe& pipe);

void printCS(const CompressStation& station);

void showObjects(const Pipe& pipe, const CompressStation& station);

void editPipe(Pipe& pipe);

void editCS(CompressStation& station);

void saveFile(const Pipe& pipe, const CompressStation& station);

void loadFile(Pipe& pipe, CompressStation& station);

void savePipe(std::ofstream& file, const Pipe& pipe);

void saveCS(std::ofstream& file, const CompressStation& station);

void loadPipe(std::ifstream& file, Pipe& pipe);

void loadCS(std::ifstream& file, CompressStation& station);