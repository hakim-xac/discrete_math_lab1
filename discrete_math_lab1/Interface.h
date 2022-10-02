#pragma once

#include "CommonInterface.h"
#include <iostream>
#include <unordered_set>
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

        template <typename ValueType>
        using PairType = std::pair<ValueType, ValueType>;

        template <typename ValueType
            , template <typename, typename, typename, typename> class BaseType>
        void pairsInput(const BaseType<ValueType, std::hash<ValueType>, std::equal_to<ValueType>, std::allocator<ValueType>>& base
            , std::vector<std::pair<ValueType, ValueType>>& pairs);
    };

}

#include "Interface.hpp"