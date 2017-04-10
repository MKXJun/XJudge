#include <stdio.h>
#include <time.h>
int removeDuplicates(int* nums, int numsSize);
int main()
{
	int nums[100], n = 0, i;
	while(scanf("%d", nums + n) != EOF)
		n++;
		
	clock_t runtime = clock();
	int res = removeDuplicates(nums, n);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	
	
	for (i = 0;i < res;++i)
		printf("%d ", nums[i]);
	return 0;
}
