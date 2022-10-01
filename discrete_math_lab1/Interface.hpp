#pragma once

namespace KHAS {

    template <typename Type>
    Type Interface::inputPowerSet()
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
    void Interface::inputElemsSet(TContainer& con, TPower&& pow) {

        using PowerType = std::decay_t<TPower>;
        using value_type = typename TContainer::value_type;

        auto power{ std::forward<TPower>(pow) };

        while(con.size() != power) {

            push(stringGeneration(' ', "Введите элемент множества:"));
            push(delimiter('-'));
            flush();
            auto [elem, is_elem] { dataInput<value_type>(ActionWithInputValue::LoopIsError) };    
            if (con.find(elem) == con.end())   con.emplace(elem);
        }
    }
}