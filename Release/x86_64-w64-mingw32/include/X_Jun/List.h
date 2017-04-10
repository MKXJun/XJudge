/*
	¼òÒ×°æCÓïÑÔList.h  
	×÷Õß£ºX_Jun 
*/

#ifndef _LIST_H_
#define _LIST_H_
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
typedef struct ListNode {
	int val;
	struct ListNode * next;
	struct ListNode * prev;
} ListNode;
ListNode before_begin;
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

List * ListCreate()
{
	List * list = (List *)malloc(sizeof (List));
	memset(list, 0, sizeof (List));
	return list;
}

void ListPushFront(List * list, int val)
{
	ListNode * node = (ListNode *)malloc(sizeof (ListNode));
	node->val = val;
	node->next = list->head;
	node->prev = NULL;
	if (list->size)
		list->head->prev = node;
	list->head = node;
	if (!(list->size))
		list->tail = list->head;
	list->size++;
}

void ListPopFront(List * list)
{
	assert(list->size);
	ListNode * node = list->head;
	list->head = list->head->next;
	list->head->prev = NULL;
	free(node);
	list->size--;
	if (!(list->size))
		list->tail = NULL;
}

void ListPushBack(List * list, int val)
{
	ListNode * node = (ListNode *)malloc(sizeof (ListNode));
	node->val = val;
	node->next = NULL;
	node->prev = list->tail;
	if (list->size)
		list->tail->next = node;
	list->tail = node;
	if (!(list->size))
		list->head = list->tail;
	list->size++;
}

void ListPopBack(List * list)
{
	assert(list->size);
	ListNode * node = list->tail;
	list->tail = list->tail->prev;
	list->tail->next = NULL;
	free(node);
	list->size--;
	if (!(list->size))
		list->head = NULL;
}

void ListInsert(List * list, int pos, int val)
{
	assert(pos >= 0 && pos <= list->size);
	if (pos == 0)
	{
		ListPushFront(list, val);
		return;
	}
	else if (pos == list->size)
	{
		ListPushBack(list, val);
		return;
	}
	ListNode * node = (ListNode *)malloc(sizeof (ListNode)), *node2;
	node->val = val;
	list->size++;
	int i;
	for (i = 1, node2 = list->head;i < pos;++i)
		node2 = node2->next;
	node->next = node2->next;
	node->next->prev = node;
	node2->next = node;
	node2->next->prev = node2;		
}

void ListErase(List * list, int beg, int end)
{
	if (beg == end)
		return;
	assert(beg >= 0 && beg < list->size && end >= 0 && end <= list->size && beg <= end);
	ListNode * node = &before_begin, *delete_node;
	node->next = list->head;
	int i;
	for (i = 0;i < beg;++i)
		node = node->next;
	for (;i < end;++i)
	{
		delete_node = node->next;
		node->next = node->next->next;
		free(delete_node);
	}
	if (node->next)
		node->next->prev = node;
	list->head = before_begin.next;
	list->head->prev = NULL;
	if (!(node->next))
		list->tail = node;
	list->size -= end - beg;
	memset(&before_begin, 0, sizeof (ListNode));
}

void ListClear(List * list)
{
	if (!(list->size))
		return;
	ListNode * node;
	while (list->head != list->tail)
	{
		node = list->head;
		list->head = list->head->next;
		free(node);
	}
	free(list->head);
	list->head = list->tail = NULL;
	list->size = 0;
}

void ListFree(List * list)
{
	ListNode * node;
	while (list->size--)
	{
		node = list->head;
		list->head = list->head->next;
		free(node);
	}
	free(list);
}
#endif
