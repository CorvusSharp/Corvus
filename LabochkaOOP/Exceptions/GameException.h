//
// Created by corvussharp on 17.12.22.
//

#ifndef LABOCHKAOOP_GAMEEXCEPTION_H
#define LABOCHKAOOP_GAMEEXCEPTION_H
#include <exception>
#include <string>

class GameException: public std::exception {
protected:
    std::string message;
public:
    explicit GameException(std::string);
    virtual std::string what() = 0;
};
#endif //LABOCHKAOOP_GAMEEXCEPTION_H
