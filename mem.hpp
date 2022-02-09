#pragma once

#include <memory>

namespace sane::mem {
    namespace detail {
        template <typename T>
        concept buffer_t = std::is_same_v<T, char> || std::is_same_v<T, unsigned char> || std::is_same_v<T, std::byte>;

        template <buffer_t T>
        struct AlignedDeleter {
            std::align_val_t alignment;

            void operator()(T* ptr) const noexcept { operator delete(ptr, alignment); }
        };
    }

    template<typename T, detail::buffer_t U = unsigned char>
	[[nodiscard]]
    inline std::unique_ptr<U, detail::AlignedDeleter<U>> aligned_unique_for_overwrite(std::size_t bytes = sizeof(T)) noexcept {
        detail::AlignedDeleter<U> const del{static_cast<std::align_val_t>(alignof(T))};

        auto p = static_cast<U*>(operator new(bytes, del.alignment));
        return { p, del };
    }
}
