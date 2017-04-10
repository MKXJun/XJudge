#include <X_Jun/List.h>
#include <time.h>
struct ListNode * delete_node(struct ListNode * list, int pos);
int main()
{
	int n, *nums, i, pos;
	struct ListNode * list, *node;
	
	scanf("%d", &n);
	nums = (int *)malloc(sizeof (int) * n);
	for (i = 0;i < n;++i)
		scanf("%d", nums + i);
	scanf("%d", &pos);
	list = make_list(nums, n);
	
	clock_t runtime = clock();
	list = delete_node(list, pos);
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
