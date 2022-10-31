//
// Created by corvussharp on 26.10.22.
//

#ifndef LABOCHKAOOP_LOGSLVLERRORS_H
#define LABOCHKAOOP_LOGSLVLERRORS_H
#include "../Observer.h"
#include "../Subject.h"
#include "../Logger.h"
class LogsLvlErrors: public Observer{
public:
    LogsLvlErrors(Subject *model);

    void update(Message& massage) override;

    ~LogsLvlErrors() override = default;
};


#endif //LABOCHKAOOP_LOGSLVLERRORS_H
