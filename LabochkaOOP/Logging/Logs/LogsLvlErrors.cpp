//
// Created by corvussharp on 26.10.22.
//

#include "LogsLvlErrors.h"
LogsLvlErrors::LogsLvlErrors(Subject *model) {
    model->attach(this);
}

void LogsLvlErrors::update(Message& msg) {
    if (msg.getType() == ERROR) {
        Logger logger(msg.get_info());
        logger.print(msg);
    }
}