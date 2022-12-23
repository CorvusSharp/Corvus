//
// Created by corvussharp on 21.09.22.
//


#ifndef UNTITLED48_FIELD_H
#define UNTITLED48_FIELD_H


#include <functional>
#include <map>
#include "../Cell/Cell.h"
#include "random"

#include "../Events/EventsPerson//EventXp.h"
#include "../Events/EventsPerson//EventHp.h"
#include "../Events/EventsPerson//EventDmg.h"
#include "../Events/EventsPerson//EventTrap.h"

#include "../Events/EventsField/EventWin.h"
#include "../Events/EventsField/EventChangeField.h"

class Field : public Subject {
private:
    bool trigWin;
    Person* person;
    std::vector<std::vector<Cell>> field;
    int height;
    int width;
    std::pair<int, int> person_loc;
    void saveGame();

    std::map<size_t, std::string> eventToString = {
            {typeid(EventTrap).hash_code(), "EventTrap"},
            {typeid(EventXp).hash_code(), "EventXp"},
            {typeid(EventDmg).hash_code(), "EventDmg"},
            {typeid(EventChangeField).hash_code(), "EventChangeField"},
            {typeid(EventWin).hash_code(), "EventWin"},
            {typeid(EventHp).hash_code(), "EventHp"}
    };
    std::map<std::string, std::function<Event*()>> stringToEvent = {
            {"EventTrap", [this](){return new EventTrap(person);}},
            {"EventHp", [this](){return new EventHp(person);}},
            {"EventWin", [this](){return new EventWin(this);}},
            {"EventChangeField", [this](){return new EventChangeField(this);}},
            {"EventDmg", [this](){return new EventDmg(person);}},
            {"EventXp", [this](){return new EventXp(person);}}
    };
    std::tuple<int, int, std::pair<int, int>, std::vector<std::vector<Cell>>> restoredData;
public:
    void swap(Field &other);
    explicit Field(int width = 10, int height = 10);

    Field(const Field &other);
    Field &operator=(const Field &other);
    Field(Field &&other);
    Field &operator=(Field &&other);


    void change_person_pos(CONTROL s);
    Cell &getCell(std::pair<int, int>);

    void callEvent(Person *person, std::pair<int, int> person_loc);
    void update_field(std::pair<int, int> person_loc);

    void spawn_box();
    void spawn_win();
    void update(void *obj);

    void make_field();
    Person get_person() const;

    void trig_win();
    bool get_win() const;

    bool level_check_passab();
    void spawn_events();

    bool check_box_win();

    int get_height() const;
    int get_width() const;
    void spawn_new_events();
    std::string getState();

    std::vector<std::vector<Cell>> get_field() const;
    void setState(std::string);
    size_t hash(int, int, std::pair<int, int>, std::vector<std::vector<Cell>>);
    void restoreState();
    void restoreGame();
    void playerPos(int x, int y);

};

#endif //UNTITLED48_FIELD_H
