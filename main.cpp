#include <cstdint>
#include "GraphColoring.h"
#include <iostream>

int main() {
    auto [v_num, edges] { graph_coloring::read_instance_file("../instances/DSJC500.5.col.txt")};

    if (v_num < 255) {
        graph_coloring::Solver<uint8_t> solver(std::move(edges), 0);
        solver.solve();
    }else if (v_num < 65535){
        graph_coloring::Solver<uint16_t> solver(std::move(edges), 1);
        solver.solve();
    }else{
        std::cerr<<"Not supported yet\n";
    }

    return 0;
}
