#pragma once
#include <map>
#include <set>
#include <fstream>
#include <string>
#include "pipe.hpp"
#include "cstation.hpp"

int inputId(const std::map<int, Pipe>& pipes);
int inputId(const std::map<int, CompressStation>& stations);
void showObjects(const std::map<int, Pipe>& pipes, const std::map<int, CompressStation>& stations);
std::set<int> findPipes(const std::map<int, Pipe>& pipes);
void findCS(const std::map<int, CompressStation>& stations);
void editPipes(std::map<int, Pipe>& pipes);
void saveFile(const std::map<int, Pipe>& pipes, const std::map<int, CompressStation>& stations, int nextId, const std::string& logFileName);
void loadFile(std::map<int, Pipe>& pipes, std::map<int, CompressStation>& stations, int& nextId);

