#pragma once

#include <sstream>
#include <iomanip>
#include "Interface.h"

namespace KHAS {

    template <typename Type>
    inline Type Interface::inputPowerSet()
    {
        using InputType = Type;

        InputType power;
        bool is_power{};
        bool replay{};
        do {
            push(delimiter('='));
            if (replay) {
                push(stringGeneration(' ', "Ошибка! Повторите ввод!"));
                push(delimiter('-'));
            }
            push(stringGeneration(' ', "Введите мощность множества"));
            push(delimiter('-'));
            flush();

            std::tie(power, is_power) = dataInput<InputType>(ActionWithInputValue::LoopIsError);
            constexpr const auto max_limit{ (std::numeric_limits<InputType>::max)() };

            power = clamp(power, 0, max_limit);
            replay = true;
        } while (power < 1);

        return power;

    }


    template <typename TContainer, typename TPower>
    inline void Interface::inputElemsSet(TContainer& con, TPower&& pow) 
    {

        using value_type = typename TContainer::value_type;

        auto power{ std::forward<TPower>(pow) };
        auto count{ power };
        bool replay{};
        value_type idx{ 1 };
        while(con.size() != power) {
            if (replay) {
                push(delimiter('-'));
                push(stringGeneration(' ', "Данное число уже есть во множестве!", "Повторите ввод!"));
            }
            push(delimiter('-'));
            push(stringGeneration(' ', "Введите элемент множества:", "ещё " + std::to_string(power - idx + 1)));
            push(delimiter('-'));
            flush();
            auto [elem, is_elem] { dataInput<value_type>(ActionWithInputValue::LoopIsError) };  
            bool is_not_clamp{ !isClamp(elem, 1, power) };
            bool is_unordered_index{ idx != elem };

            if (is_not_clamp) {
                push(delimiter('-'));
                push(stringGeneration(' ', "Введеный элемент не должен превышать мощность множества и быть меньше 1 !"));
                push(delimiter('-'));
                flush();
                continue;
            }
            else if (is_unordered_index) {
                push(delimiter('-'));
                push(stringGeneration(' ', "Ввод данных не соответствует условию!"));
                push(stringGeneration(' ', "[ Ожидается "+std::to_string(idx) + " ]" ));
                push(delimiter('-'));
                flush();
                continue;
            }
            ++idx;
            replay = true;    
            if (con.find(elem) == con.end()) {                
                if (auto mx{ std::max_element(std::begin(con), std::end(con)) };
                    con.size() == 0 || (mx != std::end(con) &&  *mx < elem)) {
                    con.emplace(elem);
                    --count;
                    replay = false;
                }
            }
        }
    }


    template <typename ValueType
        , template <typename, typename, typename, typename> class BaseType>
    void Interface::pairsInput(const BaseType<ValueType, std::hash<ValueType>, std::equal_to<ValueType>, std::allocator<ValueType>>& base
        , std::vector<std::pair<ValueType, ValueType>>& pairs) 
    {

        using value_type = ValueType;


        push(delimiter('='));
        push(stringGeneration(' ', "Ввод пар:"));
        push(delimiter('-'));
        flush();
        auto double_size{ base.size() * base.size() };

        size_t count{ 1 };
        while (pairs.size() != double_size) {
            push(stringGeneration(' ', "Пара номер: " + std::to_string(count)));
            push(delimiter('-'));
            push(stringGeneration(' ', "Введите 1 элемент пары:"));
            push(delimiter('-'));
            flush();
            auto [first, is_first] { dataInput<value_type>(ActionWithInputValue::LoopIsError) };
            push(delimiter('-'));
            push(stringGeneration(' ', "Введите 2 элемент пары:"));
            push(delimiter('-'));
            flush();
            auto [second, is_second] { dataInput<value_type>(ActionWithInputValue::LoopIsError) };
            
            if (!base.contains(first) || !base.contains(second)) {
                push(delimiter('-'));
                push(stringGeneration(' ', "Ошибка ввода пары! Введите заново!"));
                push(delimiter('-'));
                continue;
            }

            pairs.emplace_back(std::make_pair(first, second));
            ++count;  

            if (pairs.size() + 1 != double_size) {
                push(delimiter('-'));
                push(stringGeneration(' ', "Продолжить?", "0 - Нет", "1 - Да"));
                flush();
                auto [answer, is_answer] { dataInput<value_type>(ActionWithInputValue::ErrorReturn) };
                if (!is_answer || answer != 1) break;
            }
        }     
    }

    template <typename TContainer>
    void Interface::printMatrix(const TContainer& base_container, size_t lenght_col)
    {
        using value_type = TContainer;

        std::stringstream ss;

        push(delimiter('='));
        push(stringGeneration(' ', "Вывод матрицы"));
        push(delimiter('-'));

        for (size_t i{}, ie{ lenght_col }; i != ie; ++i) ss << std::setw(4) << "|" << std::setw(4) << "#" << i + 1;
        push(stringGeneration(' ', ss.str()));
        ss.str("");
        for (size_t i{}, ie{ lenght_col }; i != ie; ++i) ss << std::setw(4) << "-" << std::setw(4) << "-" << "-";
        push(stringGeneration(' ', ss.str()));
        ss.str("");

        for (size_t i{}, ie{ base_container.size() }; i != ie; ++i) {
            ss << std::setw(4) << "|" << std::setw(4) << base_container[i] << " ";
            if ((i + 1) % lenght_col == 0) {
                push(stringGeneration(' ', ss.str()));
                ss.str("");
            }
        }
        flush();

    }

