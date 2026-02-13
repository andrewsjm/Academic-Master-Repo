Perlin Noise Benchmark (Single-thread vs Multi-thread)

This folder contains a small benchmark that evaluates the runtime of a Perlin-style noise computation over a 64×64 grid.

- `mainfrk.cpp` — single-thread baseline
- `main.cpp` — multi-threaded version using `std::thread`
- `perlin.h` — noise implementation (octaves + interpolation)

perlin.h
Defines a `Noise` struct with:
- hashing-based pseudo-random `noise(x,y,z)`
- cosine interpolation
- multi-octave noise (`octaves`)
- `getColor(x,y,z,slow)` which averages surrounding samples for smoothing

mainfrk.cpp (baseline)
Creates a 64×64 grid of points and runs `getColor()` for each point in a single loop, timing the duration.

main.cpp (threaded)
Creates the same 64×64 grid, then:
- reads `<num_threads>` from the command line
- slices the work across threads
- joins all threads
- prints elapsed time

Compiliation:
g++ -O2 -std=c++17 -pthread main.cpp -o perlin_threads
g++ -O2 -std=c++17 mainfrk.cpp -o perlin_single
