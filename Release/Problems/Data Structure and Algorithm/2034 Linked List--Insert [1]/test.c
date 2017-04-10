#include <X_Jun/List.h>
#include <time.h>
struct ListNode * insert(struct ListNode * node, int pos, int val);
int main()
{
	int * nums, n, i, pos, val;
	struct ListNode * list, *node;
	
	scanf("%d", &n);
	nums = (int *)malloc(sizeof (int) * n);
	for (i = 0;i < n;++i)
		scanf("%d", nums + i);
	list = make_list(nums, n);
	scanf("%d%d", &pos, &val);
	
	clock_t runtime = clock();
	if (!pos)
		list = node = insert(list, pos, val);
	else
		node = insert(list, pos, val);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	
	list_output(node);
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
