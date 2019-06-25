#!/bin/bash

gcc aula2606seq.c -o vseq
echo "-----Execução sequencial-----"
time ./vseq

echo ""
gcc -fopenmp aula2606.c -o v1
echo "-----Execução sem #omp critical-----"
export OMP_NUM_THREADS=5
time ./v1

echo ""
gcc -fopenmp aula2606crit.c -o v2
echo "-----Execução com #omp critical dentro do for-----"
export OMP_NUM_THREADS=5
time ./v2

echo ""
gcc -fopenmp aula2606temp.c -o v3
echo "-----Execução com #omp critical fora do fora-----"
export OMP_NUM_THREADS=5
time ./v3

