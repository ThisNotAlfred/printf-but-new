#include <string>

namespace modern
{
template <class... Args> auto printf(std::string& format, Args... args) -> std::size_t;
}