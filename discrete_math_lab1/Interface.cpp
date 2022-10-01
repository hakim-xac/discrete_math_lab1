#include "Interface.h"
#include <set>
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


        //* Debug output */
        std::copy(base.begin(), base.end(), std::ostream_iterator<Type>(std::cout, " "));
    }
}