#pragma once
#ifndef ENTITATE
#define ENTITATE

#include "comoara.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

template <class T>
void primesteViata(T& entitate, int hp)
{
    entitate.sethp(entitate.gethp() + hp);
}
class entitate
{
protected:
    std::string nume;
    int hp;
    std::vector<comoara*> inventar;
public:
    entitate(std::string nume = "", int hp = 0, std::vector<comoara*> inv = {}) : nume(nume), hp(hp) {
        for (int i = 0; i < inv.size(); i++)
            inventar.push_back(inv[i]);
    };
    int gethp()
    {
        return hp;
    }
    void sethp(int hp)
    {
        this->hp = hp;
    }
    void afisare_inventar(void)
    {
        for (int i = 0; i < inventar.size(); i++)
            std::cout << "[" << i + 1 << "] " << (*inventar[i]);
        std::cout << std::endl;
    }
    void adaugare_comoara(comoara* c)
    {
        inventar.push_back(c);
    }
    int cautare_comoara(comoara* c)
    {
        for (int i = 0; i < inventar.size(); i++)
            if (c == inventar[i])
                return i;
        return -1;
    }
    void eliminare_comoara(int pozitie, comoara* c)
    {
        inventar.erase(inventar.begin() + pozitie);
        delete c;
    }
    int utilizare_comoara(comoara* c, entitate& tinta)
    {
        int locatie_in_inventar = cautare_comoara(c);
        if (c->gethp() > 0)
            primesteViata<entitate>(*this, c->gethp());
        if (c->getdmg() > 0)
            primesteViata<entitate>(tinta, -c->getdmg());
        if(c->getdmg()>0)
        std::cout << this->nume << " a realizat " << c->getdmg() << " puncte dmg lui " << tinta.getNume()<<"\n";
        if(c->gethp()>0)
        std::cout << this->nume << " si-a regenerat " << c->gethp() << " puncte de viata \n";
        int ture = c->getTure();
        if (c->esteConsumabil())
            eliminare_comoara(locatie_in_inventar, c);
        return ture;
    }
    comoara* accesareInventar(int poz)
    {
        return inventar[poz];
    }

    int marimeInventar()
    {
        return inventar.size();
    }
    std::string getNume(void)
    {
        return nume;
    }
    void golire_inventar()
    {
        for (auto x : inventar)
        {
            delete x;
        }
    }
    float maxDmgOutput()
    {
        std::vector<comoara> CopieInv;
        for (int i = 0; i < inventar.size(); i++)
        {
            CopieInv.push_back(*inventar[i]->copie());
        }
        std::sort(CopieInv.begin(), CopieInv.end(), [](comoara A, comoara B)
            {
                return A.getdmg() * B.getTure() > A.getTure() * B.getdmg();
            }
        );
        return (float) CopieInv[0].getdmg() / CopieInv[0].getTure();
    }
};

#endif