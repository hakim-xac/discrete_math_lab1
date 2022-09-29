#pragma once
#include "CommonInterface.h"
#include <algorithm>
#include <numeric>
#include <string>
#include <cassert>

namespace KHAS {

    template <typename TString>
    inline void CommonInterface::push(TString&& str) {
        out_buffer_ << std::forward<TString>(str);
        out_buffer_ << '\n';
    }

    template<typename ...TString>
    inline std::string CommonInterface::stringGeneration(char aggregate, TString&& ... str)
    {
        static_assert(sizeof...(str) > 0);
        std::initializer_list forward_str{  std::string(std::forward<TString>(str))... };

        std::size_t length_forward_str{ std::accumulate(
            forward_str.begin()
            , forward_str.end()
            , std::size_t{}
            , [](auto lhs, auto&& rhs) {
                return lhs + rhs.size();
            }) };

        assert(length_forward_str > 0);

        const std::size_t numerator{ table_width_ - length_forward_str };
        const std::size_t denominator{ sizeof...(str) + 1 };
        const std::size_t delimiter_size{  numerator / denominator + 1 };
        auto tmp{ std::string(delimiter_size, aggregate) };

        std::string result{ std::accumulate(
            forward_str.begin()
            , forward_str.end()
            , tmp
            , [&tmp](auto&& lhs, auto&& rhs) {
                auto result{ lhs + rhs + tmp };
                return result;
            }) };
        assert(result.size() <= table_width_ + denominator - numerator % denominator);
        result.resize(result.size() - denominator + numerator % denominator);
        result.shrink_to_fit();
        result.front() = result.back() = '#';
        return result;
    }
}