//
// Created by corvussharp on 26.10.22.
//

#include "LogStatus.h"

void LogStatus::update(Message &msg) {
    if (msg.getType() == STATUS) {
        Logger logger(msg.get_info());
        logger.print(msg);
    }
}
LogStatus::LogStatus(Subject *model) {
    model->attach(this);
}
