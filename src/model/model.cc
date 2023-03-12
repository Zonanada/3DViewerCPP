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
  std::cout << line << "\n";
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

// void Parser::recordIndex(std::string &line) {
//   std::string numStr;
//   bool met_index = false;
//   bool firstIndex = true;
//   int countIndexRecord = 0;
//   for (auto it = line.begin(); it != line.end(); it++) {
//     if (isNum(*it) && !met_index) {
//       numStr.push_back(*it);
//   } else if (!met_index && *it == '/') {
//       met_index = true;
//   } else if ((*it == ' ' || it + 1 == line.end()) && !numStr.empty()) {
//       met_index = false;
//       unsigned int pushNum = stoi(numStr) - 1;
//       if (firstIndex) {
//         indexes[it_indexes] = pushNum;
//         it_indexes++;
//         firstIndex = false;
//         countIndexRecord++;
//       } else {
//         indexes[it_indexes] = pushNum;
//         it_indexes++;
//         countIndexRecord++;
//         indexes[it_indexes] = pushNum;
//         it_indexes++;
//         countIndexRecord++;
//       }
//       numStr.clear();
//     }
//   }
//   indexes[it_indexes] = indexes[it_indexes - countIndexRecord];
//   it_indexes++;
// }

void Parser::recordIndex(std::string &line) {
  std::cout << line << "\n";
  std::vector <unsigned> nums;
  std::string numStr;
  bool firstIndex = true;
  int countIndexRecord = 0;
  for (unsigned i = 1; i < line.size(); i++) {
    if (line[i] != ' ') {
      numStr.push_back(line[i]);
    }
    if ((line[i] == ' ' || line[i] == '\r' || i+1 == line.size()) && !numStr.empty()) {
      nums.push_back(stoi(numStr) - 1);
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
  // indexes[it_indexes] = nums[0];
  // it_indexes++;

  // std::cout << numStr << "\n";
  // std::cout << "\n";
}

void Rendering::first_theard_copy() {
  for (unsigned i = 0; i < original_vertexes.size(); i+=2) {
    // std::cout << "1 поток\n";
    change_vertexes[i] = original_vertexes[i];
  }
}

void Rendering::second_theard_copy() {
  for (unsigned i = 1; i < original_vertexes.size(); i+=2) {
    // std::cout << "2 поток\n";
    change_vertexes[i] = original_vertexes[i];
  }
}

void Rendering::copy_original_vertex() {
  thread second_copy([&] {
    second_theard_copy();
  });
  first_theard_copy();

  second_copy.join();
}

void Rendering::first_theard_state() {
  for (unsigned int i = 0; i < change_vertexes.size(); i+=24) {
    apply_state_run(i);
  }
}

void Rendering::second_theard_state() {
  for (unsigned int i = 3; i < change_vertexes.size(); i+=24) {
    apply_state_run(i);
  }
}

void Rendering::third_theard_state() {
  for (unsigned int i = 6; i < change_vertexes.size(); i+=24) {
    apply_state_run(i);
  }
}

void Rendering::four_theard_state() {
  for (unsigned int i = 9; i < change_vertexes.size(); i+=24) {
    apply_state_run(i);
  }
}

void Rendering::fifth_theard_state() {
  for (unsigned int i = 12; i < change_vertexes.size(); i+=24) {
    apply_state_run(i);
  }
}

void Rendering::sixth_theard_state() {
  for (unsigned int i = 15; i < change_vertexes.size(); i+=24) {
    apply_state_run(i);
  }
}

void Rendering::seventh_theard_state() {
  for (unsigned int i = 18; i < change_vertexes.size(); i+=24) {
    apply_state_run(i);
  }
}

void Rendering::eighth_theard_state() {
  for (unsigned int i = 21; i < change_vertexes.size(); i+=24) {
    apply_state_run(i);
  }
}

void Rendering::apply_state() {
  copy_original_vertex();

  thread second_state([&] {
    second_theard_state();
  });

  thread third_state([&] {
    third_theard_state();
  });

  thread four_state([&] {
    four_theard_state();
  });

  thread fifth_state([&] {
    fifth_theard_state();
  });

  thread sixth_state([&] {
    sixth_theard_state();
  });

  thread seventh_state([&] {
    seventh_theard_state();
  });

  thread eighth_state([&] {
    eighth_theard_state();
  });

  first_theard_state();
  second_state.join();
  third_state.join();
  four_state.join();
  fifth_state.join();
  sixth_state.join();
  seventh_state.join();
  eighth_state.join();
  
}


void Rendering::apply_state_run(unsigned i) {
  rotate_by_x(i+1, i+2);
  rotate_by_y(i, i+2);
  rotate_by_z(i, i+1);
  scaling(i, i+1, i+2);
  transfer_by_x(i);
  transfer_by_y(i+1);
  transfer_by_z(i+2);
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
  change_vertexes[in_x] += state.transfer_by_x;
}

void Rendering::transfer_by_y(unsigned in_y) {
  change_vertexes[in_y] += state.transfer_by_y;
}

void Rendering::transfer_by_z(unsigned in_z) {
  change_vertexes[in_z] += state.transfer_by_z;
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
///////////////////////////////////////////

// matrix_t *s21_create_matrix(int rows, int columns) {
//   matrix_t *result = malloc(1 * sizeof(matrix_t));
//   double **row = malloc(rows * sizeof(double *));
//   double **ptrRow = row;
//   for (int i = 0; i < rows; i++) {
//     *ptrRow = calloc(columns, sizeof(double));
//     ptrRow++;
//   }
//   result->matrix = row;
//   result->rows = rows;
//   result->columns = columns;
//   return result;
// }

// void s21_remove_matrix(matrix_t *A) {
//   for (int i = 0; i < A->rows; i++) {
//     free(A->matrix[i]);
//   }
//   free(A->matrix);
//   free(A);
// }

// void s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
//   for (int i = 0; i < A->rows; i++) {
//     for (int j = 0; j < B->columns; j++) {
//       result->matrix[i][j] = 0;
//       for (int k = 0; k < B->rows; k++) {
//         result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
//       }
//     }
//   }
// }

// matrix_t *matrixOX(double align) {
//   matrix_t *OXMatrix = s21_create_matrix(4, 4);
//   OXMatrix->matrix[0][0] = 1;
//   OXMatrix->matrix[1][1] = cos(align);
//   OXMatrix->matrix[1][2] = -sin(align);
//   OXMatrix->matrix[2][1] = sin(align);
//   OXMatrix->matrix[2][2] = cos(align);
//   OXMatrix->matrix[3][3] = 1;
//   return OXMatrix;
// }

// matrix_t *matrixOY(double align) {
//   matrix_t *OYMatrix = s21_create_matrix(4, 4);
//   OYMatrix->matrix[0][0] = cos(align);
//   OYMatrix->matrix[0][2] = sin(align);
//   OYMatrix->matrix[1][1] = 1;
//   OYMatrix->matrix[2][0] = -sin(align);
//   OYMatrix->matrix[2][2] = cos(align);
//   OYMatrix->matrix[3][3] = 1;
//   return OYMatrix;
// }

// matrix_t *matrixOZ(double align) {
//   matrix_t *OZMatrix = s21_create_matrix(4, 4);
//   OZMatrix->matrix[0][0] = cos(align);
//   OZMatrix->matrix[0][1] = -sin(align);
//   OZMatrix->matrix[1][0] = sin(align);
//   OZMatrix->matrix[1][1] = cos(align);
//   OZMatrix->matrix[2][2] = 1;
//   OZMatrix->matrix[3][3] = 1;
//   return OZMatrix;
// }

// matrix_t *scaling(double scale) {
//   matrix_t *scaleMatrix = s21_create_matrix(4, 4);
//   scaleMatrix->matrix[0][0] = scale;
//   scaleMatrix->matrix[1][1] = scale;
//   scaleMatrix->matrix[2][2] = scale;
//   scaleMatrix->matrix[3][3] = 1;
//   return scaleMatrix;
// }

// matrix_t *countMatrix(state_st *state) {
//   matrix_t *OXMatrix = matrixOX(state->rx);
//   matrix_t *OYMatrix = matrixOY(state->ry);
//   matrix_t *OZMatrix = matrixOZ(state->rz);
//   matrix_t *scaleMaitrix = scaling(state->scale);
//   matrix_t *resultXY = s21_create_matrix(4, 4);
//   matrix_t *resultXYZ = s21_create_matrix(4, 4);
//   matrix_t *resultXYZScale = s21_create_matrix(4, 4);
//   matrix_t *resultMatrix = s21_create_matrix(4, 4);

//   s21_mult_matrix(OXMatrix, OYMatrix, resultXY);
//   s21_mult_matrix(resultXY, OZMatrix, resultXYZ);
//   s21_mult_matrix(resultXYZ, scaleMaitrix, resultMatrix);

//   s21_remove_matrix(OXMatrix);
//   s21_remove_matrix(OYMatrix);
//   s21_remove_matrix(OZMatrix);
//   s21_remove_matrix(scaleMaitrix);
//   s21_remove_matrix(resultXY);
//   s21_remove_matrix(resultXYZ);
//   s21_remove_matrix(resultXYZScale);

//   return resultMatrix;
// }


// void stateСhange(vertex_st *vertex, state_st *state) {
//   matrix_t *resultMatrix = countMatrix(state);
//   double *ptr = vertex->arr;
//   double *ptrN = vertex->arrNoChange;
//   matrix_t *vert = s21_create_matrix(4, 1);
//   matrix_t *result = s21_create_matrix(4, 1);

//   for (int i = 0; i < vertex->memory / 3; i++) {
//     double *temp_x = ptr;
//     double *temp_xN = ptrN;
//     ptr++;
//     ptrN++;
//     double *temp_y = ptr;
//     double *temp_yN = ptrN;
//     ptr++;
//     ptrN++;
//     double *temp_z = ptr;
//     double *temp_zN = ptrN;
//     ptr++;
//     ptrN++;

//     vert->matrix[0][0] = *temp_xN;
//     vert->matrix[1][0] = *temp_yN;
//     vert->matrix[2][0] = *temp_zN;

//     s21_mult_matrix(resultMatrix, vert, result);

//     *temp_x = result->matrix[0][0] + state->tx;
//     *temp_y = result->matrix[1][0] + state->ty;
//     *temp_z = result->matrix[2][0];
//   }
//   free(state);
//   s21_remove_matrix(result);
//   s21_remove_matrix(vert);
//   s21_remove_matrix(resultMatrix);
// }