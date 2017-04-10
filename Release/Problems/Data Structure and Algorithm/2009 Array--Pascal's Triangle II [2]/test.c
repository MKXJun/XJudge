#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int* getRow(int rowIndex, int* returnSize);

int main()
{
	int Size, n, i;
	int * res;
	scanf("%d", &n);
	res = getRow(n, &Size);
	
	clock_t runtime = clock();
	res = getRow(n, &Size);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (i = 0;i < Size;++i)
		printf("%d ", res[i]);
	puts("");
	free(res);
	return 0;
}
