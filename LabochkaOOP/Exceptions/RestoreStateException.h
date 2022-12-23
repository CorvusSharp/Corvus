//
// Created by corvussharp on 17.12.22.
//

#ifndef LABOCHKAOOP_RESTORESTATEEXCEPTION_H
#define LABOCHKAOOP_RESTORESTATEEXCEPTION_H



#include "GameException.h"

class RestoreStateException: public GameException{
public:
    using GameException::GameException;
    std::string what() override;

};



#endif //LABOCHKAOOP_RESTORESTATEEXCEPTION_H
