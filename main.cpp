#include <cstdint>
#include "GraphColoring.h"
#include <string>
#include <fstream>

using std::string, std::ofstream;

auto test_instance(const string& instance, unsigned int lower_bound, unsigned int seed) {
    auto [v_num, edges] { graph_coloring::read_instance_file(instance)};
    graph_coloring::Solver<uint16_t> solver(std::move(edges), seed);
    solver.solve(lower_bound);
    return solver.get_solved_color_num_and_time();
}

int main() {
    const string instance{"../instances/DSJC500.5.col.txt"};
    constexpr unsigned int lower_bound{49};
    unsigned int seed{101};//lucky seed

    test_instance(instance, lower_bound, seed);
    // constexpr string log("log.csv");
    // constexpr auto runs{50};
    // ofstream ofs(log, std::ios::app);
    // ofs<<"\ninstance, ";
    // for (int i = 1; i <= runs; ++i) {ofs<<i<<", ";}
    // ofs<<"\n"<<instance<<", ";
    // ofs.close();
    //
    // for (int i{0}; i<runs; ++i) {
    //     auto [c_num, time] {test_instance(instance, lower_bound, i)};
    //     ofs.open(log,std::ios::app);
    //     ofs<<time<<",";
    //     ofs.close();
    // }


    return 0;
}
