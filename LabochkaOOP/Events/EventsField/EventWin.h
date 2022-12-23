//
// Created by corvussharp on 11.10.22.
//

#ifndef LABOCHKAOOP_EVENTWIN_H
#define LABOCHKAOOP_EVENTWIN_H

class Field;
#include "EventField.h"

class EventWin : public EventField {
    size_t hash;
public:
    bool execute(void *obj) override;

    EventWin(Field *field);
    size_t getHash() final;
};


#endif //LABOCHKAOOP_EVENTWIN_H
