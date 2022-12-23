//
// Created by corvussharp on 06.10.22.
//

#ifndef UNTITLED48_EVENTHP_H
#define UNTITLED48_EVENTHP_H
#include "EventPerson.h"
//#include "../../Persons/Person.h"


class EventHp: public EventPerson{
    size_t hash;
public:
    bool execute(void *obj) override;
    size_t getHash() final;
    explicit EventHp(Person* person);

};
#endif //UNTITLED48_EVENTHP_H
