#pragma once
#ifndef INAMIC
#define INAMIC

#include "entitate.h"
#include "comoara.h"
#include "jucator.h"

#include <iostream>
#include <vector>
#include <sstream>


class inamic : public entitate {
private:
    int nrLoot;
public:
    inamic(std::string nume = "", int hp = 0, std::vector<comoara*> inv = {}, int nrLoot = 0) : entitate(nume, hp), nrLoot(nrLoot)
    {
        for (int i = 0; i < inv.size(); i++)
            inventar.push_back(inv[i]);
    }
    inamic* copie_inamic()
    {
        std::vector<comoara*> inv = {};
        for (int i = 0; i < inventar.size(); i++)
            inv.push_back(inventar[i]->copie());
        return new inamic(nume, hp, inv, nrLoot);;
    }
    int getloot()
    {
        return nrLoot;
    }
    ~inamic() = default;
};
#endif