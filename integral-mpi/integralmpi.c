#include <stdio.h>
#include <mpi.h> //usando a versão 4.0.1 do openmpi
void main(int argc, char** argv) {
    int my_rank;
    int num_processos; // número de processos
    float a=0.0, b=1.0; // intervalo a calcular
    int num_trap=1024; // número de trapezóides
    float h; // base do trapezóide
    float local_a, local_b; // intervalo local
    int local_n; // número de trapezóides local
    float integral; // integral no meu intervalo
    float total; // integral total
    int source; // remetente da integral
    int dest=0; // destino das integrais (nó 0)
    int tag=200; // tipo de mensagem (único)
    MPI_Status status;
    float calcula(float local_a, float local_b, int local_n, float h);
    int resto;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processos);

    h = (b-a) / num_trap;
    local_n = num_trap / num_processos;
    resto = num_trap%num_processos;
    if(my_rank < resto){
        local_n++;
        local_a = local_a = a + my_rank * local_n * h;
    }
    else{
        local_a = a + (resto * (local_n+1) * h) + (my_rank - resto) * local_n * h;
    }
    local_b = local_a + local_n * h;

    integral = calcula(local_a, local_b, local_n, h);

    printf("RANK: %d, LOCAL_A: %f, LOCAL_B: %f, LOCAL_N: %d, RESTO: %d, INTEGRAL: %f\n", my_rank, local_a, local_b, local_n, resto, integral);
    if(my_rank == 0) {
        total = integral;
        for(source=1; source<num_processos; source++) {
            MPI_Recv(&integral, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status);
            total +=integral;
        }
    } else {
        MPI_Send(&integral, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD);
    }
    if(my_rank == 0) printf("Resultado: %f\n", total);
    MPI_Finalize();
}
float calcula(float local_a, float local_b, int local_n, float h) {
    float integral;
    float bEsq, bDir, i;
    float f(float x); // função a integrar
    //integral = ( f(local_a) + f(local_b) ) /2.0;
    integral = 0;
    bEsq = local_a;
    bDir = bEsq + h;
    //integral do exemplo estava errada
    //integral abaixo calculada utilizando ((b+B)*h/2) para todos os trapezios no intervalo
    for( i=0; i<local_n; i++) {
        integral += ( (f(bEsq) + f(bDir)) * h)/2;
        bEsq += h;
        bDir = bEsq + h;
    }
    printf("%f, LOCAL_A %f\n", integral, local_a);
    //integral *= h;
    return integral;
}

float f(float x) {
    float fx; // valor de retorno

    // esta é a função a integrar
    // exemplo: função quadrática
    fx = x * x;

    return fx;
}