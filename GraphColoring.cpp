//
// Created by 吴 歆韵 on 2025/3/17.
//

#include "GraphColoring.h"
#include <fstream>

#include <string>

namespace graph_coloring{
    using std::ifstream;
    using std::stoll;
    auto read_instance_file(const string& file) -> pair<uint64_t, vector<array<string, 2>>>{
        ifstream ifs(file);
        print("Reading file: {}\n", file);
        string data;
        do{ifs>>data;}while(data != "edge");
        ifs>>data;
        const uint64_t vertex_num {(uint64_t)stoll(data)};
        ifs>>data;
        const uint64_t edge_num {(uint64_t)stoll(data)};

        print("vertex num: {}, edge num: {}\n", vertex_num, edge_num);

        vector<array<string, 2>> edges;
        edges.reserve(edge_num);
        while(!ifs.eof()){
            ifs>>data;
            if(ifs.eof())break;
            assert(data == "e");
            string source, target;
            ifs>>source>>target;
            edges.push_back({source, target});
        }

        return {vertex_num, edges};
    }
}