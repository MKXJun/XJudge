#include <X_Jun/List.h>
#include <stdbool.h>
#include <time.h>
struct ListNode *detectCycle(struct ListNode *head);
int main()
{
	struct ListNode * list, *node, *tail;
	int n, i, arr[100], link_pos;
	scanf("%d", &n);
	for (i = 0;i < n;++i)
		scanf("%d", arr + i);
	scanf("%d", &link_pos);
	node = tail = list = make_list(arr, n);
	while (tail && tail->next)
		tail = tail->next;
	if (link_pos >= 0)
	{
		for (i = 0;i < link_pos;++i)
			node = node->next;
		tail->next = node;
	}
	
	
	clock_t runtime = clock();
	node = detectCycle(list);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	if (node)
		printf("%d", node->val);
		
	if (tail)
		tail->next = NULL;
	
	while (list)
	{
		node = list;
		list = list->next;
		free(node);
	}
	return 0;
}
