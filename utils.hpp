#pragma once
#include <fstream>
#include <limits>
#include <string>

bool readInput(std::string& text);
bool validString(const std::string& value);
bool inputString(std::string& value);
bool inputInt(int& value, int minimum = std::numeric_limits<int>::min(), int maximum = std::numeric_limits<int>::max());
bool inputPercent(double& value, double minimum = 0);
bool readFileLine(std::ifstream& file, std::string& line);
bool readFileInt(std::ifstream& file, int& value, int minimum, int maximum);
