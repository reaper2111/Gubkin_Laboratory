#pragma once
#include <string>
#include <fstream>

class CompressStation {
private:
    int id = 0;
    std::string name;
    int worker_count = 0, worker_count_active = 0;
    int station_class = 0;

public:
    explicit CompressStation(int id = 0);
    int getId() const;
    const std::string& getName() const;
    double getUnusedPercent() const;

    bool createCS();
    void printCS() const;
    void editCS();
    void startWorkstation();
    void stopWorkstation();
    void saveCS(std::ofstream& file) const;
    bool loadCS(std::ifstream& file);
};
