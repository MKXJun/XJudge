#include <X_Jun/List.h>
#include <time.h>
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);
int main()
{
	struct ListNode * list1, *list2, *node, *l;
	int i, n1, n2;
	int nums1[200], nums2[200];
	scanf("%d%d", &n1, &n2);
	for (i = 0; i < n1; ++i)
		scanf("%d", nums1 + i);
	for (i = 0; i < n2; ++i)
		scanf("%d", nums2 + i);
	list1 = make_list(nums1, n1);
	list2 = make_list(nums2, n2);
	
	clock_t runtime = clock();
	l = addTwoNumbers(list1, list2);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	list_output(l);
	if (l != list1)
		while (list1)
		{
			node = list1;
			list1 = list1->next;
			free(node);	
		}
	if (l != list2)
		while (list2)
		{
			node = list2;
			list2 = list2->next;
			free(node);
		}
	while (l)
	{
		node = l;
		l = l->next;
		free(node);
	}
	return 0;
}
