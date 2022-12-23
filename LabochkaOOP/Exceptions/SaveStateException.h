//
// Created by corvussharp on 17.12.22.
//

#ifndef LABOCHKAOOP_SAVESTATEEXCEPTION_H
#define LABOCHKAOOP_SAVESTATEEXCEPTION_H



#include "GameException.h"

class SaveStateException: public GameException{
public:
    using GameException::GameException;
    std::string what() override;

};

#endif //LABOCHKAOOP_SAVESTATEEXCEPTION_H
