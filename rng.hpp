#pragma once

#include <limits>
#include <random>
#include <iostream>

namespace sane::rng {
    namespace {
        std::random_device random_device;
    }

    namespace detail {
        template<std::integral T>
        inline constexpr auto uniform_dist(T min, T max) {
            std::uniform_int_distribution dist(min, max);
            return dist;
        }

        template<std::floating_point T>
        inline constexpr auto uniform_dist(T min, T max) {
            std::uniform_real_distribution dist(min, max);
            return dist;
        }
    }

    template<typename T, typename engine_t = std::default_random_engine>
    inline constexpr T number(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        engine_t engine(random_device());
        return detail::uniform_dist(min, max)(engine);
    }

    template<typename engine_t = std::default_random_engine>
    inline bool boolean(double odds) {
        engine_t engine(random_device());
        std::bernoulli_distribution dist(odds);
        return dist(engine);
    }
}