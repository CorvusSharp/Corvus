
//
// Created by corvussharp on 21.09.22.
//

#include <sstream>
#include "Person.h"

Person::Person(int hp, int damage, int xp, int lvl) : health(hp), damage(damage), xp(xp), lvl(lvl) {

}

int Person::get_hp() const {
    return health;
}

int Person::get_xp() const {
    return xp;
}

int Person::get_dmg() const {
    return damage;
}

int Person::get_lvl() const {
    return lvl;
}

void Person::set_hp(int hp) {
    this->health = hp;
    Message message(GAME, "Установленно новое значение хп");
    LOG.print(message);

}

void Person::set_dmg(int dmg) {
    this->damage = dmg;
    Message message(GAME, "Установленно новое значение дэмга");
    LOG.print(message);
}

void Person::set_xp(int xpe) {
    this->xp = xpe;
    Message message(GAME, "Установленно новое значение опыта");
    LOG.print(message);
}

void Person::set_lvl(int lvl) {
    this->lvl = lvl;
    Message message(GAME, "Установленно новое значение уровня");
    LOG.print(message);
}

std::string Person::getState() {
    std::string saveData;
    saveData += std::to_string (hash(damage, health, xp,lvl));
    saveData += "\n" + std::to_string(damage) + "\n" + std::to_string(health) + "\n" + std::to_string(xp)+"\n" + std::to_string(lvl);
    return saveData;
}

void Person::restoreState() {
    damage= restoredData[0];
    health = restoredData[1];
    xp = restoredData[2];
    lvl = restoredData[3];
}

size_t Person::hash(int xp, int health, int dmg, int lvl) {
    size_t hashDmg = std::max(size_t(100), std::hash<int>()(dmg * 100));
    size_t hashHealth = std::max(size_t(100), std::hash<int>()(health*100));
    size_t hashXp = std::max(size_t(100), std::hash<int>()(xp * 100));
    size_t hashLvl = std::max(size_t(100), std::hash<int>()(lvl * 100));
    return (hashDmg<<hashDmg) xor (hashHealth<<hashHealth) xor (hashXp<<hashXp); // для шифрования данных
}

void Person::setState(std::string str) {
    std::vector<int> data;
    auto ss = std::stringstream {str};
    bool isReadHash = false;
    std::string hashFromFile;
    int count = 0;
    try {
        for (std::string line; std::getline(ss, line, '\n'); ){
            if (!isReadHash) {
                hashFromFile = line;
                isReadHash = true;
            } else {
                data.push_back(std::stoi(line));
            }
            ++count;
        }
    } catch (...){
        throw InvalidDataException("Incorrect data in file in line number " + std::to_string(count + 1));
    }
    std::string restoredHash = std::to_string(hash(data[0], data[1], data[2], data[3]));
    if (hashFromFile == restoredHash){
        restoredData = data;
    } else if (data.size() != TOTALVAL) {
        throw InvalidDataException("File size changed: " + std::to_string(data.size()) + " != " + std::to_string(TOTALVAL));
    } else {
        throw InvalidDataException("Hash file is not equal hash state: " + hashFromFile + " != " + restoredHash);
    }
}
