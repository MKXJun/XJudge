#include <X_Jun/List.h>
#include <stdbool.h>
#include <time.h>
bool isPalindrome(struct ListNode* head);
int main()
{
	int n, i, *nums;
	struct ListNode * list, *node;
	
	scanf("%d", &n);
	nums = (int *)malloc(sizeof (int) * n);
	for (i = 0;i < n;++i)
		scanf("%d", nums + i);
	list = make_list(nums, n);
	
	clock_t runtime = clock();
	printf("%d\n", isPalindrome(list));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	
	free(nums);
	
	return 0;
}
