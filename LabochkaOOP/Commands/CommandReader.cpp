#include<cstdio>
#include <termios.h>
#include <unistd.h>
#include "memory"
#include "CommandReader.h"

void CommandReader::set_size() {
    while (true) {
        std::cout << "Введите Высоту:";
        std::cin >> height;
        std::cout << "Введите ширину:";
        std::cin >> width;
        if (valid_arg(height) && valid_arg(width)) {
            Message message(GAME, "Height: " + std::to_string(height) + "Width: " + std::to_string(width));
            LOG.print(message);
            break;
        }
    }
}
char CommandReader::field_choice() {
    std::cout << "Хотите ли вы изменить размеры поля?\n Если нет Введите 'X' : ";
    std::cin >> sym;
    return sym;
}

bool CommandReader::valid_arg(int a) {
    if (a <= 0) {
        return false;
    }
    return true;
}
//////////////////////////////////////////////////
CONTROL CommandReader::check_step() {
    char key;
    std::cout << "Команды :\n\t\tw - движение вперед\n\t\ts - движение вниз\n\t\t"
                 "d - движение вправо\n\t\ta - движение влево\n\t\te - выйти из игры" << std::endl;
    std::cout << " Введите команду: ";
    std::cin >> key;
    step = control_config->get_key(key);
    return step;
}
void CommandReader::set_config(ControlConfig *config) {
    control_config = config;
}

CommandReader::CommandReader() {
    control_config = new ControlFile("cfg.txt");
}

///////////////////////////////////////////////////

int CommandReader::get_height() const {
    return height;
}

void CommandReader::print_death() {
    Message message(GAME, "Персонаж умер");
    LOG.print(message);
}

void CommandReader::print_win() {
    std::cerr << "ПобедОчка";
}

std::vector<OUTPUT> CommandReader::get_outputs() {
    return this->outputs;
}

std::vector<LEVEL> CommandReader::get_levels() {
    return this->levels;
}

char CommandReader::get_sym() const {
    return sym;
}

CONTROL CommandReader::get_step() const {
    return step;
}


int CommandReader::get_width() const {
    return width;
}


void CommandReader::set_output() {
    char res;
    std::cout << "Output to: \n";
    std::cout << "0 - File\n";
    std::cout << "1 - Console\n";
    std::cin >> res;
    switch (res) {
        case '0':
            this->outputs.push_back(OUTPUT::FILEOUT);
            break;
        case '1': {
            this->outputs.push_back(OUTPUT::CONSOLE);
            break;
        }
        case '3':{
            break;
        }
        default:
            this->outputs.push_back(OUTPUT::FILEOUT);
            this->outputs.push_back(OUTPUT::CONSOLE);
            break;
    }
}


void CommandReader::set_level() {
    char res;
    std::cout << "Logging level: \n";
    std::cout << "0 - Logging game\n";
    std::cout << "1 - Logging Status\n";
    std::cout << "2 - Logging Errors\n";
    std::cout<<" any - Nothing\n";
    std::cin >> res;
    switch (res) {
        case '0':
            this->levels.push_back(LEVEL::GAME);
            break;
        case '1': {
            this->levels.push_back(LEVEL::GAME);
            this->levels.push_back(LEVEL::STATUS);
            break;
        }
        case '2': {
            this->levels.push_back(LEVEL::GAME);
            this->levels.push_back(LEVEL::STATUS);
            this->levels.push_back(LEVEL::ERROR);
            break;
        }
        default:
            break;
    }
}

