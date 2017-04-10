#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void rotate(int** matrix, int matrixRowSize, int matrixColSize);
int main()
{
	int ** matrix, n, i, j;
	scanf("%d", &n);
	matrix = (int **)malloc(sizeof (int *) * n);
	for (i = 0;i < n;++i)
		matrix[i] = (int *)malloc(sizeof (int) * n);
	for (i = 0;i < n;++i)
		for (j = 0;j < n;++j)
			scanf("%d", &matrix[i][j]);
			
	clock_t runtime = clock();
	rotate(matrix, n, n);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);			
	
	
	
	for (i = 0;i < n;++i)
	{
		for (j = 0;j < n;++j)
			printf("%d ", matrix[i][j]);
		puts("");
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}
