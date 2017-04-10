#include <stdio.h>
#include <time.h>

void merge(int* nums1, int m, int* nums2, int n);
int main()
{
	int nums1[100], nums2[100];
	int n1, n2;
	int i;
	scanf("%d", &n1);
	for (i = 0;i < n1;++i)
		scanf("%d", nums1 + i);
	scanf("%d", &n2);
	for (i = 0;i < n2;++i)
		scanf("%d", nums2 + i);
		
	
	
	clock_t runtime = clock();
	merge(nums1, n1, nums2, n2);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (i = 0;i < n1 + n2;++i)
		printf("%d ", nums1[i]);
	puts("");
	return 0;
}
