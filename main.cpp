#include <cstdint>
#include "GraphColoring.h"
#include <iostream>

int main() {
    auto [v_num, edges] { graph_coloring::read_instance_file("../instances/DSJC125.1.col.txt")};

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
