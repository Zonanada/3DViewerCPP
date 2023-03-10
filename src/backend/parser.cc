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

    if (in.is_open()) {
        while (getline(in, line)) {
        if (line[0] == 'v' && line[1] == ' ') {
            recordVertex(line);
        }
        if (line[0] == 'f' && line[1] == ' ') {
            recordIndex(line);
        }
    }
    int coeff = vertex_max / 0.5;
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
  for (auto it = line.begin(); it != line.end(); it++) {
    if (isNum(*it)) {
      numStr.push_back(*it);
    } else if (*it == ' '  && !numStr.empty()) {
      vertexes[it_vertexes] = stod(numStr);
      if (abs(vertexes[it_vertexes]) > vertex_max) vertex_max = vertexes[it_vertexes];
      it_vertexes++;
      numStr.clear();
    }
  }
  vertexes[it_vertexes] = stod(numStr);
  it_vertexes++;
}

void Parser::recordIndex(std::string &line) {
  std::string numStr;
  bool met_index = false;
  bool firstIndex = true;
  int countIndexRecord = 0;
  for (auto it = line.begin(); it != line.end(); it++) {
    if (isNum(*it) && !met_index) {
      numStr.push_back(*it);
  } else if (!met_index && *it == '/') {
      met_index = true;
  } else if ((*it == ' ' || it + 1 == line.end()) && !numStr.empty()) {
      met_index = false;
      unsigned int pushNum = stoi(numStr) - 1;
      
      if (firstIndex) {
        indexes[it_indexes] = pushNum;
        it_indexes++;
        firstIndex = false;
        countIndexRecord++;
      } else {
        indexes[it_indexes] = pushNum;
        it_indexes++;
        countIndexRecord++;
        indexes[it_indexes] = pushNum;
        it_indexes++;
        countIndexRecord++;
      }
      numStr.clear();
    }
  }
  indexes[it_indexes] = indexes[it_indexes - countIndexRecord];
  it_indexes++;
}
