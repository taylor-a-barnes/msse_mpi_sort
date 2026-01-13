#include <bits/stdc++.h>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <mpi.h>
#include <random>

int main(int argc, char *argv[]) {
  MPI_Init(&argc, &argv);

  int my_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // We will initialize the random number seed with the process rank
  std::mt19937 mt = std::mt19937(my_rank);
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  // Create a set of random values on each rank
  int nvalues_per_rank = 10;
  std::vector<double> sortvec(nvalues_per_rank);
  for (int ivalue = 0; ivalue < nvalues_per_rank; ++ivalue) {
    sortvec[ivalue] = dist(mt);
  }

  // Sort the vector within the rank
  // Note: the sort function could be useful to remember later
  std::sort(sortvec.begin(), sortvec.end());

  /* This is where you need to sort the values across all ranks
     REMEMBER: Be careful to limit your use of memory.
               You must not at any point have any rank store all the values of sortvec from all ranks
               (unless world_size is very small - less than 3).
  */

  // Print the final values
  // To ensure that everything is printed in the correct order, we loop over ranks
  for ( int irank = 0; irank < world_size; irank++) {
    if ( irank == my_rank ) {
       std::cout << "Values on rank " << my_rank << '\n';
       for ( int ivalue = 0; ivalue < nvalues_per_rank; ivalue++) {
         std::cout << "   Index: " << ivalue << "   Value: " << sortvec[ivalue] << '\n';
       }
       std::cout << std::flush;
    }
    // Note: MPI_Barrier does not ensure that I/O buffers have been written, so the result of this is technically undefined
    // The call to sleep_for should largely ensure that the printing is well behaved
    MPI_Barrier(MPI_COMM_WORLD);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  MPI_Finalize();
}
