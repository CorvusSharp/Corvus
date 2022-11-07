//
// Created by corvussharp on 07.11.22.
//

#ifndef LABOCHKAOOP_CONTROLFILE_H
#define LABOCHKAOOP_CONTROLFILE_H

#include "ControlConfig.h"

class ControlFile : public ControlConfig {
public:

    explicit ControlFile(const std::string &);
    void read_config() override;
    ~ControlFile();
private:
    std::ifstream config;
};

#endif //LABOCHKAOOP_CONTROLFILE_H
