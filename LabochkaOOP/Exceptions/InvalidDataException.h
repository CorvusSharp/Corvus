//
// Created by corvussharp on 23.12.22.
//

#ifndef LABOCHKAOOP_INVALIDDATAEXCEPTION_H
#define LABOCHKAOOP_INVALIDDATAEXCEPTION_H


#include "GameException.h"

class InvalidDataException : public GameException {
public:
    using GameException::GameException;

    std::string what() final;
};


#endif //LABOCHKAOOP_INVALIDDATAEXCEPTION_H
