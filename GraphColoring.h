//
// Created by 吴 歆韵 on 2025/3/17.
//

#ifndef GRAPH_COLORING_GRAPH_COLORING_H
#define GRAPH_COLORING_GRAPH_COLORING_H
#include <csg/core.h>
#include <string>
#include <array>
#include <vector>
#include <cstdint>
#include <fmt/core.h>
#include <limits>
#include <ranges>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <random>
#include <ctime>

namespace graph_coloring{
    using csg::Graph;
    using fmt::print;
    using std::string, std::vector, std::array, std::pair;
    using std::ranges::sort, std::ranges::fill;

    auto read_instance_file(const string&) -> pair<uint64_t, vector<array<string, 2>>>;

    template<typename U>
    struct Solver{
        struct Move{
            U vertex;
            U to_color;
        };

    private:
        Graph<string, U> graph;
        vector<U> color;
        vector<vector<U>> conflict_table;
        vector<vector<uint64_t>> tabu_table;
        uint64_t tt_min{10};
        uint64_t tt_extends{10};
        uint64_t iteration{0};
        U max_color{0};
        U conflicts{0};
        U ever_least_conflicts{std::numeric_limits<U>::max()};
        clock_t start_time{0};

        mutable vector<Move> tmp_best_moves;
        mutable vector<Move> tmp_best_tb_moves;
        mutable std::mt19937 die;

        void init();
        void greedy_color();
        void shrink_color_num();
        void calc_conflict_table();
        void reset_tabu_table();
        auto find_move() const -> pair<Move, int>;
        void make_move(Move,int);
        void local_search();

        [[nodiscard]] auto check_graph() const -> bool;
        void check_solution() const;
        [[nodiscard]] auto check_conflicts() const -> bool;

    public:

        explicit Solver(vector<array<string, 2>>&&, unsigned int seed = 0);
        void solve();
    };

    template<typename U>
    void Solver<U>::local_search() {
        for(;;++iteration){
            auto [mv, delta] {find_move()};
            make_move(mv, delta);
            if(conflicts == 0) return;
            assert(check_conflicts());
        }
    }

    template<typename U>
    void Solver<U>::make_move(Move mv, const int delta) {
        U prev_color{color[mv.vertex]};

        for(U n : graph.get_neighbors_id(mv.vertex)){
            auto& n_row {conflict_table[n]};
            --n_row[prev_color];
            ++n_row[mv.to_color];
        }

        color[mv.vertex] = mv.to_color;
        conflicts += delta;
        if (conflicts < ever_least_conflicts) ever_least_conflicts = conflicts;
        tabu_table[mv.vertex][prev_color] = iteration + conflicts + die()%tt_extends + 1;
    }

    /***
     * Returns the best Move with a delta to the conflicts
     */
    template<typename U>
    auto Solver<U>::find_move() const -> pair<Move, int> {
        tmp_best_moves.clear();
        tmp_best_tb_moves.clear();
        int best_delta{std::numeric_limits<int>::max()};
        int best_tb_delta{std::numeric_limits<int>::max()};

        for(U v{0}; v<graph.get_vertex_num(); ++v){
            if (conflict_table[v][color[v]] == 0) continue;
            for(U c{0}; c<=max_color; ++c){
                if (c==color[v]){continue;}
                bool is_tabu{tabu_table[v][c] >= iteration};
                auto& best_mvs {is_tabu?tmp_best_tb_moves:tmp_best_moves};
                auto& best_d {is_tabu?best_tb_delta:best_delta};
                if(const int delta {conflict_table[v][c] - conflict_table[v][color[v]]}
                ; delta < best_d){
                    best_mvs.clear();
                    best_mvs.push_back({v,c});
                    best_d = delta;
                }else if(delta == best_d){
                    best_mvs.push_back({v,c});
                }
            }
        }

        if (tmp_best_moves.empty()) {
            print("\tNo non-tabu move!\n");
            return pair(tmp_best_tb_moves[die()%tmp_best_tb_moves.size()], best_tb_delta);
        }else if (best_tb_delta + conflicts < ever_least_conflicts && best_tb_delta < best_delta) {
            print("\tAspiration!\n");
            return pair(tmp_best_tb_moves[die()%tmp_best_tb_moves.size()], best_tb_delta);
        }else {
            return pair(tmp_best_moves[die()%tmp_best_moves.size()], best_delta);
        }
    }

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
    void Solver<U>::calc_conflict_table() {
        conflicts = 0;
        for(U v{0}; v<graph.get_vertex_num(); ++v){
            auto& ct_v_row {conflict_table[v]};
            fill(ct_v_row, 0);
            for(U n : graph.get_neighbors_id(v)) ++ct_v_row[color[n]];
            conflicts += ct_v_row[color[v]];
        }
        conflicts /= 2;
    }

    template<typename U>
    void Solver<U>::reset_tabu_table() {
        for (auto& row : tabu_table) fill(row, 0);
    }

    template<typename U>
    void Solver<U>::shrink_color_num() {
        --max_color;
        for(U& c : color){
            if(c > max_color) c = die()%max_color;
        }
        for(auto& row : conflict_table) row.pop_back();
        for(auto& row : tabu_table) row.pop_back();
    }

    template<typename U>
    void Solver<U>::init() {
        greedy_color();
        conflict_table.resize(graph.get_vertex_num(), vector<U>(max_color+1));
        tabu_table.resize(graph.get_vertex_num(), vector<uint64_t>(max_color+1));
        shrink_color_num();
        calc_conflict_table();
        reset_tabu_table();
        assert(check_conflicts());
    }

    template<typename U>
    void Solver<U>::check_solution() const{
        for(U v{0}; v<graph.get_vertex_num(); ++v){
            for (U n : graph.get_neighbors_id(v)){
                if(color[v] == color[n]) {
                    std::cerr <<"err"<<std::endl;
                    std::abort();
                }
            }
        }
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
        print("Greedy find a {} coloring solution\n", max_color+1);
    }

    template<typename U>
    void Solver<U>::solve() {
        start_time = std::clock();
        init();
        for(;;){
           local_search();
           if(conflicts > 0) break;
           auto time_used{(std::clock() - start_time) / (double)CLOCKS_PER_SEC};
           check_solution();
           print("Successfully find a {} coloring solution! using {} seconds, {} iterations\n", max_color+1, time_used, iteration);
           shrink_color_num();
           calc_conflict_table();
           reset_tabu_table();
        }
    }

    template<typename U>
    Solver<U>::Solver(vector<array<string, 2>>&& edges, const unsigned int seed)
    :die(seed){
        for(auto& edge_data : edges){
            graph.add_bdi_edge(edge_data[0], edge_data[1]);
        }
        graph.compile();
        assert(check_graph());
    }
}
#endif //GRAPH_COLORING_GRAPH_COLORING_H
