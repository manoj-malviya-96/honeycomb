# HoneyComb

## Build Notes:
Note: If you have vcpkg installed, you can skip submodule update.

## Setting up env
```bash
git submodule update --init --recursive
```

Note: on linux you might need to:
```bash 
apt-get install libxt-dev
```

### !!! WARNING: First time Run is slow and might take over 30 minutes
It will take ages due to vcpkg setup and installing VTK and other deps.
But it caches everything so next runs will be much faster.

## Building App
Example Cmake command for MacOS
```bash
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo 
    -DCMAKE_TOOLCHAIN_FILE=/Users/manojmalviya/Documents/Git/honeycomb/thirdparty/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja -S /Users/manojmalviya/Documents/Git/honeycomb 
    -B /Users/manojmalviya/Documents/Git/honeycomb/cmake-build-relwithdebinfo
```
Example Build command for MacOS
```bash
ninja -j 8 .
```

## Running App
```bash
./build_directory/honeycomb_exe
```
It will open a window visualizing the hexagonal mesh


## Documentation
Codebase is split into two - 
1. Creating skeleton - a 2D graph of all vertices (can be extended to 3D)
2. And then using VTK to extrude and rendering the grid.

### Skeleton
Skeleton2D is a graph object containing vertices and edges (type safe).
Adding vertex and edges are done smartly to make sure no duplicates are added.

I tried to achieve this with optimal performance using 
```std::unordered_set``` for edges (as order doesnt matter) and std::map for vertices with vector (as order matters).

And then generating the skeleton using functional programming. I am a huge fan of keeping data immutable and using functional programming.
Just input and output for better control and specific series of functions.

Math is easy - we compute centers of all hexagons and then generate around it. 
The most bug prone part of code is generating centers - as to create a staggered grid.

Generating hexagon based on center is easy and I cache many precomputed values for high performance. 

### Renderer
VTK rendering is done in a seperate namespace -
I take skeleton 2D and convert to polygon in VTK style. And then use it to extrude a pipe along skeleton - 
and then we can render with classic approach (setting up actor, mapper, renderer and then window )
To make sure we can interact, added an interactive controller as well.


### Future Work
1. Fix corners of hexagon and add fillet. 
2. 3D vertices 
3. Adding tests

### Render example





