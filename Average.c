#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main (int argc, char* argv[])
{
	MPI_Init(&argc,&argv);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    printf("My rank is: %d\n",world_rank );
    FILE * fp;
    char str[60];
    char buffer[50]="";
   	sprintf(buffer, "filename%d.txt",world_rank);
   	fp = fopen(buffer , "r");
   	if(fp == NULL) {
      perror("Error opening file");
      return(-1);
   	}
   	long sum=0;
   	long count=0;
   	while( fgets (str, 60, fp)!=NULL ) {
   		long val = atol(str);
     	sum+= val;while( fgets (str, 60, fp)!=NULL ) {
   		long val = atol(str);
     	sum+= val;
     	count++;
   	}
     	count++;
   	}
   	fclose(fp);
	long* vals = (long *)malloc(1 * sizeof(long));   
   	if(world_rank!=0){
   		*vals =sum;
   		*(vals+1) =count;
   		printf("Sending from: %d\n", world_rank);;
   		MPI_Send(vals,2,MPI_LONG,0,0,MPI_COMM_WORLD);
   	}
   	else{
   		long globalSum = sum;
   		long globalCount = count;

   		MPI_Recv(vals,2,MPI_LONG,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
   		globalSum+= *vals;
   		globalCount+=*(vals+1);

   		vals = (long *)malloc(2 * sizeof(long));    
   		MPI_Recv(vals,2,MPI_LONG,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
   		globalSum+= *vals;
   		globalCount+=*(vals+1);
   		

   		vals = (long *)malloc(2 * sizeof(long));    
   		MPI_Recv(vals,2,MPI_LONG,3,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
   		globalSum+= *vals;
   		globalCount+=*(vals+1);

   		printf("GlobalSum %li , GlobalCount %li \n", globalSum, globalCount);

   		long globalMean = globalSum/globalCount;

   		printf("GlobalMean : %li\n",globalMean );


   	}
    // Finalize the MPI environment.
    MPI_Finalize();
   
   return 0;
}