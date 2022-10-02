#pragma once

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
    inline void Interface::inputElemsSet(TContainer& con, TPower&& pow) {

        using value_type = typename TContainer::value_type;

        auto power{ std::forward<TPower>(pow) };
        auto count{ power };
        bool replay{};
        while(con.size() != power) {
            if (replay) {
                push(delimiter('-'));
                push(stringGeneration(' ', "Данное число уже есть во множестве!", "Повторите ввод!"));
            }
            push(delimiter('-'));
            push(stringGeneration(' ', "Введите элемент множества:", "ещё " + std::to_string(count)));
            push(delimiter('-'));
            flush();
            auto [elem, is_elem] { dataInput<value_type>(ActionWithInputValue::LoopIsError) };    
            if (con.find(elem) == con.end()) {
                con.emplace(elem);
                --count;
                replay = false;
            }
            else replay = true;
        }
    }


    template <typename ValueType
        , template <typename, typename, typename, typename> class BaseType>
    void Interface::pairsInput(const BaseType<ValueType, std::hash<ValueType>, std::equal_to<ValueType>, std::allocator<ValueType>>& base
        , std::vector<std::pair<ValueType, ValueType>>& pairs) {

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
}