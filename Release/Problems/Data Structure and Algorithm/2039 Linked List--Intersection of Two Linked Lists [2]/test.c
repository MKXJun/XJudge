#include <X_Jun/List.h>
#include <time.h>
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB);

int main()
{
	struct ListNode * listA = NULL, *listB = NULL, *tailB = NULL, *node;
	int nA, nB, in, i, val, numsA[100], numsB[100];
	scanf("%d%d%d", &nA, &nB, &in);
	
	for (i = 0;i < nA;++i)
		scanf("%d", numsA + i);
	for (i = 0;i < nB;++i)
		scanf("%d", numsB + i);
	listA = make_list(numsA, nA);
	listB = make_list(numsB, nB);
	for (i = 0, node = listA;i < in;++i, node = node->next)
		continue; 
	for (tailB = listB;tailB && tailB->next;tailB = tailB->next)
		continue;
	if (tailB)
		tailB->next = node;
		
	clock_t runtime = clock();
	struct ListNode * res = getIntersectionNode(listA, listB);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);	
		
	
	if (res)
		printf("%d", res->val);
	
	if (tailB)
		tailB->next = NULL;
		
	while (listA)
	{
		node = listA;
		listA = listA->next;
		free(node);
	}
	while (listB)
	{
		node = listB;
		listB = listB->next;
		free(node);
	}
	
	return 0;
}
