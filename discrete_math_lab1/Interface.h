#pragma once

#include "CommonInterface.h"
#include <iostream>
#include <unordered_set>
#include <sstream>

namespace KHAS {

    class Interface final : public CommonInterface
    {

    private:


    private:

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

        template <typename TContainer>
        void printMatrix(const TContainer& base_container, size_t lenght_col);

        template <typename TContainer, typename TPairContainer>
        void applyPairs(TContainer& base_container, const TPairContainer& pair_container, size_t lenght_col);

        template <typename TVecContainer, typename TPairContainer>
        void printProperties(const TVecContainer& vec_conteiner, const TPairContainer& pair_container, size_t lenght_col);

        template <typename TVecContainer>
        void printIsReflexive(const TVecContainer& vec_conteiner, size_t lenght_col);

        template <typename TVecContainer>
        void printIsAntiReflexive(const TVecContainer& vec_conteiner, size_t lenght_col);

        template <typename TVecContainer>
        void printIsSymmetry(const TVecContainer& vec_conteiner, size_t lenght_col);

        template <typename TVecContainer>
        void printIsAntiSymmetry(const TVecContainer& vec_conteiner, size_t lenght_col);

        template <typename TVecContainer, typename TPairContainer>
        void printIsTransitivity(const TVecContainer& vec_conteiner, const TPairContainer& pair_conteiner, size_t lenght_col);

        template <typename TVecContainer>
        bool isReflexive(const TVecContainer& vec_conteiner, size_t lenght_col);

        template <typename TVecContainer>
        bool isAntiReflexive(const TVecContainer& vec_conteiner, size_t lenght_col);

        template <typename TVecContainer>
        bool isSymmetry(const TVecContainer& vec_conteiner, size_t lenght_col);

        template <typename TVecContainer>
        bool isAntiSymmetry(const TVecContainer& vec_conteiner, size_t lenght_col);

        template <typename TVecContainer, typename TPairContainer>
        bool isTransitivity(const TVecContainer& vec_conteiner, const TPairContainer& pair_conteiner, size_t lenght_col);


    public:
        void loop() override;

        //* params */
        // first:   size_t          table_width_    | not default
        // second:  std::ostream&   out_            | default: std::cout
        Interface(std::size_t table_width, std::ostream& out = std::cout)
            : CommonInterface(table_width, out) {};
    };

}

#include "Interface.hpp"