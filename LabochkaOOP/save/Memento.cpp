//
// Created by corvussharp on 23.12.22.
//


#include "Memento.h"
#include "../Exceptions/SaveStateException.h"
#include "../Exceptions/RestoreStateException.h"
#include "../Exceptions/OpenFileException.h"
#include <fstream>
#include <iostream>

void Memento::saveState(const std::string& state, const std::string& filename) {
    std::fstream fileSave;
    fileSave.open(filename, std::ios::out);
    if (!fileSave.is_open())
        throw OpenFileException("Could not open file [ " + filename + " ] for save state");
    fileSave << state;
    fileSave.close();
}

std::string Memento::restoreState(const std::string& filename) {
    std::fstream fileSave;
    fileSave.open(filename);
    if(!fileSave.is_open())
        throw OpenFileException("Could not open file [ " + filename + " ] for restore state");
    std::string data;
    std::string line;
    while (getline(fileSave, line)){
        data+=line;
        data+="\n";
    }
    return data;
}