#include "new_printf.hpp"

auto
main() -> int
{
    modern::printf("{}, {}! {}-{}, {}, {}", "hello", "world", 120000U, 12);

    return 0;
}