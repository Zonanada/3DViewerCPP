#include "parser.h"

int Parser::isNum(char symbol) {
  return (symbol >= '0' && symbol <= '9') || symbol == ',' || symbol == '.' ||
         symbol == '-' || symbol == '+';
}

int Parser::countIndexInLine(std::string &line) {
  int countIndex = 0;
  bool met_index = false;
  for (auto it = line.begin(); it != line.end(); it++) {
      if (isNum(*it) && !met_index) {
        countIndex++;
        met_index = true;
      }
      if (met_index && *it == ' ') {
        met_index = false;
      }
  }
  return countIndex;
}

void Parser::reading() {
    unsigned int countVertex = 0;
    unsigned int countIndex = 0;
    std::string line;
    std::ifstream in(filename);
    if (in.is_open()) {
        while (getline(in, line)) {
            if (line[0] == 'v' && line[1] == ' ') {
                countVertex++;
            }
            if (line[0] == 'f' && line[1] == ' ') {
                countIndex += countIndexInLine(line);
            }
        }
        in.close();
    } else {
        throw std::out_of_range(
        "File not found!");
    }

    vertexes.resize(countVertex * 3);
    indexes.resize(countIndex * 2);
}

void Parser::record() {
    std::string line;
    std::ifstream in(filename);
    it_vertexes = 0;
    it_indexes = 0;
    vertex_max = 0;

    if (in.is_open()) {
        while (getline(in, line)) {
        if (line[0] == 'v' && line[1] == ' ') {
            recordVertex(line);
        }
        if (line[0] == 'f' && line[1] == ' ') {
            recordIndex(line);
        }
    }
    int coeff = vertex_max / 1;
    for (auto it = vertexes.begin(); it != vertexes.end(); it++) {
        *it /= coeff;
    }

    } else {
        throw std::out_of_range(
        "File not found!");
    }
}

void Parser::recordVertex(std::string &line) {
  std::string numStr;
  for (unsigned i = 1; i < line.size(); i++) {
    if (isNum(line[i])){
      numStr.push_back(line[i]);
    }
    if ((line[i] == ' ' || i+1 == line.size() || line[i+1] == '\r' ) && !numStr.empty()) {
      vertexes[it_vertexes] = stod(numStr);
      if (abs(vertexes[it_vertexes]) > vertex_max) vertex_max = vertexes[it_vertexes];
      it_vertexes++;
      numStr.clear();
    }
  }
}


void Parser::recordIndex(std::string &line) {
  std::vector <unsigned> nums;
  std::string numStr;
  bool firstIndex = true;
  int countIndexRecord = 0;
  for (unsigned i = 1; i < line.size(); i++) {
    if (line[i] != ' ' ) {
      numStr.push_back(line[i]);
    }
  if ((line[i] == ' ' || line[i+1] == '\r' || i+1 == line.size()) && !numStr.empty()) {
    if (numStr[0] != ' ' && numStr[0] != '\r') {
      nums.push_back(stoi(numStr) - 1);
    }
      numStr.clear();
    }
  }
  indexes[it_indexes] = nums[0];
  indexes[it_indexes + (nums.size() * 2 - 1)] = nums[0];
  it_indexes++;
  for (unsigned i = 1; i < nums.size(); i++) {
      indexes[it_indexes] = nums[i];
      indexes[it_indexes+1] = nums[i];
      it_indexes+=2;
  }
  it_indexes++;
}