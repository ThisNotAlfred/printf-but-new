project(
    'json-but-new',
    'cpp',
    default_options: [
        'cpp_std=c++23',
        'warning_level=3',
    ],
)

sources = [
    'source/main.cpp',
    'source/new_printf.cpp',
]

includes = [
    'include/new.hpp',
]

include_dirs = include_directories(
    [
        'include',
    ],
)

executable(
    'printf-but-new',
    [sources, includes],
    include_directories: [include_dirs],
)