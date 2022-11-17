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

void ControlFile::check_fix_config() {
    std::vector<char> list_char;
    for (auto elem: empty_config) {
        if (elem.second == '\0') {
            empty_config = default_config;
            return;
        }
        list_char.push_back(elem.second);
    }
    for (int i = 0; i < (list_char.size() - 1); i++) {
        for (int j = i + 1; j < list_char.size(); j++) {
            if (list_char[i] == list_char[j]) {
                empty_config = default_config;
                return;
            }
        }
    }
}

CONTROL ControlFile::get_key(char key) {
    for (auto a: empty_config) {
        if (a.second == key)
            return a.first;
    }
    return NOTHING;
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
        if (cmd == "UP=") {
            empty_config[UP] = symControl;
            std::string tmpMes = "Управление вверх установлено на ";
            Message message(STATUS, tmpMes + symControl);
            LOG.print(message);
        }
        if (cmd == "DOWN=") {
            empty_config[DOWN] = symControl;
            std::string tmpMes = "Управление вниз установлено на ";
            Message message(STATUS, tmpMes + symControl);
            LOG.print(message);
        }
        if (cmd == "LEFT=") {
            empty_config[LEFT] = symControl;
            std::string tmpMes = "Управление влево установлено на ";
            Message message(STATUS, tmpMes + symControl);
            LOG.print(message);
        }
        if (cmd == "RIGHT=") {
            empty_config[RIGHT] = symControl;
            std::string tmpMes = "Управление вправо установлено на ";
            Message message(STATUS, tmpMes + symControl);
           LOG.print(message);
        }
        if (cmd == "EXIT=") {
            empty_config[EXIT] = symControl;
            std::string tmpMes = "Выход установлен на ";
            Message message(STATUS, tmpMes + symControl);
            ///LOG.print(message);
        }
        if (cmd == "NOTHING=") {
            empty_config[NOTHING] = symControl;
        }
    }
    check_fix_config();
}



