#pragma once

#include <chrono>
#include <utility>

namespace sane::time {
    struct date {
        int year;
        unsigned int month;
        unsigned int day;
    };

    template<typename Func, typename clock_t = std::chrono::steady_clock, typename... Args>
    std::chrono::time_point<clock_t> measure(Func&& function, Args&&... args) {
        //clock_t clock;
        const auto begin = clock_t::now();
        function(std::forward<Args>(args)...);
        const auto end = clock_t::now();
        return end - begin;
    }

    template<typename clock_t = std::chrono::steady_clock>
    std::chrono::time_point<clock_t> now() noexcept {
        return clock_t::now();
    }

    date current_date() {
        const std::chrono::year_month_day ymd = std::chrono::floor<std::chrono::days>(now<std::chrono::system_clock>());

        return {
            static_cast<int>(ymd.year()),
            static_cast<unsigned int>(ymd.month()),
            static_cast<unsigned int>(ymd.day())
        };
    }
}