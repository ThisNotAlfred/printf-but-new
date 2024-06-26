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
    std::for_each(format.begin(), format.end(),
                  [&number_of_placeholders, &format, idx = 0](auto chr) mutable {
                      if (chr == '{') {
                          for (std::size_t i = idx + 1; i < format.size(); ++i) {
                              if (format[i] == '{') {
                                  std::cout << idx << "\n";
                                  write(STDOUT_FILENO, "wrong formatting!\n", 18);
                                  exit(EXIT_FAILURE);
                              }
                          }

                          if (chr == '}') {
                              ++number_of_placeholders;
                          }
                      }
                      ++idx;
                  });

    if (sizeof...(Args) != number_of_placeholders) {
        write(STDOUT_FILENO, "wrong formatting!\n", 18);
        std::cout << sizeof...(Args) << " " << number_of_placeholders << "\n";
        exit(EXIT_FAILURE);
    }

    r_printf(format, args...);
}
} // namespace modern