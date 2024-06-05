#pragma once
#ifndef FABRICA
#define FABRICA

#include "comoara.h"
#include "inamic.h"

class Fabrica
{
private:
    std::vector<std::string> numePosibileInamici = { "Schelet","Mazga","Dragon" };
    static int esteInInterval(int x, std::vector<int> v)
    {
        if (x < v[0])
            return 0;
        for (int i = 0; i < v.size() - 1; i++)
            if (x >= v[i] && x < v[i]+v[i + 1])
                return i + 1;
        return v.size()-1;
    }
public:
    static inamic* CreareInamicRandom(int hp) {
        std::vector<inamic> inamici = { inamic("Dragon", 100, { new comoara("gheare",5,30,3), new comoara("inima_dragon",25,0,2,true)}, 3),
                                        inamic("Schelet", 30, { new comoara("sabie schelet",0,5,2), new comoara("potiune", 15,0,1,true)}, 2),
                                        inamic("Mazga", 10, { new comoara("lovitura mazga",1,1,2),new comoara("regenerare1",20,0,1,true),new comoara("regenerare2",40,0,2,true) }, 1) };
        int random = rand() % 100;
        std::vector<int> hpintervale = {100,100,0};
        std::vector<std::vector<int>> probabil = { { 70,25,5 } ,{ 25,50,25 },{ 5,25,70 } };
        std::vector<int> setprob = probabil[esteInInterval(hp, hpintervale)];
        return inamici[esteInInterval(random, setprob)].copie_inamic();
    }
    static comoara* CreareComoaraRandom(float dmgOutput) { //primesc [dmgperAttack/ture] 
        int random = rand() % 2;
        enum optiuni
        {
            POTIUNE,
            ARMA
        };
        switch (random)
        {
        case POTIUNE: {
            random = rand() % (int)(2.5*dmgOutput);
            std::vector<int> hpintervale= { 15,30,0 };
            comoara potiune_generica = comoara("potiune", 15 + 15 * esteInInterval(random, hpintervale), 0, 1+rand()%2, true);
            return potiune_generica.copie();
        }
        case ARMA: {
            int randomhprest = (rand() % (int)dmgOutput)/2;
            int newdmg = (int)(dmgOutput* 1.5)+randomhprest;
            random = rand() % 100;
            std::vector<int> dmgintervale = { 30,100,0 };
            std::vector<std::vector<int>> probabil = { { 70,25,5 } ,{ 25,50,25 },{ 5,25,70 } };
            std::vector<int> setprob = probabil[esteInInterval(dmgOutput, dmgintervale)];
            int indexArma = esteInInterval(random, setprob);
            std::vector<comoara> comori = { comoara("sabie", randomhprest, 1*newdmg, 1),
                                            comoara("topor", 2 * randomhprest, 2*newdmg, 2),
                                            comoara("buzdugan", 3 * randomhprest, 3*newdmg, 3) };
            return comori[indexArma].copie();
        }
        };
        
       
    }
};




#endif
