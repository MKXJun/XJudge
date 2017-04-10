#include <X_Jun/List.h>
#include <time.h>

struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2);

int main()
{
	int n, i, *nums;
	struct ListNode * list1, *list2, *list, *node;
	
	scanf("%d", &n);
	nums = (int *)malloc(sizeof (int) * n);
	for (i = 0;i < n;++i)
		scanf("%d", nums + i);
	list1 = make_list(nums, n);
	free(nums);
	
	scanf("%d", &n);
	nums = (int *)malloc(sizeof (int) * n);
	for (i = 0;i < n;++i)
		scanf("%d", nums + i);
	list2 = make_list(nums, n);
	free(nums);
	
	clock_t runtime = clock();
	list = mergeTwoLists(list1, list2);
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
	
	return 0;
}
