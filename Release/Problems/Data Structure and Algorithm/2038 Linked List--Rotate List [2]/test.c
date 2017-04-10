#include <X_Jun/List.h>
#include <time.h>

struct ListNode* rotateRight(struct ListNode* head, int k);
int main()
{
	int n, i, k, *nums;
	struct ListNode * list, *node;
	
	scanf("%d", &n);
	nums = (int *)malloc(sizeof (int) * n);
	for (i = 0;i < n;++i)
		scanf("%d", nums + i);
	scanf("%d", &k);
	list = make_list(nums, n);
	
	clock_t runtime = clock();
	list = rotateRight(list, k);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	
	list_output(list);
	
	while (list)
	{
		node = list;
		list = list->next;
		free(node);
	}
	free(nums);
	
	return 0;
}
