# Graph Coloring local search based algorithm

This is an educational repo storing the local search based algorithms for the Graph Coloring problem.


## Current versions

There are several branches for different algorithms

| Branch     | Version tag       | Description                                                                                              |
|------------|-------------------|----------------------------------------------------------------------------------------------------------|
| greedy     | greedy_v0.1.0     | The most simple greedy algorithm, used to generate the initialization configuration for other algorithms |
| vanilla_LS | vanilla_LS_v0.1.2 | The vanilla local search                                                                                 |
| vanilla_TS | vanilla_TS_v0.1.3 | The vanilla tabu search based from the vanilla local search                                              |
| main       | -                 | The working branch                                                                                       |


The vanilla_TS_v0.1.3 solves the instance DSJC500.5 with 49 colors in about 200 seconds.

## Compile and Run

First make sure that you have git, make, cmake, and a c++20 compatible compiler installed in your machine.

### 1. Clone the specific version to local

```bash
git clone --branch <version_tag> https://github.com/xavierwoo/graph_coloring.git
```

Replace <version_tag> to the version you are interested in.
For example: 

```bash
git clone --branch vanilla_TS_v0.1.3 https://github.com/xavierwoo/graph_coloring.git
```

Or you can just clone the whole repo and checkout the specific version.


### 2. Make a build directory for cmake

Create a build directory, and cd into it

```bash
$ mkdir build && cd build
```

This _build_ folder is for cmake.

### 3. Create Makefile using cmake

```bash
$ cmake -DCMAKE_BUILD_TYPE=Release ..
```

This command creates a Makefile for release build in the current directory (build) according to the CMakeLists.txt from the upper directory.
It should automatically download the dependencies.
It may take some time according to your network condition.

### 4. Build

Use _make_ command to compile.

```bash
$ make
```
This will create an executable file named _graph_coloring_ in this directory

### 5. Run

```bash
$ ./graph_coloring
```

This command run the compiled executable file


## Dependencies

This repo uses the following dependencies:

* compact_simple_graph v0.1.0. https://github.com/xavierwoo/compact_simple_graph.git
* compact_uset v0.4.0 https://github.com/xavierwoo/compact_uset.git
* fmt 11.1.4. https://github.com/fmtlib/fmt.git

CMake should have taken care of them.
You don't have to download them if using CMake.