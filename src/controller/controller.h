#ifndef SRC_CONTROLLER_CONTROLLER_H
#define SRC_CONTROLLER_CONTROLLER_H

#include "../model/model.h"

class Controller {
    public:
        Controller() : rendering(new Rendering){};
        void parse_filename(std::string filename) {
            return rendering->parse_filename(filename);
        }
        void set_state(State input_state) {
            return rendering->set_state(input_state);
        }
        std::vector <double> &get_vertexes(){
            return rendering->get_vertexes();
        }
        std::vector <unsigned int> &get_indexes() {
            return rendering->get_indexes();
        }

        ~Controller(){
            delete rendering;
        }

    private:
        Rendering *rendering;
};

#endif