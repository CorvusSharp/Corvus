//
// Created by corvussharp on 17.12.22.
//

#include "RestoreStateException.h"
std::string  RestoreStateException::what() {
    return "Error restore state because of:\n" + message;
}