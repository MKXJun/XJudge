#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int* spiralOrder(int** matrix, int matrixRowSize, int matrixColSize);

int main()
{
	int m, n, i, j;
	scanf("%d%d", &m, &n);
	int ** matrix = (int **)malloc(sizeof(int*) * m);
	for (i = 0;i < m;++i)
		matrix[i] = (int *)malloc(sizeof (int) * n);
	for (i = 0;i < m;++i)
		for (j = 0;j < n;++j)
			scanf("%d", &matrix[i][j]);
				
	clock_t runtime = clock();
	int * res = spiralOrder(matrix, m, n);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (i = 0;i < m * n;++i)
		printf("%d ", res[i]);
	free(res);
	for (i = 0;i < m;++i)
		free(matrix[i]);
	free(matrix);
	return 0;
}
