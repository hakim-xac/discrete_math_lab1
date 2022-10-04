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

        auto size{ base.size() }; 
        bool replay{};
        size_t count{ 1 };
        while (pairs.size() != size) {
            push(stringGeneration(' ', "Пара номер: " + std::to_string(count)));
            if (replay) {
                push(delimiter('-'));
                push(stringGeneration(' ', "Ошибка ввода пары! Введите заново!"));
            }
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
            
            if (base.contains(first) && base.contains(second)) {
                pairs.emplace_back(std::make_pair(first, second));
                replay = false;
                ++count;
            }
            else replay = true;
        }     
    }

    template <typename ValueType>
    void Interface::printMatrix(const std::vector<std::pair<ValueType, ValueType>>& pairs) 
    {
        using value_type = std::decay_t<ValueType>;

        size_t size{ pairs.size() };
        size_t double_size{ size * size };
        std::vector <value_type> base(double_size);

        for (const auto& [col, row] : pairs) {

            auto pos{ row * size + col - size - 1 };
            assert(pos >= 0 && pos < double_size);
            if(!base[pos]) base[pos] = 1;
        }
        printToBuffer(base, size);

    }


    template<typename ValueType>
    inline void Interface::printToBuffer(const std::vector<ValueType>& base, size_t col_size)
    {
        std::stringstream ss;

        push(delimiter('='));
        push(stringGeneration(' ', "Вывод матрицы"));
        push(delimiter('-'));

        for (size_t i{}, ie{ col_size }; i != ie; ++i) ss << std::setw(4) << "|" << std::setw(4) << "#" << i+1;
        push(stringGeneration(' ', ss.str()));
        ss.str("");
        for (size_t i{}, ie{ col_size }; i != ie; ++i) ss << std::setw(4) << "-" << std::setw(4) << "-" << "-";
        push(stringGeneration(' ', ss.str()));
        ss.str("");

        for (size_t i{}, ie{ base.size() }; i != ie; ++i) {
            ss << std::setw(4) << "|" << std::setw(4) << base[i] << " ";
            if ((i + 1) % col_size == 0) {
                push(stringGeneration(' ', ss.str()));
                ss.str("");
            }
        }
        flush();

    }
}