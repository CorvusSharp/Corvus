//
// Created by corvussharp on 07.11.22.
//


#include "ControlFile.h"
#include "ControlConfig.h"
#include "iostream"
#include "../LOG/Logging/Logger.h"

ControlFile::~ControlFile() {
    config.close();
}

ControlFile::ControlFile(const std::string &file_name) {
    config.open(file_name, std::ios_base::in);
}

void ControlFile::read_config() {
    if (!config.is_open()) {
        empty_config = default_config;
        return;
    }
    std::string tmpStr;
    while (getline(config, tmpStr)) {
        std::string cmd;
        char symControl = '\0';
        std::istringstream stream(tmpStr);
        stream >> cmd >> symControl;
        if (cmd == "UP=" && symControl != '\0') {
            empty_config[UP] = symControl;
            std::string tmpMes = "Управление вверх установлено на ";
            Message message(STATUS, tmpMes + symControl);
            LOG.print(message);
        }
        if (cmd == "DOWN=" && symControl != '\0') {
            empty_config[DOWN] = symControl;
            std::string tmpMes = "Управление вниз установлено на ";
            Message message(STATUS, tmpMes + symControl);
            LOG.print(message);
        }
        if (cmd == "LEFT=" && symControl != '\0') {
            empty_config[LEFT] = symControl;
            std::string tmpMes = "Управление влево установлено на ";
            Message message(STATUS, tmpMes + symControl);
            LOG.print(message);
        }
        if (cmd == "RIGHT=" && symControl != '\0') {
            empty_config[RIGHT] = symControl;
            std::string tmpMes = "Управление вправо установлено на ";
            Message message(STATUS, tmpMes + symControl);
            LOG.print(message);
        }
        if (cmd == "EXIT=" && symControl != '\0') {
            empty_config[EXIT] = symControl;
            std::string tmpMes = "Выход установлен на ";
            Message message(STATUS, tmpMes + symControl);
            LOG.print(message);
        }
        if (cmd == "NOTHING" && symControl != '\0') {
            empty_config[NOTHING] = symControl;
        }
    }
    check_config();
}

