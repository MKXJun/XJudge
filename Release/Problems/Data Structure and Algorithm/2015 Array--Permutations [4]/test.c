#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int** permuteUnique(int* nums, int numsSize, int* returnSize);
int main()
{
	int nums[15], n = 0, returnSize = 0, i, j;
	int ** res;
	while (~scanf("%d", nums + n))
		n++;
		
	clock_t runtime = clock();
	res = permuteUnique(nums, n, &returnSize);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	putchar('[');
	for (i = 0;i < returnSize - 1;++i)
	{
		putchar('[');
		for (j = 0;j < n - 1;++j)
			printf("%d,", res[i][j]);
		if (n)
			printf("%d", res[i][n - 1]);
		printf("],");
	}
	if (returnSize)
	{
		putchar('[');
		for (j = 0;j < n - 1;++j)
			printf("%d,", res[i][j]);
		if (n)
			printf("%d", res[i][n - 1]);
		putchar(']');
	}
	putchar(']');
	for (i = 0;i < returnSize;++i)
		free(res[i]);
	free(res);
	return 0;
}
