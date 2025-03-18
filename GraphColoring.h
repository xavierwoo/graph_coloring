//
// Created by 吴 歆韵 on 2025/3/17.
//

#ifndef GRAPH_COLORING_GRAPHCOLORING_H
#define GRAPH_COLORING_GRAPHCOLORING_H
#include <csg/core.h>
#include <string>
#include <array>
#include <vector>
#include <cstdint>
#include <utility>
#include <fmt/core.h>
#include <limits>
#include <ranges>
#include <algorithm>

namespace graph_coloring{
    using csg::Graph;
    using fmt::print;
    using std::string, std::vector, std::array, std::pair;
    using std::ranges::sort, std::ranges::fill;

    auto read_instance_file(const string&) -> pair<uint64_t, vector<array<string, 2>>>;

    template<typename U>
    struct Solver{
    private:
        Graph<string, U> graph;
        vector<U> color;
        vector<vector<U>> conflict_table;
        U max_color{0};
        U conflicts{0};

        void greedy_color();

        [[nodiscard]] auto check_graph() const -> bool;
        [[nodiscard]] auto check_solution() const -> bool;
        [[nodiscard]] auto check_conflicts() const -> bool;
    public:
        explicit Solver(vector<array<string, 2>>&&);

        void solve();
    };

    template<typename U>
    auto Solver<U>::check_conflicts() const -> bool {
        U calculate_conflicts{0};
        vector<U> conflict_row(max_color+1, 0);
        for (U v{0}; v < graph.get_vertex_num(); ++v){
            fill(conflict_row, 0);
            for(U n : graph.get_neighbors_id(v))++conflict_row[color[n]];
            if(conflict_row != conflict_table[v]) return false;
            calculate_conflicts += conflict_row[color[v]];
        }
        return calculate_conflicts/2 == conflicts;
    }

    template<typename U>
    auto Solver<U>::check_solution() const -> bool{
        for(U v{0}; v<graph.get_vertex_num(); ++v){
            for (U n : graph.get_neighbors_id(v)){
                if(color[v] == color[n]) return false;
            }
        }
        return true;
    }

    template<typename U>
    auto Solver<U>::check_graph() const -> bool {
        for(U i{0}; i<graph.get_vertex_num() - 1; ++i){
            for (U j=i+1; j<graph.get_vertex_num(); ++j){
                if (graph.has_edge_id(i,j) != graph.has_edge_id(j, i)) return false;
            }
        }
        return true;
    }

    template<typename U>
    void Solver<U>::greedy_color() {
        color.resize(graph.get_vertex_num(), std::numeric_limits<U>::max());
        for(U v{0}; v<graph.get_vertex_num(); ++v){
            vector<U> neighbor_color;
            neighbor_color.reserve(graph.get_vertex_num());
            for(U n : graph.get_neighbors_id(v)) neighbor_color.push_back(color[n]);
            sort(neighbor_color);
            U c {0};
            for(U nc : neighbor_color){
                if(c == nc) ++c;
                else if (c < nc) break;
            }
            color[v] = c;
            if(max_color < c) max_color = c;
        }
        assert(check_solution());
    }

    template<typename U>
    void Solver<U>::solve() {
        greedy_color();
        print("Greedy colored the graph using {} colors", max_color+1);
    }

    template<typename U>
    Solver<U>::Solver(vector<array<string, 2>>&& edges){
        for(auto& edge_data : edges){
            graph.add_bdi_edge(edge_data[0], edge_data[1]);
        }
        graph.compile();
        assert(check_graph());
    }


}
#endif //GRAPH_COLORING_GRAPHCOLORING_H
