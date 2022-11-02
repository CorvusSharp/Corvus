//
// Created by corvussharp on 01.11.22.
//

#ifndef LABOCHKAOOP_INPUTFILE_H
#define LABOCHKAOOP_INPUTFILE_H

#include "Input.h"

class InputFile: public Input{
    void input() override;
private:
    std::string s;
    std::stringstream ss;
    std::vector<std::string> v;
};


#endif //LABOCHKAOOP_INPUTFILE_H
