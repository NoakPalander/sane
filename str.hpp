#pragma once

#include <vector>
#include <string>
#include <ranges>
#include <string_view>
#include <charconv>

namespace sane::str {
    inline std::vector<std::string> split(std::string_view string, std::string_view delim = " ") {
        auto split_view = std::views::split(string, delim) | std::views::transform([](auto view) {
            auto common_view = view | std::views::common;
            return std::string(common_view.begin(), common_view.end());
        });

        return std::vector(split_view.begin(), split_view.end());
    }

    template<typename T>
    inline void from(std::string_view string, T& out, int base = 10) {
        auto[_, ec] = std::from_chars(string.begin(), string.end(), out, base);

        if (ec != std::errc())
            throw std::invalid_argument("Couldn't convert the passed string into the requested type.");
    }

    template<typename T>
    inline T from(std::string_view string, int base = 10) {
        T out;
        from(string, out, base);
        return out;
    }

    void to_upper(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), [](char8_t key){
            return std::toupper(key);
        });
    }

    void to_lower(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), [](char8_t key){
            return std::tolower(key);
        });
    }
}