#include "model.h"


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

void Rendering::copy_original_vertex() {
  for (unsigned i = 0; i < original_vertexes.size(); i++) {
    change_vertexes[i] = original_vertexes[i];
  }
}


void Rendering::apply_state() {
  copy_original_vertex();
  for (unsigned int i = 0; i < change_vertexes.size(); i+=3) {
      rotate_by_x(i+1, i+2);
      rotate_by_y(i, i+2);
      rotate_by_z(i, i+1);
      // scaling(i, i+1, i+2);
      // transfer_by_x(i);
      // transfer_by_y(i+1);
      // transfer_by_z(i+2);
  }
  // output_vertex(change_vertexes);
}

void Rendering::rotate_by_x(unsigned in_y, unsigned in_z) {
  double tmp_value_y = change_vertexes[in_y];
  double tmp_value_z = change_vertexes[in_z];
  change_vertexes[in_y] = tmp_value_y * cos(state.rotate_by_x) + tmp_value_z * sin(state.rotate_by_x);
  change_vertexes[in_z] = tmp_value_z * cos(state.rotate_by_x) - tmp_value_y * sin(state.rotate_by_x);
}

void Rendering::rotate_by_y(unsigned in_x, unsigned in_z) {
  double tmp_value_x = change_vertexes[in_x];
  double tmp_value_z = change_vertexes[in_z];
  change_vertexes[in_x] = tmp_value_x * cos(state.rotate_by_y) + tmp_value_z * sin(state.rotate_by_y);
  change_vertexes[in_z] = tmp_value_z * cos(state.rotate_by_y) - tmp_value_x * sin(state.rotate_by_y);
}

void Rendering::rotate_by_z(unsigned in_x, unsigned in_y) {
  double tmp_value_x = change_vertexes[in_x];
  double tmp_value_y = change_vertexes[in_y];
  change_vertexes[in_x] = tmp_value_x * cos(state.rotete_by_z) + tmp_value_y * sin(state.rotete_by_z);
  change_vertexes[in_y] = tmp_value_y * cos(state.rotete_by_z) - tmp_value_x * sin(state.rotete_by_z);
}

void Rendering::scaling(unsigned in_x, unsigned in_y, unsigned in_z) {
  change_vertexes[in_x] *= state.scale;
  change_vertexes[in_y] *= state.scale;
  change_vertexes[in_z] *= state.scale;
}

void Rendering::transfer_by_x(unsigned in_x) {
  change_vertexes[in_x] *= state.transfer_by_x;
}

void Rendering::transfer_by_y(unsigned in_y) {
  change_vertexes[in_y] *= state.transfer_by_y;
}

void Rendering::transfer_by_z(unsigned in_z) {
  change_vertexes[in_z] *= state.transfer_by_z;
}

std::vector <double> &Rendering::get_vertexes() {
  return change_vertexes;
}

std::vector <unsigned int> &Rendering::get_indexes() {
  return parser.get_indexes();
}

void Rendering::parse_filename(std::string filename) {
  parser.parse_filename(filename);
  change_vertexes = parser.get_vertexes();
}

void Rendering::set_state(State input_state) {
  state = input_state;
  apply_state();
}

void Rendering::output_vertex(std::vector <double> &nums) {
    for (auto it : nums) {
        std::cout << it << " "; 
    }
    std::cout << "\n";
}
