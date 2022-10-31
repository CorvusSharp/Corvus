//
// Created by corvussharp on 21.09.22.
//

#include "Mediator.h"
#include "../Logs/LogsStatus.h"

void Mediator::start() {
    bool res = true;
    bool mv = true;
    input.set_output();
    input.set_level();
    Logger::getInstance().setLogOutInfo(LogOutInfo{input.get_outputs(), input.get_levels()});
    LogsStatus logsStatus(&(this->input));

    input.field_choice();
    if (input.get_sym() != 'X') {
        input.set_size();
        play.set_field(input.get_width(), input.get_height());
    } else {
        play.set_field_base();
    }
    while (input.get_step() != Person::EXIT) {
        play.print_stats();
        play.print_field();
        if (play.death_person()) {
            input.print_death();
            return;
        }
        if (play.win_game()) {
            input.print_win();
            return;
        }

        input.check_step();
        input.get_step();
        play.set_step(input.get_step());
    }
}
