# Graph Coloring local search based algorithm

This is an educational repo storing the local search based algorithms for the Graph Coloring problem.


## Current versions

There are several branches for different algorithms

| Branch     | Version tag       | Description                                                                                              |
|------------|-------------------|----------------------------------------------------------------------------------------------------------|
| greedy     | greedy_v0.1.0     | The most simple greedy algorithm, used to generate the initialization configuration for other algorithms |
| vanilla_LS | vanilla_LS_v0.1.2 | The vanilla local search                                                                                 |
| vanilla_TS | vanilla_TS_v0.1.1 | The vanilla tabu search based from the vanilla local search                                              |
| main       | -                 | The working branch                                                                                       |


The vanilla_LS_v0.1.1 solves the instance DSJC500.5 with 49 colors in about 100 seconds.

## Compile and Run

First make sure that you have git, make, cmake, and a c++20 compatible compiler installed in your machine.

### 1. Clone the repo to local

```bash
$ git clone --no-checkout https://github.com/xavierwoo/graph_coloring.git
```

This command clones the repo to a folder named _graph_coloring_ in the current directory.
Now change directory into it, run following command to get all branches and tags

```bash
$ cd graph_coloring && git fetch --tags
```


### 2. Check out the version tag you want

Check out the version.
For example, we check out the 0.1.1 version for vanilla tabu search algorithm.

```bash
$ git checkout vanilla_TS_v0.1.1
```

### 3. Make a build directory for cmake

Create a build directory, and cd into it

```bash
$ mkdir build && cd build
```

This _build_ folder is for cmake.

### 4. Create Makefile using cmake

```bash
$ cmake -DCMAKE_BUILD_TYPE=Release ..
```

This command creates a Makefile for release build in the current directory (build) according to the CMakeLists.txt from the upper directory.
It should automatically download the dependencies.
It may take some time according to your network condition.

### 5. Build

Use _make_ command to compile.

```bash
$ make
```
This will create an executable file named _graph_coloring_ in this directory

### 6. Run

```bash
$ ./graph_coloring
```

This command run the compiled executable file


## Dependencies

This repo uses the following dependencies:

* compact_simple_graph v0.1.0. https://github.com/xavierwoo/compact_simple_graph.git
* fmt 11.1.4. https://github.com/fmtlib/fmt.git

