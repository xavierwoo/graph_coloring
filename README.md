# Graph Coloring local search based algorithm

This is an educational repo storing the local search based algorithms for the Graph Coloring problem.


## Current versions

There are several branches for different algorithms

| Branch     | Version tag       | Description                                                                                              |
|------------|-------------------|----------------------------------------------------------------------------------------------------------|
| greedy     | greedy_v0.1.0     | The most simple greedy algorithm, used to generate the initialization configuration for other algorithms |
| vanilla_LS | vanilla_LS_v0.1.1 | The vanilla local search                                                                                 |
| vanilla_TS | vanilla_TS_v0.1.0 | The vanilla tabu search based from the vanilla local search                                              |
| main       | -                 | The working branch                                                                                       |


The vanilla_LS_v0.1.1 solves the instance DSJC500.5 with 49 colors in about 100 seconds.

## Dependencies

This repo uses the following dependencies:

* compact_simple_graph v0.1.0. https://github.com/xavierwoo/compact_simple_graph.git
* fmt 11.1.4. https://github.com/fmtlib/fmt.git
ls
