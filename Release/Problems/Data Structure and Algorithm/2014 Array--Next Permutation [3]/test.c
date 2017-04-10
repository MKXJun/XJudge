#include <stdio.h>
#include <time.h>
void nextPermutation(int* nums, int numsSize);
int main()
{
	int nums[100], n, i;
	scanf("%d", &n);
	for (i = 0;i < n;++i)
		scanf("%d", nums + i);
	
	clock_t runtime = clock();
	nextPermutation(nums, n);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);	
	
	
	for (i = 0;i < n;++i)
		printf("%d ", nums[i]);
	puts("");
	return 0;
}
