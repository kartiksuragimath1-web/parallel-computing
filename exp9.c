#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int value, sum, prod, max, min;
    int all_sum, all_prod, all_max, all_min;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* Each process gets a value based on its rank */
    value = rank + 1;

    /* MPI_Reduce: results are available only at root process */
    MPI_Reduce(&value, &sum, 1, MPI_INT, MPI_SUM, 0,
               MPI_COMM_WORLD);

    MPI_Reduce(&value, &prod, 1, MPI_INT, MPI_PROD, 0,
               MPI_COMM_WORLD);

    MPI_Reduce(&value, &max, 1, MPI_INT, MPI_MAX, 0,
               MPI_COMM_WORLD);

    MPI_Reduce(&value, &min, 1, MPI_INT, MPI_MIN, 0,
               MPI_COMM_WORLD);

    /* MPI_Allreduce: results are available at every process */
    MPI_Allreduce(&value, &all_sum, 1, MPI_INT, MPI_SUM,
                  MPI_COMM_WORLD);

    MPI_Allreduce(&value, &all_prod, 1, MPI_INT, MPI_PROD,
                  MPI_COMM_WORLD);

    MPI_Allreduce(&value, &all_max, 1, MPI_INT, MPI_MAX,
                  MPI_COMM_WORLD);

    MPI_Allreduce(&value, &all_min, 1, MPI_INT, MPI_MIN,
                  MPI_COMM_WORLD);

    /* Print MPI_Reduce results only at root */
    if (rank == 0) {
        printf("--- Results using MPI_Reduce (only root prints) ---\n");
        printf("Sum = %d\n", sum);
        printf("Product = %d\n", prod);
        printf("Max = %d\n", max);
        printf("Min = %d\n", min);
    }

    /* Print results from every process */
    printf("Process %d has value %d\n", rank, value);

    printf("Process %d sees (MPI_Allreduce): "
           "Sum=%d, Prod=%d, Max=%d, Min=%d\n",
           rank, all_sum, all_prod, all_max, all_min);

    MPI_Finalize();

    return 0;
}
   
