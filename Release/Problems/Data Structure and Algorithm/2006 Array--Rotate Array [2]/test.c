#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rotate(int* nums, int numsSize, int k);
int main()
{
	int *nums, n, k, i;
	scanf("%d", &n);
	nums = (int *)malloc(sizeof (int) * n);
	for (i = 0;i < n;++i)
		scanf("%d", nums + i);
	scanf("%d", &k);
	
	clock_t runtime = clock();
	rotate(nums, n, k);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);	
	
	
	for (i = 0;i < n;++i)
		printf("%d ", nums[i]);
	free(nums);
	printf("\n%d\n", n);	 
	return 0;
}

