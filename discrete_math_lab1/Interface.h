#pragma once

#include "CommonInterface.h"
#include <iostream>
#include <sstream>

namespace KHAS {

    class Interface final : public CommonInterface
    {
    private:

    public:
        void loop() override;

        //* params */
        // first:   size_t          table_width_    | not default
        // second:  std::ostream&   out_            | default: std::cout
        Interface(std::size_t table_width, std::ostream& out = std::cout)
            : CommonInterface(table_width, out) {};

        template<typename Type>
        Type inputPowerSet();

        template <typename TContainer, typename TPower>
        void inputElemsSet(TContainer& con, TPower&& pow);

        template <typename Type, typename TPower>
        void pairsInput(std::vector<std::pair<Type, Type>>& base, TPower&& pow, std::pair<Type, Type> min_max_elems);
    };

}

#include "Interface.hpp"