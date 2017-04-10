#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** generateMatrix(int n);
int main()
{
	int n, i, j;
	scanf("%d", &n);
	
	clock_t runtime = clock();
	int ** matrix = generateMatrix(n);
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
