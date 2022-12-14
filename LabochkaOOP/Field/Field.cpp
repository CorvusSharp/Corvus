//
// Created by corvussharp on 21.09.22.
//v

#include <sstream>
#include "Field.h"
#include "iostream"
#include "../save/Memento.h"
#include "../Exceptions/OpenFileException.h"
#include "../Exceptions/RestoreStateException.h"
#include "../Exceptions/SaveStateException.h"


#define FILESAVEFIELD "saveField.txt"
#define FILESAVEPLAYER "savePlayer.txt"
LogOutInfo *info = nullptr;

void Field::swap(Field &other) {
    std::swap(width, other.width);
    std::swap(height, other.height);
    std::swap(field, other.field);
    std::swap(person_loc, other.person_loc);
    std::swap(person, other.person);
}

void Field::trig_win() {
    trigWin = true;
}

void Field::update_field(std::pair<int, int> person_loc) {
    this->field.at(person_loc.second).at(person_loc.first).set_event(nullptr);
}

void Field::update(void *obj) {

}


int Field::get_height() const {
    return height;
}


int Field::get_width() const {
    return width;
}

std::vector<std::vector<Cell>> Field::get_field() const {
    return field;
}

bool Field::level_check_passab() {
    if (person->get_lvl() >= 2) {
        return true;
    }
    return false;
};

bool Field::get_win() const {
    return trigWin;
}

bool Field::check_box_win() {
    int count = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (dynamic_cast<EventXp *>(field.at(i).at(j).get_event()) != nullptr) {
                count++;
            }
        }
    }
    if (count == 0) {
        return true;
    }
    return false;
}

Field &Field::operator=(const Field &other) {
    if (this != &other) // не пытаемся ли мы присвоить объект сам в себя
        Field(other).swap(*this); //создаем временный объект(все поля совпадают с азер), меняемся с ним данными

    return *this;
}

Field &Field::operator=(Field &&other) {
    if (this != &other)
        this->swap(other); // меняем местами текущий и other
    return *this;
}

Field::Field(int width, int height) : trigWin(false), width(width), height(height), person_loc({0, 0}),person(new Person(1,1,1,1)) {
    for (int i = 0; i != height; ++i) {
        field.emplace_back(); // инициализация полей
        for (int j = 0; j != width; ++j) {
            field.at(i).emplace_back();
        }
    }
}

Field::Field(const Field &other) : width(other.width), height(other.height), person_loc(other.person_loc),
                                   person(other.person) {
    for (size_t i = 0; i != height; ++i) {
        field.emplace_back();
        for (size_t j = 0; j != width; ++j) {
            field.at(i).push_back(other.field.at(i).at(j));
        }
    }
}

Field::Field(Field &&other) { // конструктор перемещаем объект
    this->swap(other);
}

Cell &Field::getCell(std::pair<int, int> position) {
    return field.at(position.second).at(position.first);
}


void Field::spawn_new_events() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution gen_height(1, height - 1);
    std::uniform_int_distribution gen_width(0, width - 1);

    std::pair<int, int> pair1 = {gen_height(rng), gen_width(rng)};

    auto *spawnEventsBlock = new EventChangeField(this);

    field.at(pair1.first).at(pair1.second).set_event(spawnEventsBlock);
    field.at(pair1.first).at(pair1.second).set_passab(false);
}

void Field::spawn_box() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution gen_height(1, height - 1);
    std::uniform_int_distribution gen_width(0, width - 1);

    std::pair<int, int> pair1 = {gen_height(rng), gen_width(rng)};
    std::pair<int, int> pair2 = {gen_height(rng), gen_width(rng)};

    while (pair1 == pair2)
        pair2 = {gen_height(rng), gen_width(rng)};

    auto *boxXp = new EventXp(person);
    auto *boxXp1 = new EventXp(person);

    delete field.at(pair1.first).at(pair1.second).get_event();
    delete field.at(pair2.first).at(pair2.second).get_event();

    field.at(pair1.first).at(pair1.second).set_event(boxXp);
    field.at(pair2.first).at(pair2.second).set_event(boxXp1);
}

