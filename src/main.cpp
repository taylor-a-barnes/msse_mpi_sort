#include<iostream>
#include<random>
#include<mpi.h>

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
  for (int ivalue = 0; ivalue < nvalues_per_rank; ivalue++) {
    sortvec[ivalue] = dist(mt);
  }

  // This is where you need to sort the values across all ranks

  // Print the final values
  // To ensure that everything is printed in the correct order, we loop over ranks
  for ( int irank = 0; irank < world_size; irank++) {
    if ( irank == my_rank ) {
       std::cout << "Values on rank " << my_rank << std::endl;
       for ( int ivalue = 0; ivalue < nvalues_per_rank; ivalue++) {
         std::cout << "   Index: " << ivalue << "   Value: " << sortvec[ivalue] << std::endl;
       }
       std::cout << std::flush;
    }
    // The barrier ensures that the preceeding rank has finished printing before moving to the next
    MPI_Barrier(MPI_COMM_WORLD);
  }

  MPI_Finalize();
}
