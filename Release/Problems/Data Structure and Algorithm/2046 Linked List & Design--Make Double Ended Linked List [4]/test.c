#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
	int val;
	struct ListNode * next;
	struct ListNode * prev;
} ListNode;

typedef struct {
	ListNode * head;
	ListNode * tail;
	int size;
} List;
List * ListCreate();
void ListPushFront(List * list, int val);
void ListPopFront(List * list);
void ListPushBack(List * list, int val);
void ListPopBack(List * list);
void ListInsert(List * list, int pos, int val);
void ListErase(List * list, int beg, int end);
void ListClear(List * list);
void ListFree(List * list);

void CallFunc(List ** list, char * func)
{
	if (!strcmp(func, "create"))
		*list = ListCreate();
	else if (!strcmp(func, "pushfront"))
	{
		int val;
		scanf("%d", &val);
		ListPushFront(*list, val);
	}
	else if (!strcmp(func, "popfront"))
		ListPopFront(*list);
	else if (!strcmp(func, "pushback"))
	{
		int val;
		scanf("%d", &val);
		ListPushBack(*list, val);
	}
	else if (!strcmp(func, "popback"))
		ListPopBack(*list);
	else if (!strcmp(func, "insert"))
	{
		int pos, val;
		scanf("%d%d", &pos, &val);
		ListInsert(*list, pos, val);
	}
	else if (!strcmp(func, "erase"))
	{
		int beg, end;
		scanf("%d%d", &beg, &end);
		ListErase(*list, beg, end);
	}
	else if (!strcmp(func, "clear"))
		ListClear(*list);
	else if (!strcmp(func, "free"))
		ListFree(*list);
	else if (!strcmp(func, "print"))
	{
		ListNode * node = (*list)->head;
		while (node)
		{
			printf("%d ", node->val);
			node = node->next;
		}
		puts("");
		node = (*list)->tail;
		while (node)
		{
			printf("%d ", node->val);
			node = node->prev;
		}
		puts("");
	}
}



int main()
{
	char str[100];
	List * list;
	clock_t runtime = clock();
	while (~scanf("%s", str))
		CallFunc(&list, str);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	return 0;
}
