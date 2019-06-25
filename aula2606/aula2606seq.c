#include <stdio.h>

#define NUMFOR 50000

int main(){
    int a[NUMFOR];
    for(int i = 0; i < NUMFOR; i++){
        a[i] = i;
    }
    double temp = 0.0;
    int n = NUMFOR;
    int value,i;
    long sum;
    sum = 0;
    for(int i=0; i< n; i++){
        value = a[i];
        sum = sum + value;
    }
    printf("\nSUM: %ld\n", sum);
}