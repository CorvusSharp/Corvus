//
// Created by corvussharp on 23.12.22.
//

#ifndef LABOCHKAOOP_ORIGINATOR_H
#define LABOCHKAOOP_ORIGINATOR_H


#include "Memento.h"

class Originator {
public:
    virtual Memento saveState() = 0;
    virtual void restoreState(Memento) = 0;
    virtual void restoreCorrectState() = 0;

};



#endif //LABOCHKAOOP_ORIGINATOR_H
