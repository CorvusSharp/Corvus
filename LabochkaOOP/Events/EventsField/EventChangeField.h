//
// Created by corvussharp on 12.10.22.
//

#ifndef LABOCHKAOOP_EVENTCHANGEFIELD_H
#define LABOCHKAOOP_EVENTCHANGEFIELD_H

class Field;

#include "EventField.h"

class EventChangeField : public EventField {
    size_t hash;
public:
    bool execute(void *obj) override;
    size_t getHash() final;
    explicit EventChangeField(Field *field);
};


#endif //LABOCHKAOOP_EVENTCHANGEFIELD_H
