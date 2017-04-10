#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void moveZeroes(int* nums, int numsSize);

int main()
{
	int numsSize, *arr, i;
	scanf("%d", &numsSize);
	arr = (int *)malloc(sizeof (int) * numsSize);
	for (i = 0;i < numsSize;i++)
		scanf("%d", &arr[i]);
		
	clock_t runtime = clock();
	moveZeroes(arr, numsSize);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (i = 0;i < numsSize - 1;i++)
		printf("%d ", arr[i]);
	printf("%d\n", arr[numsSize - 1]);
	free(arr);
	return 0;
}
