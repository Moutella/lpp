#include <stdio.h>
#include <omp.h>

#define NUMFOR 50000

int main(){
    
    int a[NUMFOR];
    for(int i = 0; i < NUMFOR; i++){
        a[i] = i;
    }
    int n = NUMFOR;
    int value, i;
    long sum;
    sum = 0;
    #pragma omp parallel shared(a, sum) private(value, i)
    {
       long temp = 0;
        #pragma omp for
        for(int i=0; i< n; i++){
            value = a[i];
            temp += value;
        }
        sum = sum + temp;
    }
    printf("\nSUM: %ld", sum);
}