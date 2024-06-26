#include <algorithm>
#include <iostream>
#include <string>
#include <unistd.h>

template <typename Arg, typename... Args>
auto
r_printf(const std::string_view format, const Arg& arg, const Args&... args)
{
}

namespace modern
{
template <typename... Args>
constexpr auto
printf(const std::string_view format, const Args&... args) -> void
{
    auto number_of_placeholders = 0;

    for (std::size_t i = 0; i < format.size(); ++i) {
        if (format[i] == '{') {
            for (std::size_t j = i + 1; j < format.size(); ++j) {
                if (format[j] == '{') {
                    write(STDOUT_FILENO, "wrong formatting!\n", 18);
                    exit(EXIT_FAILURE);
                }

                if (format[j] == '}') {
                    ++number_of_placeholders;
                    break;
                }
            }
        }
    }

    if (sizeof...(Args) != number_of_placeholders) {
        write(STDOUT_FILENO, "wrong formatting!\n", 18);
        exit(EXIT_FAILURE);
    }

    r_printf(format, args...);
}
} // namespace modern