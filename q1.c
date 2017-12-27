#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv){
	int i, rank, size, offset, nints, N=4;

	MPI_File fhw;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);

	int buf[N];
	for(i=0; i<N;i++)
		buf[i] = rank*N + i;

	offset = rank*(N/size)*sizeof(int);

	MPI_File_open(MPI_COMM_WORLD, "datafile.txt", MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &fhw);

	// Added code
	MPI_File_write_at(fhw,offset,&buf,(N/size),MPI_INT,&status);

	MPI_File_close(&fhw);

	MPI_File_open(MPI_COMM_WORLD,"datafile.txt",MPI_MODE_RDONLY,MPI_INFO_NULL,&fhw);

	//Added code
	MPI_File_read_at(fhw, offset + i*sizeof(int), buf, 1, MPI_INT, &status);

	printf("\nProcess %d read %d %d %d %d\n",rank, buf[0],buf[1],buf[2],buf[3]);

	MPI_File_close(&fhw);

	MPI_Finalize();

	return 0;
}
