#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int removeElement(int* nums, int numsSize, int val);

int main()
{
	int numsSize, val, *arr, i;
	scanf("%d", &numsSize);
	arr = (int *)malloc(sizeof (int) * numsSize);
	for (i = 0;i < numsSize;i++)
		scanf("%d", &arr[i]);
	scanf("%d", &val);
	
	clock_t runtime = clock();
	int res = removeElement(arr, numsSize, val);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (i = 0;i < res;i++)
		printf("%d ", arr[i]);
	free(arr);
	return 0;
}