    template <typename TContainer, typename TPairContainer>
    void Interface::applyPairs(TContainer& base_container, const TPairContainer& pair_container, size_t lenght_col) {

        for (auto&& pair : pair_container) {
            auto row{ pair.first - 1 };
            auto col{ pair.second - 1 };

            auto pos{ row * lenght_col + col };
            assert(base_container.size() > pos);
            base_container[pos] = 1;
        }
    }


    template <typename TVecContainer, typename TPairContainer>
    void Interface::printProperties(const TVecContainer& vec_conteiner, const TPairContainer& pair_conteiner, size_t lenght_col) {

        push(delimiter('='));
        push(stringGeneration(' ', "Свойства"));
        push(delimiter('-'));
        printIsReflexive       (vec_conteiner, lenght_col);
        printIsAntiReflexive   (vec_conteiner, lenght_col);
        printIsSymmetry        (vec_conteiner, lenght_col);
        printIsAntiSymmetry    (vec_conteiner, lenght_col);
        printIsTransitivity    (vec_conteiner, pair_conteiner, lenght_col);

        flush();
    }

    template <typename TVecContainer>
    void Interface::printIsReflexive(const TVecContainer& vec_conteiner, size_t lenght_col) {
        
        push(stringGeneration(' ', "Рефлексивность:", (isReflexive(vec_conteiner, lenght_col) ? "Рефлексивно" : "НЕ Рефлексивно")));
        push(delimiter('-'));
    }

    template <typename TVecContainer>
    void Interface::printIsAntiReflexive(const TVecContainer& vec_conteiner, size_t lenght_col) {

        push(stringGeneration(' ', "Антирефлексивность:", (isAntiReflexive(vec_conteiner, lenght_col) ? "Антирефлексивно" : "НЕ Антирефлексивно")));
        push(delimiter('-'));
    }

    template <typename TVecContainer>
    void Interface::printIsSymmetry(const TVecContainer& vec_conteiner, size_t lenght_col) {

        push(stringGeneration(' ', "Симметричность:", (isSymmetry(vec_conteiner, lenght_col) ? "Симметрично" : "НЕ Симметрично")));
        push(delimiter('-'));
    }

    template <typename TVecContainer>
    void Interface::printIsAntiSymmetry(const TVecContainer& vec_conteiner, size_t lenght_col) {

        push(stringGeneration(' ', "Антисимметричность:", (isAntiSymmetry(vec_conteiner, lenght_col) ? "Антисимметрично" : "НЕ Антисимметрично")));
        push(delimiter('-'));
    }

    template <typename TVecContainer, typename TPairContainer>
    void Interface::printIsTransitivity(const TVecContainer& vec_conteiner, const TPairContainer& pair_conteiner, size_t lenght_col) {

        push(stringGeneration(' ', "Транзитивность:", (isTransitivity(vec_conteiner, pair_conteiner, lenght_col) ? "Транзитивно" : "НЕ Транзитивно")));
        push(delimiter('-'));
    }

    template <typename TVecContainer>
    bool Interface::isReflexive(const TVecContainer& vec_conteiner, size_t lenght_col) {
        
        for (size_t ie{}, ite{ vec_conteiner.size() }; ie < ite; ie += (lenght_col + 1))
            if (!vec_conteiner[ie]) return false;
        return true;
    }

    template <typename TVecContainer>
    bool Interface::isAntiReflexive(const TVecContainer& vec_conteiner, size_t lenght_col) {

        for (size_t it{}, ite{ vec_conteiner.size() }; it < ite; it += (lenght_col + 1))
            if (vec_conteiner[it]) return false;
        return true;
    }

    template <typename TVecContainer>
    bool Interface::isSymmetry(const TVecContainer& vec_conteiner, size_t lenght_col) {

    for (size_t it{ 1 }, ite{ (vec_conteiner.size() >> 1) - 1 }; it < ite; ++it) {
            auto left{ lenght_col * it + it - 1 };
            auto right{ (it - 1) * lenght_col + it };
            
            if (vec_conteiner[left] != vec_conteiner[right]) return false;
        }
        return true;
    }

    template <typename TVecContainer>
    bool Interface::isAntiSymmetry(const TVecContainer& vec_conteiner, size_t lenght_col) {

        return !isSymmetry(vec_conteiner, lenght_col);
    }

    template <typename TVecContainer, typename TPairContainer>
    bool Interface::isTransitivity(const TVecContainer& vec_conteiner, const TPairContainer& pair_conteiner, size_t lenght_col) {

        for (const auto& elem : pair_conteiner) {

            auto fnd{ std::find_if(std::begin(pair_conteiner)
                , std::end(pair_conteiner)
                , [&elem, &vec_conteiner, &lenght_col](const auto& pair ) {

                auto pos { (elem.first - 1) * lenght_col + pair.second - 1 };
                return elem.second == pair.first && vec_conteiner[pos] == 1;

                }) };
            if (fnd == pair_conteiner.end()) return false;
        }
        return true;
    }
}