#include <stdio.h>
#include <ctime>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <mpi.h>

#include <random>


double pi_calc(long int n) {
    
    // Write your code below
    ////////////////////////////////////////

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    long int points_per_process = n / size;
    long int local_count = 0;


    std::mt19937_64 generator(rank + time(nullptr));
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    // Monte Carlo simulation
    for (long int i = 0; i < points_per_process; ++i) {
        double x = distribution(generator);
        double y = distribution(generator);
        if (x * x + y * y <= 1.0) {
            ++local_count;
        }
    }

    // Reduce all local counts to get the global count
    long int global_count;
    MPI_Reduce(&local_count, &global_count, 1, MPI_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    return (4.0 * global_count) / n; 
}
