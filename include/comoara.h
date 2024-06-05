#pragma once
#ifndef COMOARA
#define COMOARA

#include <iostream>
#include <iostream>
#include <vector>
#include <sstream>

class comoara {
private:
    std::string nume;
    int hprestaurat;
    int dmgperAttack;
    int ture;
    bool consumabil;
    template<class T>
    static std::string toString(const T& value) {
        std::ostringstream os;
        os << value;
        return os.str();
    }
    template<class T>
    static std::string AfisareProprietate(std::string sir, T x)
    {
        return (x == 0) ? "" : (" " + sir + " " + toString<T>(x));
    }
    template<>
    static std::string AfisareProprietate(std::string sir, bool x)
    {
        return (x == 0) ? "" : (" " + sir);
    }
public:
    comoara(std::string nume = "", int hpr = 0, int dmg = 0, int ture = 0, bool cons = 0) : nume(nume), hprestaurat(hpr), dmgperAttack(dmg), ture(ture), consumabil(cons) {};
    bool esteConsumabil(void)
    {
        return consumabil;
    }
    friend std::ostream& operator<<(std::ostream& os, comoara com)
    {
        std::vector<int> propr = { com.hprestaurat, com.dmgperAttack,com.ture }; bool cons = com.consumabil;
        std::vector<std::string> siruri = { "hp:","dmg:","ture:", "(consumabil)" };
        std::cout << com.nume << ":";
        for (int i = 0; i < propr.size(); i++)
            std::cout << AfisareProprietate<int>(siruri[i], propr[i]);
        std::cout << AfisareProprietate<bool>(siruri[3], cons) << std::endl;
        return os;
    }
    comoara* copie(void)
    {
        return new comoara(nume, hprestaurat, dmgperAttack, ture, consumabil);
    }
    int gethp(void)
    {
        return hprestaurat;
    }
    int getdmg(void)
    {
        return dmgperAttack;
    }
    int getTure(void)
    {
        return ture;
    }
    std::string getNume(void)
    {
        return nume;
    }
    
};

#endif