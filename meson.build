project(
    'json-but-new',
    'cpp',
    default_options: [
        'cpp_std=c++23',
        'warning_level=3',
        'buildtype=release',
    ],
)

sources = [
    'source/main.cpp',
]

includes = [
    'include/new_printf.hpp',
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