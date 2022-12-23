//
// Created by corvussharp on 06.10.22.
//

#ifndef UNTITLED48_EVENTDMG_H
#define UNTITLED48_EVENTDMG_H

#include "EventPerson.h"
//#include "../../Persons/Person.h"


class EventDmg: public EventPerson{
    size_t hash;
public:

    bool execute(void *obj) override;
    size_t getHash() final;
    EventDmg(Person* person);
};

#endif //UNTITLED48_EVENTDMG_H
