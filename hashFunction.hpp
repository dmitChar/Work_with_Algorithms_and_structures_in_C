
#pragma once

#include "passanger.cpp"
#include "checkFile.hpp"
#include <iostream>
#include <fstream>

struct Table {
    passenger value;
    bool used;
};

struct Keys {
    Table* data;
};

inline int HashFunction(std::string key, int length);
inline void Show(Keys* k, int length);
inline void Add(Keys *k, int a, passenger pas, int length);
inline bool DelElem(Keys* k, int length,  std::string number);
inline void init(Keys* k, int length);
inline bool tableIsEmpty(Keys *k, int length);
inline void readF(Keys *k, int length);
inline bool searchByPasport(Keys *k, int length, std::string numb);
inline void delAllTable(Keys *k, int length);
inline void showOnePassanger(Keys *k, int length, std::string numb);
inline bool searchByFIO(Keys *k, int length, std::string numb);
inline std::string getPasByFIO(Keys *k, int length, std::string numb);

