#include "Interface.h"
#include <unordered_set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

namespace KHAS {

    void Interface::loop()
    {
        using Type = int;

        system("cls");
        showHeader();

        auto power{ inputPowerSet<Type>() };
        std::unordered_set<Type> base;
        base.reserve(power);
        inputElemsSet(base, power);


        std::vector<std::pair<Type, Type>> pairs;
        pairs.reserve(power);        
        pairsInput<Type>(base, pairs);

        printMatrix(pairs);
    }
}