#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


 
#define LEN 256
int main (int argc, char* argv[])
{
	MPI_Init(&argc,&argv);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    FILE * fp;
   	int i;
   	int n;
   	char buffer[50]="";
   	sprintf(buffer, "filename%d.txt",world_rank);
   	srand((unsigned) world_rank+1);
   	fp = fopen (buffer,"w");
   	for(i = 0; i < 250000000;i++){
   		int r = rand() % 1000000000;
    	fprintf (fp, "%d\n",r);
    	if (i==0){
    		printf("%d\n", r);
    	}
   	}
 
   /* close the file*/  
   fclose (fp);

    // Finalize the MPI environment.
    MPI_Finalize();
   
   return 0;
}