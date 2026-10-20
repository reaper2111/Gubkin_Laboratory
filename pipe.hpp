#pragma once
#include <string>
#include <fstream>

class Pipe {
private:
    int id = 0;
    int diameter = 0, length = 0;
    std::string name;
    bool isRepair = false;

public:
    explicit Pipe(int id = 0);
    int getId() const;
    const std::string& getName() const;
    bool getRepairStatus() const;

    bool createPipe();
    void printPipe() const;
    void editPipe();
    void setRepairStatus(bool status);
    void savePipe(std::ofstream& file) const;
    bool loadPipe(std::ifstream& file);
};
