
#include "InvalidDataException.h"


        std::string InvalidDataException::what() {
    return "Incorrect data: " + message;
}