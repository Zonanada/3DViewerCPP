#include "model.h"



void Rendering::first_theard_copy() {
  for (unsigned i = 0; i < original_vertexes.size(); i+=2) {
    change_vertexes[i] = original_vertexes[i];
  }
}

void Rendering::second_theard_copy() {
  for (unsigned i = 1; i < original_vertexes.size(); i+=2) {
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

void Rendering::set_projection(bool have_or_not) {
  projection = have_or_not;
  if (projection) {
    offset_along_z = -5;
  } else {
    offset_along_z = 0;
  }
  apply_state();
}

bool Rendering::get_projection() {
  return projection;
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
  change_vertexes[in_z] += (state.transfer_by_z + offset_along_z);
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