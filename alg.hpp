#pragma once
#include <span>
#include <iostream>
#include <vector>

namespace sane::alg {
    template<typename T>
    [[nodiscard]]
    constexpr inline std::vector<std::pair<std::size_t, T const&>> enumerate(std::span<T> span) noexcept {
        std::vector<std::pair<std::size_t, T const&>> enumerated;
        enumerated.reserve(span.size());

        for (std::size_t index = 0; auto const& val : span)
            enumerated.emplace_back(index++, val);

        return enumerated;
    }
}