void Field::spawn_win() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution gen_height(1, height - 1);
    std::uniform_int_distribution gen_width(0, width - 1);

    std::pair<int, int> pair1 = {gen_height(rng), gen_width(rng)};

    auto *boxExit = new EventWin(this);

    field.at(pair1.first).at(pair1.second).set_event(boxExit);
    field.at(pair1.first).at(pair1.second).set_passab(false);
}


Person Field::get_person() const {
    return *person;
}

void Field::callEvent(Person *person, std::pair<int, int> person_loc) {
    if (dynamic_cast<EventPerson *>(getCell(person_loc).get_event())) {
        getCell(person_loc).update(person);
    } else if (dynamic_cast<EventField *>(getCell(person_loc).get_event())) {
        getCell(person_loc).update(this);
    }
}


void Field::spawn_events() {
    field.at(0).at(0).set_passab(true);
    for (int i = 0; i != height; ++i) {
        int value;
        if (i == 0) {
            value = 1;
        } else value = 0;
        for (int j = value; j != width; ++j) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100);

            switch (dist(rng)) {
                case 1: {
                    auto *xp = new EventXp(person);
                    field.at(i).at(j).set_event(xp);
                    break;
                }
                case 2: {
                    auto *hp = new EventHp(person);
                    field.at(i).at(j).set_event(hp);
                    break;
                }
                case 5: {
                    auto *dmg = new EventDmg(person);
                    field.at(i).at(j).set_event(dmg);
                    break;
                }
                default:
                    break;
            }

        }
    }
}


void Field::change_person_pos(CONTROL s) {
    auto tmp = person_loc;
    field.at(person_loc.second).at(person_loc.first).set_person_in(false);

    switch (s) {
        case CONTROL::UP:
            tmp.second--;
            break;
        case CONTROL::DOWN:
            tmp.second++;
            break;
        case CONTROL::LEFT:
            tmp.first--;
            break;
        case CONTROL::RIGHT:
            tmp.first++;
            break;
        case CONTROL::SAVE:
            saveGame();
            return;
        case CONTROL::LOAD:
            restoreGame();
            playerPos(person_loc.first, person_loc.second);
            return;
        default:
            break;
    }

    tmp.first = tmp.first % width;
    tmp.second = tmp.second % height;

    if (tmp.first < 0) tmp.first += width;
    if (tmp.second < 0) tmp.second += height;


    if (field.at(tmp.second).at(tmp.first).get_passab() || level_check_passab() ||
        (dynamic_cast<EventWin *>(field.at(tmp.second).at(tmp.first).get_event()) && check_box_win())) {
        person_loc = tmp;
        callEvent(person, person_loc);
        update_field(person_loc);
    }
    field.at(person_loc.second).at(person_loc.first).set_person_in(true);
}


void Field::make_field() {
    field.at(0).at(0).set_person_in(true);
    field.at(0).at(0).set_passab(true);
    spawn_box();
    spawn_new_events();
    spawn_win();
    for (int i = 0; i != height; ++i) {
        int value;
        if (i == 0) {
            value = 1;
        } else value = 0;
        for (int j = value; j != width; ++j) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> dist(1, 100);
            switch (dist(rng)) {
                case 2: {
                    auto *hp = new EventHp(person);
                    if (field.at(i).at(j).get_event() == nullptr) {
                        field.at(i).at(j).set_event(hp);
                    }
                    break;
                }
                case 3: {
                    auto *trap = new EventTrap(person);
                    field.at(i).at(j).set_event(trap);
                }
                case 5: {
                    auto *dmg = new EventDmg(person);
                    if (field.at(i).at(j).get_event() == nullptr) {
                        field.at(i).at(j).set_event(dmg);
                    }
                    break;
                }
                default:
                    break;
            }

        }
    }

}

void Field::playerPos(int x, int y) {
    field.at(person_loc.second).at(person_loc.first).set_person_in(false);
    field.at(person_loc.second).at(person_loc.first).set_person_in(true);
}





void Field::saveGame() {
    Memento memento;
    try {
        memento.saveState(getState(), FILESAVEFIELD);
        memento.saveState(person->getState(), FILESAVEPLAYER);
    } catch (...) {
        throw;
    }
}


