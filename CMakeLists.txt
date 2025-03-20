cmake_minimum_required(VERSION 3.29)
project(graph_coloring)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        compact_simple_graph
        GIT_REPOSITORY https://github.com/xavierwoo/compact_simple_graph.git
        GIT_TAG v0.1.0  # Specify the Git tag here
)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG         11.1.4 # or a specific release tag
)


FetchContent_MakeAvailable(compact_simple_graph fmt)

add_executable(graph_coloring main.cpp
        GraphColoring.cpp
        GraphColoring.h)

target_link_libraries(graph_coloring compact_simple_graph fmt::fmt)