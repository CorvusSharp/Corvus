//
// Created by corvussharp on 14.12.22.
//

#ifndef LABOCHKAOOP_GENFIELD_H
#define LABOCHKAOOP_GENFIELD_H

#include "../Field/RULES/RuleSizeField.h"
#include "../Field/RULES/RuleSpawnPerson.h"
#include "../Field/RULES/RuleSpawnWallCell.h"
#include "../Field/RULES/RuleEventField.h"
#include "../Field/RULES/RuleEventPerson.h"

template<class ... Rule>
class GenField {
public:
    Field *Gen() {
        auto *field = new Field;
        (Rule()(field), ...);
        return field;
    }
};

#endif //LABOCHKAOOP_GENFIELD_H
