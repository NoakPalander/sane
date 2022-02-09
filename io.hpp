#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <string_view>
#include <vector>
#include <fstream>
#include <filesystem>
#include <ranges>
#include <charconv>

namespace lazy::io {
    namespace detail {
        template<typename T>
        concept readable = requires(T t) {
            std::cin >> t;
        };

        template<typename T>
        concept writable = requires(T t) {
            std::cout << t;
        };
    }

    inline void sync_with_stdio(bool sync) noexcept {
        std::istream::sync_with_stdio(sync);
    }

    template<detail::readable T>
    inline T read(std::istream& stream = std::cin, bool discard_newline = true) {
        T t;
        stream >> t;
        if (discard_newline)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return t;
    }


    [[nodiscard]]
    inline std::string read_line(std::istream& stream = std::cin, std::string_view text = "") noexcept {
        if (!text.empty())
            std::cout << text;

        std::string out;
        std::getline(stream, out);
        return out;
    }

    [[nodiscard]]
    inline std::vector<std::string> read_lines(std::filesystem::path const& path) noexcept {
        std::vector<std::string> out;
        std::ifstream reader(path);
        if (reader)
            for (std::string line; std::getline(reader, line);)
                out.emplace_back(line);

        return out;
    }

    [[nodiscard]]
    inline std::string read_all(std::filesystem::path const& path) noexcept {
        std::string out;
        std::ifstream reader(path);
        if (reader)
            for (std::string line; std::getline(reader, line);)
                out += line + '\n';

        return out;
    }

    template<detail::writable T>
    inline bool write(std::filesystem::path const& path, T const& data, std::ios::openmode mode = std::ios::out) noexcept {
        std::ofstream writer(path, mode);
        if (writer) {
            writer << data;
            return true;
        }

        return false;
    }

    template<detail::writable T>
    inline bool write_lines(std::filesystem::path const& path, std::vector<T> const& data,
                            std::ios::openmode mode = std::ios::out) noexcept
    {
        std::ofstream writer(path, mode);
        if (writer) {
            for (auto const& i : data)
                writer << i << '\n';

            return true;
        }

        return false;
    }
}