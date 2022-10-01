#include "Interface.h"
#include <set>
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
        std::set<Type> base;
        inputElemsSet(base, power);

        auto min_max_elems{ std::minmax_element(base.begin(), base.end()) };

        std::vector<std::pair<Type, Type>> pairs;
        pairs.reserve(power);
        pairsInput<Type>(pairs, power, { *(min_max_elems.first), *(min_max_elems.second) });

        //* Debug output */
        std::copy(base.begin(), base.end(), std::ostream_iterator<Type>(std::cout, " "));
        std::cout << "\n\n";
        //* Debug output */
        for (auto&& [a, b] : pairs) {
            std::cout << a << " " << b << "\n";
        }
    }
}