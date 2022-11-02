//
// Created by corvussharp on 01.11.22.
//


#include "InputFile.h"


void InputFile::input() {
    std::ifstream ifs("input.txt");
    if(ifs.is_open()){
    }
    while (std::getline(ifs, s)){
        ss.str(s);
        while (ss>>s){
            v.push_back(s);
        }
        for (auto const &val : v) {
            std::cout<< val;
            v.clear();
            ss.clear();
        }
        ifs.close();
    }
}
