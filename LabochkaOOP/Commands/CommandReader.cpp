//
// Created by corvussharp on 21.09.22.
//

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
    char CommandReader::field_choice(){
        std::cout << "Хотите ли вы изменить размеры поля?\n Если нет Введите 'X' : ";
        std::cin>>sym;
        return sym;
    }

    bool CommandReader::valid_arg(int a){
        if (a<=0){
            return false;
        }
        return true;
    }
    void CommandReader::check_step(){

        std::cout<<"Команды :\n\t\tw - движение вперед\n\t\ts - движение вниз\n\t\t"
                   "d - движение вправо\n\t\ta - движение влево\n\t\te - выйти из игры"<<std::endl;
        std::cout<<" Введите команду: ";
        input_sym(sym);
        switch (sym) {
            case 'w': {
                step = Person::UP;
                Message message(GAME, "Пользователь ввел команду: w");
                LOG.print(message);
                break;
            }
            case 's': {
                step = Person::DOWN;
                Message message(GAME, "Пользователь ввел команду: s" );
                LOG.print(message);
                break;
            }
                case 'd': {
                    step = Person::RIGHT;
                    Message message(GAME, "Пользователь ввел команду: d");
                    LOG.print(message);
                    break;
                }
            case 'a': {
                step = Person::LEFT;
                Message message(GAME, "Пользователь ввел команду: a");
                LOG.print(message);
                break;
            }
            case 'e': {
                step = Person::EXIT;
                Message message(GAME, "Пользователь ввел команду: e");
                LOG.print(message);
                break;
            }
            default:
                step = Person::NOTHING;
                Message message(ERROR,"Вы ввели не правильную команду");
                LOG.print(message);
                break;
        }
    }

    int CommandReader::get_height() const{
        return height;
    }

    void CommandReader::print_death(){
        Message message(GAME, "Персонаж умер");
        LOG.print(message);
    }

    int CommandReader::get_width()const{
        return width;
    }
    char CommandReader::input_sym(char &sym){
        std::cin>>sym;
        return sym;
    }
    void CommandReader::print_win(){
        std::cerr<<"ПобедОчка";
    }
    char CommandReader::get_sym()const{
        return sym;
    }
    Person::STEP CommandReader::get_step() const{
        return step;
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
    std::cout << "0 - Game\n";
    std::cout << "1 - Status\n";
    std::cout << "2 - Errors\n";
    std::cin >> res;
    switch (res) {
        case '0':
            this->levels.push_back(LEVEL::GAME);
            break;
        case '1': {
            this->levels.push_back(LEVEL::GAME);
            this->levels.push_back(LEVEL::STATUS);
        }
            break;
        case '2': {
            this->levels.push_back(LEVEL::GAME);
            this->levels.push_back(LEVEL::STATUS);
            this->levels.push_back(LEVEL::ERROR);
        }
            break;
    }
}


std::vector <OUTPUT> CommandReader::get_outputs() {
    return this->outputs;
}

std::vector <LEVEL> CommandReader::get_levels() {
    return this->levels;
}

