//
// Created by corvussharp on 21.09.22.
//

#ifndef UNTITLED48_COMMANDREADER_H
#define UNTITLED48_COMMANDREADER_H

#include "../Persons/Person.h"
#include "iostream"
#include "../LOG/LogsInfo/Structs.h"
#include "../INPUT/ControlConfig.h"
#include "../INPUT/ControlFile.h"

class CommandReader : public Subject {

public:

    CommandReader();
    bool valid_arg(int a);

    void set_size();
    void print_death();
    void set_level();
    void set_output();
    void print_win();

    int get_height() const;
    int get_width() const;

    char get_sym() const;
    char field_choice();

    CONTROL get_step() const;
    CONTROL check_step();

    void set_config(ControlConfig *config);

    std::vector<LEVEL> get_levels();
    std::vector<OUTPUT> get_outputs();

private:
    ControlConfig *control_config;
    CONTROL step;
    int height, width;
    char sym;
    std::vector<OUTPUT> outputs;
    std::vector<LEVEL> levels;
};


#endif //UNTITLED48_COMMANDREADER_H
