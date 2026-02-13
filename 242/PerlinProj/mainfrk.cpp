#include <iostream>
#include "perlin.h"

#include <vector>
#include <chrono>

using namespace std;

Noise noice;

// A simple integer grid point (x, y).
struct Point {
    int x, y;
};

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    // Grid size (64x64 points)
    const int cols = 64;
    const int rows = 64;

    // Build list of points on the grid
    vector<Point> points;
    points.reserve(cols * rows);

    for (int x = 0; x < cols; ++x) {
        for (int y = 0; y < rows; ++y) {
            points.push_back({x, y});
        }
    }

    // Seed noise generator (deterministic)
    noice.seed = 12345;

    // Start timing
    auto start_t = chrono::steady_clock::now();

    // Compute noise color for each point (single-thread)
    double d = 0.0;
    for (const Point& p : points) {
        d = noice.getColor(p.x, p.y, 0.1, 1);
    }
    (void)d;

    // Stop timing
    auto end_t = chrono::steady_clock::now();

    cout << "Elapsed time in ms: "
         << chrono::duration_cast<chrono::milliseconds>(end_t - start_t).count()
         << "\n";

    return 0;
}
