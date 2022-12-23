//
// Created by corvussharp on 17.12.22.
//

#ifndef LABOCHKAOOP_OPENFILEEXCEPTION_H
#define LABOCHKAOOP_OPENFILEEXCEPTION_H


#include <string>
#include "GameException.h"

class OpenFileException: public GameException{
public:
    using GameException::GameException;
    std::string what() override;
};




#endif //LABOCHKAOOP_OPENFILEEXCEPTION_H
