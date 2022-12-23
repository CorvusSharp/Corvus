//
// Created by corvussharp on 21.09.22.
//

#ifndef UNTITLED48_PERSON_H
#define UNTITLED48_PERSON_H

#include "../LOG/Logs/Subject.h"
#define TOTALVAL 3
#include "../Exceptions/InvalidDataException.h"
class Person : public Subject {
public:

    explicit Person(int hp = 1, int damage = 1, int xp = 1, int lvl = 1);

    int get_hp() const;
    int get_lvl() const;
    int get_xp() const;
    int get_dmg() const;

    void set_hp(int hp);
    void set_dmg(int dmg);
    void set_lvl(int lvl);
    void set_xp(int xpe);

    std::string getState();
    void setState(std::string);
    void restoreState();
    size_t hash(int xp, int health, int dmg,int lvl);
private:
    int health, xp, damage, lvl;
    std::vector<int> restoredData;
};

#endif //UNTITLED48_PERSON_H
