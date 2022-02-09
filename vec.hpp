#pragma once

#include <cassert>
#include <memory>
#include <algorithm>

namespace sane {
    template<typename T, std::size_t N>
    class dyn_array {
    private:
        std::unique_ptr<T[]> buffer_;

    public:
        constexpr dyn_array()
                : buffer_{std::make_unique<T[]>(N)} {}

        explicit constexpr dyn_array(T const(&list)[N]) noexcept
                : buffer_{std::make_unique<T[]>(N)} {

            std::copy(list, list + N, buffer_.get());
        }

        constexpr dyn_array(dyn_array const& rhs) noexcept
                : buffer_{std::make_unique<T[]>(N)} {

            std::copy(rhs.buffer.get(), rhs.buffer.get() + N, buffer_.get());
        }

        constexpr dyn_array& operator=(dyn_array const& rhs) noexcept {
            if (this != &rhs) {
                buffer_ = std::make_unique<T[]>(N);
                std::copy(rhs.buffer_.get(), rhs.buffer_.get() + N, buffer_.get());
            }

            return *this;
        }

        constexpr dyn_array(dyn_array&& rhs) noexcept = default;
        constexpr dyn_array& operator=(dyn_array&& rhs) noexcept = default;

        [[nodiscard]] constexpr T* begin()             { return buffer_.get();     }
        [[nodiscard]] constexpr T* end()               { return buffer_.get() + N; }
        [[nodiscard]] constexpr T const* begin() const { return buffer_.get();     }
        [[nodiscard]] constexpr T const* end() const   { return buffer_.get() + N; }

        [[nodiscard]] constexpr std::size_t size() const {
            return N;
        }

        [[nodiscard]] constexpr T& at(std::size_t index) {
            if (index >= N)
                throw std::out_of_range("Out of bounds access!");

            return buffer_[index];
        }

        [[nodiscard]] constexpr T const& at(std::size_t index) const {
            if (index >= N)
                throw std::out_of_range("Out of bounds access!");

            return buffer_[index];
        }

        [[nodiscard]] constexpr T* data()             { return buffer_.get(); }
        [[nodiscard]] constexpr T const* data() const { return buffer_.get(); }

        [[nodiscard]] constexpr T& operator[](std::size_t index) {
            assert(index < N);
            return buffer_[index];
        }

        [[nodiscard]] constexpr T const& operator[](std::size_t index) const {
            assert(index < N);
            return buffer_[index];
        }
    };

    template<typename T>
    class static_vec {};

    class matrix {};
}