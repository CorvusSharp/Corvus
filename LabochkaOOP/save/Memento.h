//
// Created by corvussharp on 23.12.22.
//

#ifndef LABOCHKAOOP_MEMENTO_H
#define LABOCHKAOOP_MEMENTO_H


#include <string>


class Memento {
public:
    void saveState(const std::string&, const std::string&);
    std::string restoreState(const std::string&);
};


#endif //LABOCHKAOOP_MEMENTO_H
