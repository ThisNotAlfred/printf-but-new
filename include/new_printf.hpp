#include <algorithm>
#include <iostream>
#include <string>
#include <unistd.h>

template <typename Arg>
    requires std::integral<Arg>
inline constexpr auto
parse_number(Arg arg)
{
    return std::to_string(arg);
}

template <typename Arg, typename... Args>
auto
r_printf(std::string& buffer, const std::string& format, const Arg& arg, const Args&... args)
{
    uint placeholder_loc = format.find('{');
    buffer.append(format.data(), placeholder_loc);

    std::string new_format = format.substr(placeholder_loc + 2, format.size());

    std::string new_arg = {};
    if constexpr (std::is_same<int, Arg>() || std::is_same<uint, Arg>() ||
                  std::is_same<double, Arg>() || std::is_same<float, Arg>() ||
                  std::is_same<long, Arg>() || std::is_same<ulong, Arg>()) {
        new_arg = parse_number(arg);
    } else {
        new_arg = arg;
    }

    buffer.append(new_arg);

    if constexpr (sizeof...(args) != 0) {
        r_printf(buffer, new_format, args...);
    }
}

namespace modern
{
template <typename... Args>
constexpr auto
printf(const std::string& format, const Args&... args)
{
    auto number_of_placeholders = 0;

    for (std::size_t i = 0; i < format.size(); ++i) {
        if (format[i] == '{') {
            for (std::size_t j = i + 1; j < format.size(); ++j) {
                if (format[j] == '{') {
                    write(STDOUT_FILENO, "wrong formatting!\n\0", 19);
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
        write(STDOUT_FILENO, "wrong formatting!\n\0", 19);
        exit(EXIT_FAILURE);
    }

    std::string buffer = {};
    r_printf(buffer, format, args...);

    write(STDOUT_FILENO, buffer.data(), buffer.size());
}
} // namespace modern