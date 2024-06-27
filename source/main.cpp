#include "new_printf.hpp"

#include <chrono>
#include <print>

auto
main() -> int
{
    auto loop_start = std::chrono::high_resolution_clock::now();
    for (uint i = 0; i < 100000; ++i) {
        modern::printf("{}, {}! {}-{}\n", "hello", "world", 120000U, 12);
    }
    auto loop_end   = std::chrono::high_resolution_clock::now();
    auto time       = loop_end - loop_start;

    std::chrono::duration<float> delta_time_new_printf = time;

    loop_start = std::chrono::high_resolution_clock::now();
    for (uint i = 0; i < 100000; ++i) {
        printf("%s, %s! %u-%d\n", "hello", "world", 120000U, 12);
    }
    loop_end   = std::chrono::high_resolution_clock::now();
    time       = loop_end - loop_start;
    
    std::chrono::duration<float> delta_time_old_printf = time;

    loop_start = std::chrono::high_resolution_clock::now();
    for (uint i = 0; i < 100000; ++i) {
        std::print("{}, {}! {}-{}\n", "hello", "world", 120000U, 12);
    }
    loop_end   = std::chrono::high_resolution_clock::now();
    time       = loop_end - loop_start;
    
    std::chrono::duration<float> delta_time_std23_print = time;

    loop_start = std::chrono::high_resolution_clock::now();
    for (uint i = 0; i < 100000; ++i) {
        write(STDOUT_FILENO, "hello, world! 120000-12\n\0", 25);
    }
    loop_end   = std::chrono::high_resolution_clock::now();
    time       = loop_end - loop_start;
    
    std::chrono::duration<float> delta_time_write = time;

    std::print("new printf took: {} for 10000 iterations\n", delta_time_new_printf);
    std::print("old printf took: {} for 10000 iterations\n", delta_time_old_printf);
    std::print("std23 print took: {} for 10000 iterations\n", delta_time_std23_print);
    std::print("linux write syscall took: {} for 10000 iterations\n", delta_time_write);

    return 0;
}