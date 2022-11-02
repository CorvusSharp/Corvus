//
// Created by corvussharp on 01.11.22.
//

#ifndef LABOCHKAOOP_INPUT_H
#define LABOCHKAOOP_INPUT_H

#endif //LABOCHKAOOP_INPUT_H

#include <sstream>
#include "fstream"
#include "vector"
#include "iostream"

class Input{
public:
    virtual  ~Input() = default;
    virtual void input() = 0;
};