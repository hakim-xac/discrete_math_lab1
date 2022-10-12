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

        std::unordered_set<Type> base_set;
        base_set.reserve(power);
        inputElemsSet(base_set, power);

        std::vector<std::pair<Type, Type>> pairs;
        pairs.reserve(power*power); 

        pairsInput<Type>(base_set, pairs);
        pairs.shrink_to_fit();

        std::vector<Type> base_vec(power * power, Type{});
        applyPairs(base_vec, pairs, power);

        printMatrix(base_vec, power);

        printProperties(base_vec, pairs, power);
    }
}