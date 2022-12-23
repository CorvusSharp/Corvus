//
// Created by corvussharp on 11.10.22.
//

#include "EventWin.h"
#include "../../Field/Field.h"


EventWin::EventWin(Field *field) {
    this->field = field;
    hash = typeid(EventWin).hash_code();

}

bool EventWin::execute(void *obj) {
    if (field) {
        field->trig_win();
        Message message(GAME, "Win event happened");
        notify(message);
        return true;
    }
    return false;
}

size_t EventWin::getHash() {
    return hash;
}

