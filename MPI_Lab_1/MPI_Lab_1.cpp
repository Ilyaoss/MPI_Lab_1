// MPI_Lab_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include < stdio.h > 
#include "mpi.h"
#include < iostream > 
#include < windows.h > 
#include < ctime >

int main(int argc, char * argv[]) {
	int ProcNum, ProcRank;
	int buf[1] = {
		1
	};
	double RecvRank = 0;
	double t1;
	MPI_Status Status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	//for (int t = 0; t < 10; t++) {
		if (ProcRank == 0) {
			// Действия, выполняемые только процессом с рангом 0 
			//printf("\n Hello from process %3d, i have done", ProcRank); 
			t1 = MPI_Wtime();
			std::cout << "i have done " <<
				ProcRank << " time " <<
				t1 << "\n";
			fflush(stdout);
			for (int i = 1; i < ProcNum; i++) {
				MPI_Send(buf, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
			}
			int f = 0;
			for (int j = 1; j < 10000000; j++) {
				RecvRank += j;
				RecvRank /= j;
			}
			while (f < ProcNum - 1) {
				MPI_Recv(buf, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
				f++;
			}
			t1 = MPI_Wtime();
			std::cout << "i have done all " << ProcRank << " time " << t1 << "\n";
			fflush(stdout);
			//printf("\n Hello from process %3d, i have done all", ProcRank); 
		}
		else { // Сообщение, отправляемое всеми процессами, 
			   // кроме процесса с рангом 0 
			MPI_Recv(buf, 1, MPI_INT, 0,
				MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
			t1 = MPI_Wtime();
			std::cout << "i have read " <<
				ProcRank << " time " <<
				t1 << "\n";
			fflush(stdout);
			//printf("\n Hello from process %3d, i have red", ProcRank); 
			for (int j = 1; j < 10000000; j++) {
				RecvRank += j;
				RecvRank /= j;
			}
			MPI_Send(buf, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
			t1 = MPI_Wtime();
			std::cout << "i have send " <<
				ProcRank << " time " <<
				t1 << "\n";
			fflush(stdout);
			//printf("\n Hello from process %3d, i have send", ProcRank); 
		}
	//}
	MPI_Finalize();
	return 0;
}
