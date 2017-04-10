/*
	简易版C语言Vector  
	作者：X_Jun 
*/

#ifndef _VECTOR_H_
#define _VECTOR_H_ 

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
typedef struct {
	int * data;
	size_t size;
	size_t capacity;
} Vector;

Vector * VectorCreate(size_t numsOfElement)
{
	Vector * vec = (Vector *)malloc(sizeof (Vector));
	vec->data = (int *)malloc(sizeof (int) * numsOfElement);
	memset(vec->data, 0, sizeof (int) * numsOfElement);
	vec->size = numsOfElement;
	vec->capacity = numsOfElement;
	return vec;
}

void VectorReallocate(Vector * vec, int newSize)
{
	int * Data = (int *)realloc(vec->data, sizeof (int) * newSize);
		
	if (Data)
		vec->data = Data;
	else if (newSize)
	{
		printf("\n内存分配失败！\n");
		exit(1);
	}
	
	vec->capacity = newSize;
}

void VectorPushBack(Vector * vec, int val)
{
	if (vec->size == vec->capacity)
		VectorReallocate(vec, vec->capacity ? vec->capacity * 2 : 1);
	vec->data[vec->size++] = val;
}

void VectorPopBack(Vector * vec)
{
	assert(vec->size);
	vec->size--;
	if (vec->size < vec->capacity / 4)
		VectorReallocate(vec, vec->capacity / 2);
}

void VectorClear(Vector * vec)
{
	VectorReallocate(vec, 1);
	vec->size = 0;
}

void VectorInsertValue(Vector * vec, size_t pos, int val)
{
	assert(pos >= 0 && pos < vec->size);
	if (vec->size == vec->capacity)
		VectorReallocate(vec, vec->capacity ? vec->capacity * 2 : 1);
	int i;
	for (i = vec->size;i > pos;i--)
		vec->data[i] = vec->data[i - 1];
	vec->data[pos] = val;
	vec->size++;
}

void VectorErase(Vector * vec, size_t beg, size_t end)
{
	assert(beg >= 0 && beg < vec->size && end >= 0 && end < vec->size && end >= beg);
	size_t i, j;
	for (i = beg, j = end;j < vec->size;++i, ++j)
		vec->data[i] = vec->data[j];
	vec->size -= end - beg;
	if (vec->size < vec->capacity / 4)
		VectorReallocate(vec, vec->capacity / 2);
}


void VectorFree(Vector * vec)
{
	free(vec->data);
	free(vec);
}

#endif
