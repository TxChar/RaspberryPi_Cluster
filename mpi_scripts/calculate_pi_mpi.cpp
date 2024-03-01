#include <iostream>
#include <cmath>
#include <mpi.h>
#include <chrono>

const double PI = 3.14159265358979323846;

double comp_pi(int n, int myrank, int nprocs) {
    double h = 1.0 / n;
    double s = 0.0;
    for (int i = myrank + 1; i <= n; i += nprocs) {
        double x = h * (i - 0.5);
        s += 4.0 / (1.0 + x * x);
    }
    return s * h;
}

void prn_pi(double pi, double PI) {
    std::cout << "pi is approximately " << pi << ", error is " << std::abs(pi - PI) << std::endl;
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    int nprocs, myrank;
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    int n;
    double pi, mypi;

    if (myrank == 0) {
        int _n = 500; // Change number of interval you want.
        n = _n;
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Start timing
    auto start_time = std::chrono::high_resolution_clock::now();

    mypi = comp_pi(n, myrank, nprocs);

    MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (myrank == 0) {
        // End timing
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end_time - start_time;
        std::cout << "Time taken: " << elapsed_time.count() << " seconds" << std::endl;

        prn_pi(pi, PI);
    }

    MPI_Finalize();
    return 0;
}

