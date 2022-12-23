//
// Created by corvussharp on 12.10.22.
//

#include "EventChangeField.h"

#include "../../Field/Field.h"

EventChangeField::EventChangeField(Field *field) {
    this->field = field;
    hash = typeid(EventChangeField).hash_code();

}

bool EventChangeField::execute(void *obj) {
    if (field) {
        field->spawn_events();
        Message message(GAME, "Change event happened");
        notify(message);
        return true;
    }
    return false;
}

size_t EventChangeField::getHash() {
    return hash;
}
