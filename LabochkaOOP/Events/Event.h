//
// Created by corvussharp on 11.10.22.
//

#ifndef LABOCHKAOOP_EVENT_H
#define LABOCHKAOOP_EVENT_H
#include "../LOG/Logs/Subject.h"
#include "../LOG/LogsInfo/LogOutInfo.h"
class Event: public Subject{
public:

    virtual bool execute(void *obj) = 0;
    virtual size_t getHash() = 0;
};


#endif //LABOCHKAOOP_EVENT_H
