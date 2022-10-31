//
// Created by corvussharp on 26.10.22.
//

#ifndef LABOCHKAOOP_LOGSTATUS_H
#define LABOCHKAOOP_LOGSTATUS_H
#include "../Observer.h"
#include "../Subject.h"
class LogStatus: public Observer{
void update(Message& massage);

explicit LogStatus(Subject *model);
};


#endif //LABOCHKAOOP_LOGSTATUS_H
