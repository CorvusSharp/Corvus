//
// Created by corvussharp on 07.11.22.
//

#ifndef LABOCHKAOOP_CONTROLCONFIG_H
#define LABOCHKAOOP_CONTROLCONFIG_H

#include "../LOG/LogsInfo/Structs.h"
#include "map"
#include <fstream>
#include "sstream"
#include "vector"

class ControlConfig {
public:
    virtual void read_config() = 0;
    CONTROL get_key(char move);
    void check_config();
protected:
    std::map<CONTROL, char> empty_config = {
            {CONTROL::UP,    '\0'},
            {CONTROL::DOWN,  '\0'},
            {CONTROL::LEFT,  '\0'},
            {CONTROL::RIGHT, '\0'},
            {CONTROL::EXIT,  '\0'}
    };
    std::map<CONTROL, char> default_config = {
            {CONTROL::UP,    'w'},
            {CONTROL::DOWN,  's'},
            {CONTROL::LEFT,  'a'},
            {CONTROL::RIGHT, 'd'},
            {CONTROL::EXIT,  'e'}

    };
};

#endif //LABOCHKAOOP_CONTROLCONFIG_H
