}

    CONTROL ControlConfig::get_key(char move) {
//
// Created by corvussharp on 07.11.22.
//

#include <iostream>
#include "ControlConfig.h"

        void ControlConfig::check_config() {
            std::vector<char> used_sym;
            for (auto elem: empty_config) {
                if (elem.second == '\0') {
                    empty_config = default_config;
                    return;
                }
            }
            for (auto a: empty_config) {
                    std::cout << a.second;
        if (a.second == move) {
            return a.first;
        }
    }
    return NOTHING;
}



