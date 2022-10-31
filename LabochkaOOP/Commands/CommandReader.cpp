//
// Created by corvussharp on 21.09.22.
//

#include "CommandReader.h"

    void CommandReader::set_size(){
        while (true){

            std::cout<<"Введите Высоту:"; std::cin>>height;

            std::cout<<"Введите ширину:"; std::cin>>width;
            if(valid_arg(height) && valid_arg(width)){
                break;
            } else{
               auto a = arg_error();
            }
        }
    }
    char CommandReader::field_choice(){
        std::cout << "Хотите ли вы изменить размеры поля?\n Если нет Введите 'X' : ";
        std::cin>>sym;
        return sym;
    }
    int CommandReader::arg_error(){
        std::cout <<"\nВы вели отрицательно значение, попробуйте снова"<<std::endl;
        return 0;
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
            case 'w':
                step = Person::UP;
                break;
            case 's':
                step = Person::DOWN;
                break;
            case 'd':
                step = Person::RIGHT;
                break;
            case 'a':
                step = Person::LEFT;
                break;
            case 'e':
                step = Person::EXIT;
                std::cerr<<"Игра Закончена!"<<std::endl;
                break;
            default:
                std::cerr<<"Вы ввели не правильную команду"<<std::endl;
                step = Person::NOTHING;
                break;
        }
    }

    int CommandReader::get_height() const{
        return height;
    }

    void CommandReader::print_death(){
    std::cerr<<"Вы откинулуись!";
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


bool CommandReader::set_move(LogOutInfo *info) {
    char res;
    std::cout << "Move to: \n";
    std::cin >> res;
    switch (res) {
        case 'w':
            this->move = MOVES::UP;
            break;
        case 's':
            this->move = MOVES::DOWN;
            break;
        case 'a':
            this->move = MOVES::LEFT;
            break;
        case 'd':
            this->move = MOVES::RIGHT;
            break;
        case 'q': {
            Message message(STATUS, "Game over");
            notify(message);
            return false;
        }
        default:
            this->move = MOVES::NOWHERE;
            break;
    }
    return true;
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
            this->outputs.push_back(OUTPUT::FILEOUT);
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

CommandReader::MOVES CommandReader::get_move() {
    return this->move;
}

std::vector <LEVEL> get_levels();

std::vector <OUTPUT> CommandReader::get_outputs() {
    return this->outputs;
}

std::vector <LEVEL> CommandReader::get_levels() {
    return this->levels;
}

