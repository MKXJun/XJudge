#include <stdio.h>
#include <time.h>
int majorityElement(int* nums, int numsSize);
int main()
{
	int nums[100], n = 0, i;
	while (~scanf("%d", nums + n))
		n++;
		
	clock_t runtime = clock();
	printf("%d\n", majorityElement(nums, n));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	return 0;
}