#pragma once
#ifndef JOC
#define JOC

#include "comoara.h"
#include "entitate.h"
#include "jucator.h"
#include "inamic.h"

#include "fabrica.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>

class joc
{
private:
    bool Terminat;
    jucator* erou = nullptr;
public:
    void init()
    {
        Terminat = 0;
        while (!Terminat)
        {
            erou = jucator::GetInstanta();
            inamic* NouInamic = Fabrica::CreareInamicRandom(erou->gethp());
            int numarComori = lupta(NouInamic);
            if (erou->gethp() <= 0)
            {
                Terminat = 1;
                std::cout << "Ai murit!\n";
            }
            else
            {
                while (numarComori > 0)
                {
                    comoara* nou = Fabrica::CreareComoaraRandom(erou->maxDmgOutput());
                    std::cout << "Ai gasit: " << *nou;
                    erou->adaugare_comoara(nou);
                    int optiune = 1;
                    while (optiune)
                    {
                        std::cout << "[0] Inapoi\n";
                        std::cin >> optiune;
                    }
                    numarComori--;
                }
            }
        }
    }
    int alegereDeLaComoara(comoara* c, inamic* i)
    {
        int optiune;
        system("CLS");
        std::cout << "Pe cine vrei sa o folosesti? ([0] Pe inamic/[1] Pe mine)\n";
        std::cin >> optiune;
        switch (optiune)
        {
        case 1:return erou->utilizare_comoara(c, *erou);
        case 0:return erou->utilizare_comoara(c, *i);
        }
    }
    int alegere_jucator(inamic* i)
    {
        while (1)
        {
            system("CLS");
            std::cout << "["<<erou->gethp()<<"hp] Ce vrei sa faci "<<erou->getNume()<<"?\n"
                "[0] " + erou->getDefault()->getNume() + "\n"
                "[1] Deschid inventarul\n"
                "[2] Inspectez inamic\n";
            int optiune;
            std::cin >> optiune;
            switch (optiune)
            {
            case 0:
            {
                return alegereDeLaComoara(erou->getDefault(), i);
            }
            case 1:
            {
                system("CLS");
                std::cout << "Ce vrei sa faci?\n"
                              "[0] Ma intorc\n";
                erou->afisare_inventar(); //restul inventarului
                std::cin >> optiune;

                if (optiune != 0)
                {
                    int poz = optiune;
                    comoara* comoaraInChestiune = erou->accesareInventar(poz-1);
                    system("CLS");
                    std::cout << "Vrei sa folosesti " + comoaraInChestiune->getNume() + " ?\n"
                        "[0] Da\n"
                        "[1] Nu\n"
                        "[2] Setez default\n";
                    std::cin >> optiune;
                    switch (optiune)
                    {
                    case 0: return alegereDeLaComoara(comoaraInChestiune, i);
                    case 2: erou->setDefault(comoaraInChestiune);
                    case 1:;
                    }
                }

            }
            case 2:
            {system("CLS");
            std::cout << i->getNume() << "[" << i->gethp() << "]\n";
            i->afisare_inventar();
            while (optiune != 0)
            {
                std::cout << "[0] Inapoi\n";
                std::cin >> optiune;
            }
            }
            }
        }
    }
    int alegere_inamic(inamic* ina)
    {
        int hpMaxindice = 0;
        if (ina->gethp() < jucator::GetInstanta()->gethp())
            for (int i = 0; i < ina->marimeInventar(); i++)
                if (ina->accesareInventar(i)->gethp() > ina->accesareInventar(hpMaxindice)->gethp())
                    hpMaxindice = i;
        return ina->utilizare_comoara(ina->accesareInventar(hpMaxindice), *erou);
                    
    }
    int lupta(inamic* i)
    {
        int ture_erou=1;
        int ture_inamic=1;
        while (i->gethp()>0 && erou->gethp()>0)
        {
            if(ture_erou==1)
                ture_erou = 1+alegere_jucator(i);
            if(ture_inamic==1)
                ture_inamic = 1+alegere_inamic(i);
            ture_erou--;
            ture_inamic--;
            if (ture_erou >= 1)
            {
                if(ture_erou>1)
                    std::cout << "Trebuie sa mai astepti " << ture_erou << " ture" << std::endl;
                else
                    std::cout << "Poti ataca!\n";
            }
            if (ture_inamic >= 1)
            {
                if (ture_inamic > 1)
                    std::cout << "Inamicul trebuie sa mai astepte " << ture_inamic << " ture" << std::endl;
                else
                    std::cout << "Inamicul poate ataca!\n";
            }
            std::cout << i->getNume() << " [" << i->gethp() << "hp], " << erou->getNume() << " [" << erou->gethp() << "hp]\n";
            int optiune=1;
            while (optiune != 0)
            {
                std::cout << "[0] Inapoi\n";
                std::cin >> optiune;
            }
        }
        return i->getloot();
    }
};
#endif