std::string Field::getState() {
    std::string fieldParams;
    fieldParams += std::to_string(hash(width, height, person_loc, field));
    fieldParams += '\n' + std::to_string(width);
    fieldParams += '\n' + std::to_string(height);
    fieldParams += '\n' + std::to_string(person_loc.first);
    fieldParams += '\n' + std::to_string(person_loc.second);
    for (int h = 0; h < height; ++h){
        for (int w = 0; w < width; ++w){
            if (field.at(h).at(w).get_event() != nullptr){
                if (eventToString.find(field.at(h).at(w).get_event()->getHash()) == eventToString.end()) fieldParams += "\nNone";
                else fieldParams += '\n' + eventToString.at(field.at(h).at(w).get_event()->getHash());
            } else fieldParams += '\n' + std::to_string(!field.at(h).at(w).get_passab());
        }
    }
    return fieldParams;
}


void Field::setState(std::string str) {
    std::vector<int> data;
    auto ss = std::stringstream {str};
    bool isReadHash = false;
    std::string hashFromFile;
    int count = 0;
    std::vector<std::vector<Cell>> field;
    int h = 0;
    int w = 0;
    std::string tmpline;
    try {
        for (std::string line; std::getline(ss, line, '\n'); ){
            tmpline = line;
            if (!isReadHash) {
                hashFromFile = line;
                isReadHash = true;
                continue;
            }else {
                if (count < 4){
                    data.push_back(std::stoi(line));
                    ++count;
                    if(count  == 4){
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < data[0]; ++i) {
            field.emplace_back();
            for (int j = 0; j < data[1]; ++j) {
                count++;
                std::string current_cell;
                std::getline(ss, current_cell, '\n');
                tmpline = current_cell;
                Cell new_cell;
                if (current_cell == "0" or current_cell == "1"){
                    new_cell.set_passab(current_cell != "1");
                } else if(current_cell != "None")
                    new_cell.set_event(stringToEvent[current_cell]());
                field.at(i).push_back(new_cell);
            }
        }
    } catch (...){
        throw InvalidDataException("Incorrect data in file in line number " + std::to_string(count + 1) + "-----" + tmpline);
    }
    size_t fieldHash = hash(data[0], data[1], std::pair<int, int>(data[2], data[3]), field);
    if (std::to_string(fieldHash) != hashFromFile)
        throw InvalidDataException("Hash file is not equal hash state: " + std::to_string(fieldHash) + " != " + hashFromFile);
    else restoredData = std::make_tuple(data[0], data[1], std::make_pair(data[2], data[3]), field);
}


size_t Field::hash(int width, int height, std::pair<int, int> playerCoordinates, std::vector<std::vector<Cell>> field) {
    size_t hashWidth = std::hash<int>()(width);
    size_t hashHeight = std::hash<int>()(height);
    size_t hashCoordFirst = std::hash<int>()(playerCoordinates.first);
    size_t hashCoordSecond = std::hash<int>()(playerCoordinates.second);
    size_t hashCells = size_t(0);
    for (int h = 0; h < height; ++h){
        for (int w = 0; w < width; ++w){
            if (!field.at(h).at(w).get_passab()){
                hashCells += w<<h;
            }else if (field.at(h).at(w).get_event() != nullptr) {
                hashCells += field.at(h).at(w).get_event()->getHash();
            }
        }
    }
    return (hashWidth << hashWidth) + (hashHeight << hashHeight) + (hashCoordFirst << hashCoordFirst) + (hashCoordSecond << hashCoordSecond) + (hashCells << hashCells);
}


void Field::restoreState() {
    for (int h = 0; h < height; ++h){
        for (int w = 0; w < width; ++w){
            delete field.at(h).at(w).get_event();
        }
    }
    field.clear();
    width = std::get<0>(restoredData);
    height = std::get<1>(restoredData);
    field = std::get<3>(restoredData);
    playerPos( std::get<2>(restoredData).first,  std::get<2>(restoredData).second);
}


void Field::restoreGame() {
    Memento memento;
    try{
        person->setState(memento.restoreState(FILESAVEPLAYER));
        setState(memento.restoreState(FILESAVEFIELD));
        person->restoreState();
        restoreState();
    } catch (OpenFileException& OFE) {
        throw RestoreStateException(OFE.what());
    } catch (RestoreStateException& RSE) {
        throw RestoreStateException(RSE.what());
    } catch (InvalidDataException& IDE) {
        throw InvalidDataException(IDE.what());
    } catch (...) {
        throw RestoreStateException("Unknown Error");
    }
}
