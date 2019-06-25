#!/bin/bash


gcc -fopenmp tempNoCrit.c -o temp
echo "-----Execução com #omp critical fora do fora-----"
export OMP_NUM_THREADS=5
for i in {1..100000}
do { ./temp ; }
done
echo ""


