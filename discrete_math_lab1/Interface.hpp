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
                push(stringGeneration(' ', "������! ��������� ����!"));
                push(delimiter('-'));
            }
            push(stringGeneration(' ', "������� �������� ���������"));
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

        using value_type = typename TContainer::value_type;

        auto power{ std::forward<TPower>(pow) };

        while(con.size() != power) {

            push(delimiter('-'));
            push(stringGeneration(' ', "������� ������� ���������:"));
            push(delimiter('-'));
            flush();
            auto [elem, is_elem] { dataInput<value_type>(ActionWithInputValue::LoopIsError) };    
            if (con.find(elem) == con.end())   con.emplace(elem);
        }
    }


    template <typename Type, typename TPower>
    void Interface::pairsInput(std::vector<std::pair<Type, Type>>& base, TPower&& pow, std::pair<Type, Type> min_max_elems) {

        using value_type = Type;

        auto power{ std::forward<TPower>(pow) };

        push(delimiter('='));
        push(stringGeneration(' ', "���� ���:"));
        push(delimiter('-'));
        flush();
        bool replay{};
        size_t count{ 1 };
        while (base.size() != power) {
            push(stringGeneration(' ', "���� �����: "+std::to_string(count)));
            if (replay) {
                push(delimiter('-'));
                push(stringGeneration(' ', "������ ����� ����! ������� ������!"));
            }
            push(delimiter('-'));
            push(stringGeneration(' ', "������� 1 ������� ����:"));
            push(delimiter('-'));
            flush();
            auto [first, is_first] { dataInput<value_type>(ActionWithInputValue::LoopIsError) };
            push(delimiter('-'));
            push(stringGeneration(' ', "������� 2 ������� ����:"));
            push(delimiter('-'));
            flush();
            auto [second, is_second] { dataInput<value_type>(ActionWithInputValue::LoopIsError) };
            if (isClamp(first, min_max_elems.first, min_max_elems.second)
                && isClamp(second, min_max_elems.first, min_max_elems.second)) {
                base.emplace_back(std::make_pair(first, second));
                replay = false;
                ++count;
            }
            else {
                replay = true;
            }
        }

        
    }
}