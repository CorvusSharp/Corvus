//
// Created by corvussharp on 21.09.22.
//

#ifndef UNTITLED48_COMMANDREADER_H
#define UNTITLED48_COMMANDREADER_H

#include "../Persons/Person.h"
#include "iostream"

class CommandReader : public Subject {

public:
    void set_size();
    void check_step();
    int arg_error();

    bool valid_arg(int a);
    void print_death();
    int get_height() const;
    int get_width() const;
    void print_win();

    char input_sym(char &sym);
    char get_sym() const;
    char field_choice();

    void set_output();
    void set_level();
    Person::STEP get_step() const;

    bool set_move(LogOutInfo *info);

    enum MOVES {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NOWHERE
    };

    MOVES get_move();

    std::vector<LEVEL> get_levels();

    std::vector<OUTPUT> get_outputs();

private:
    Person::STEP step;
    int height, width;
    char sym;
    MOVES move;
    std::vector<OUTPUT> outputs;
    std::vector<LEVEL> levels;
};


#endif //UNTITLED48_COMMANDREADER_H
