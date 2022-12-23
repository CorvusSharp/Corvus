//
// Created by corvussharp on 14.10.22.
//

#ifndef LABOCHKAOOP_EVENTTRAP_H
#define LABOCHKAOOP_EVENTTRAP_H
//#include "../../Persons/Person.h"

#include "EventPerson.h"
class EventTrap: public EventPerson{
    size_t hash;
public:
    EventTrap(Person* person);
    bool execute(void *obj) override;
    size_t getHash() final;
};


#endif //LABOCHKAOOP_EVENTTRAP_H
