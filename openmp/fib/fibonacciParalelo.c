#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define MAX 100010
#define LEN 25001

char seq[MAX][LEN];

void add(int a, int b) {
	int i, aux, s;
	for (i = 0, aux = 0; seq[a][i] != '\0' && seq[b][i] != '\0'; i++) {
		s = seq[a][i] + seq[b][i] + aux - '0' - '0';
		aux = s / 10;
		seq[a + 1][i] = s % 10 + '0';
	}
	while (seq[a][i] != '\0') {
		s = seq[a][i] + aux - '0';
		aux = s / 10;
		seq[a + 1][i] = s % 10 + '0';
		i++;
	}
	while (seq[b][i] != '\0') {
		s = seq[b][i] + aux - '0';
		aux = s / 10;
		seq[a + 1][i] = s % 10 + '0';
		i++;
	}
	if (aux != 0)
		seq[a + 1][i++] = aux + '0';
	seq[a + 1][i] = '\0';
}

int main() {
	int n, i, len, msec;
    clock_t before = clock();
	seq[0][0] = '0';
	seq[0][1] = '\0';
	seq[1][0] = '1';
	seq[1][1] = '\0';
	#pragma omp parallel for
	for (i = 2; i < MAX; i++){
		add(i - 1, i - 2);
	}
    clock_t difference = clock() - before;
    msec = difference * 1000 / CLOCKS_PER_SEC;
    printf("Tempo: %d segundos %d mili\n", msec/1000, msec%1000);
	scanf("%d", &n);

	len = strlen(seq[n]);
	for (i = 0; i <= len - 1; i++)
		printf("%c", seq[n][len - 1 - i]);
	printf("\n");
	fflush(stdout);

	return 0;
}