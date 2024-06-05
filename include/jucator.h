#pragma once
#ifndef JUCATOR
#define JUCATOR

#include "comoara.h"
#include "entitate.h"
#include "inamic.h"

#include <iostream>
#include <vector>
#include <sstream>



class jucator : public entitate
{
private:
    static jucator* instanta;
    comoara* defaul;
    jucator(std::string nume = "", int hp = 0, std::vector<comoara*> inv = {}, comoara* defaul = nullptr) : entitate(nume, hp), defaul(defaul)
    {
        for (int i = 0; i < inv.size(); i++)
            inventar.push_back(inv[i]);
    }  
public:
    jucator(const jucator&) = delete;
    jucator& operator=(const jucator&) = delete;
    void setDefault(comoara* c)
    {
        defaul = c;
    }
    comoara* getDefault()
    {
        return defaul;
    }
    static jucator* GetInstanta(void) {
        if (instanta == nullptr) {
            std::string nume;
            std::cout << "Alege un nume: ";
            std::cin >> nume;
            comoara* sabie_inceput = new comoara("sabie", 5, 15, 1);
            comoara* potiune_inceput = new comoara("potiune", 30, 0, 5, true);
            comoara* potiune_inceput1 = new comoara("topor", 0, 31, 2, true);
            comoara* potiune_inceput2 = new comoara("potiune", 30, 0, 1, true);
            instanta = new jucator(nume, 100, {sabie_inceput, potiune_inceput,potiune_inceput1,potiune_inceput2}, sabie_inceput);
        }
        return instanta;
    }
    
};

jucator* jucator::instanta = nullptr;
#endif