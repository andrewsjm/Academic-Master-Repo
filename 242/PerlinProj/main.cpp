#include <iostream>
#include "perlin.h"

#include <thread>
#include <vector>
#include <chrono>
#include <stdexcept>   // std::invalid_argument, std::out_of_range

using namespace std;

// Global noise generator instance used by all threads.
Noise noice;

// A simple integer grid point (x, y).
struct Point {
    int x, y;
};

// Global list of points (one per pixel / grid cell).
// Each worker will read from this vector.
vector<Point> points;

// Worker describes a slice of the 'points' vector to process.
struct Worker {
    int start;  // inclusive index into points[]
    int end;    // exclusive index into points[]

    void run() {
        // Local variable so threads don't share the same 'd'
        // (we aren't using the value, just forcing the computation).
        double d = 0.0;

        // Process points[start .. end-1]
        for (int i = start; i < end; ++i) {
            d = noice.getColor(points[i].x, points[i].y, 0.1, 1);
        }

        (void)d;
    }
};

static int parse_num_threads(int argc, char** argv) {
    // Expect: ./a.out <num_threads>
    if (argc < 2 || argv[1] == nullptr) {
        cerr << "Usage: " << argv[0] << " <num_threads>\n";
        cerr << "Example: " << argv[0] << " 4\n";
        exit(1);
    }

    try {
        int n = stoi(argv[1]);
        if (n <= 0) {
            cerr << "Error: num_threads must be > 0\n";
            exit(1);
        }
        return n;
    } catch (const invalid_argument&) {
        cerr << "Error: num_threads must be an integer (got '" << argv[1] << "')\n";
        exit(1);
    } catch (const out_of_range&) {
        cerr << "Error: num_threads out of range (got '" << argv[1] << "')\n";
        exit(1);
    }
}

int main(int argc, char** argv) {
    // Grid size (64x64 points)
    const int cols = 64;
    const int rows = 64;

    // Parse number of threads from command line safely
    const int num_threads = parse_num_threads(argc, argv);

    // Fill the global points vector with all (x,y) coordinates
    points.reserve(cols * rows);
    for (int x = 0; x < cols; ++x) {
        for (int y = 0; y < rows; ++y) {
            points.push_back({x, y});
        }
    }

    // Seed the noise generator for deterministic output
    noice.seed = 12345;

    // Start timing
    auto start_t = chrono::steady_clock::now();

    // Create threads
    vector<thread> threads;
    threads.reserve(num_threads);

    // Split the work into roughly equal slices.
    const int total = cols * rows;
    const int slice = total / num_threads;

    // Launch one worker per thread
    for (int i = 0; i < num_threads; ++i) {
        Worker* w = new Worker;

        // Compute the index range for this worker.
        // Last worker takes the remainder so no points missed.
        w->start = i * slice;
        w->end   = (i == num_threads - 1) ? total : (i + 1) * slice;

        threads.emplace_back(&Worker::run, w);

    }

    // Join all threads
    for (auto& t : threads) {
        t.join();
    }

    // Stop timing
    auto end_t = chrono::steady_clock::now();

    cout << "Number of threads: " << num_threads << "\n";
    cout << "Elapsed time in ms: "
         << chrono::duration_cast<chrono::milliseconds>(end_t - start_t).count()
         << "\n";

    return 0;
}
