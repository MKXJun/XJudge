#include <X_Jun/List.h>
#include <time.h>

struct ListNode* oddEvenList(struct ListNode* head);

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
	list_output(oddEvenList(list));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	
	while (list)
	{
		node = list;
		list = list->next;
		free(node);
	}
	free(nums);
	
	return 0;
}