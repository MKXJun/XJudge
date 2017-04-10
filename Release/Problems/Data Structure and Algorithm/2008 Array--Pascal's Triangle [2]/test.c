#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int** generate(int numRows, int** columnSizes);

int main()
{
	int n, **nums, i, j, *Sizes;
	scanf("%d", &n);
	
	clock_t runtime = clock();
	nums = generate(n, &Sizes);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (i = 0;i < n;++i)
	{
		for (j = 0;j < Sizes[i];++j)
			printf("%d ", nums[i][j]);
		puts("");
	}
	
	for (i = 0;i < n;++i)
		free(nums[i]);
	free(nums);
	free(Sizes);
}
