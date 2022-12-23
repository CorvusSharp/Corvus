//
// Created by corvussharp on 17.12.22.
//

#include "SaveStateException.h"

std::string SaveStateException::what() {
    return "Error save game because of\n" + message;
}