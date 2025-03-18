#include <fmt/core.h>
#include <cstdint>
#include "GraphColoring.h"
#include <iostream>

using fmt::print;
int main() {
    auto [v_num, edges] { graph_coloring::read_instance_file("../instances/DSJC500.9.col.txt")};

    if (v_num < 255) {
        graph_coloring::Solver<uint8_t> solver(std::move(edges));
        solver.solve();
    }else if (v_num < 65535){
        graph_coloring::Solver<uint16_t> solver(std::move(edges));
        solver.solve();
    }else{
        std::cerr<<"Not supported yet\n";
    }

    return 0;
}
