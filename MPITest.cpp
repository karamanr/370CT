#include <iostream>
#include "mpi.h"
#include <cstring>
int main(int argc, char** argv) {

	// Initialize the MPI environment
	MPI_Init(NULL, NULL);
	char node_name[MPI_MAX_PROCESSOR_NAME];
	int rank, size, namelen;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Get_processor_name(node_name, &namelen);
	memset(node_name + namelen, 0, MPI_MAX_PROCESSOR_NAME - namelen);

	if (rank == 0) {
		std::cout << std::endl;
		std::cout << " > #################" << std::endl;
		std::cout << "Size test: " << size << std::endl;
		std::cout << " > #################" << std::endl;
		std::cout << "Rank test " << rank << std::endl;
		std::cout << " > #################" << std::endl;
		std::cout << "Node name test: " << node_name << std::endl;
		std::cout << " > #################" << std::endl;
		std::cout << "Memory test \n" << memset << std::endl;
	}

	MPI_Finalize();
}