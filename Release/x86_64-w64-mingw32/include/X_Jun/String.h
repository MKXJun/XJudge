/*
	简易版C语言String  
	作者：X_Jun 
*/

#ifndef _STRING_H_
#define _STRING_H_
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
typedef struct {
	char * c_str;
	int length;
	int capacity;
} String;

String * StringCreate();
void StringReallocate(String * obj, int newSize);
void StringAssign(String * obj, const char * str);
void StringAppend(String * obj, const char * str);
bool StringEqual(String * obj, const char * str);
void StringPushBack(String * obj, int ch);
void StringPopBack(String * obj);
void StringInsert(String * obj, int pos, int ch);
void StringErase(String * obj, size_t beg, size_t end);
void StringClear(String * obj);
void StringFree(String * obj);

String * StringCreate()
{
	String * Str = (String *)malloc(sizeof (String));
	Str->c_str = (char *)malloc(sizeof (char) * 5);
	memset(Str->c_str, 0, sizeof (char) * 5);
	Str->length = 0;
	Str->capacity = 5;
	return Str;
}

void StringReallocate(String * obj, int newSize)
{
	char * str = (char *)realloc(obj->c_str, sizeof (char) * newSize);
	if (!str)
	{
		fprintf(stderr, "内存分配失败!\n");
		exit(1); 
	}
	else
		obj->c_str = str;
}

void StringAssign(String * obj, const char * str)
{
	int len = strlen(str);
	if (len >= obj->capacity)
	{
		StringReallocate(obj, len + 1);
		obj->capacity = len + 1;
	}	
	obj->length = len;
	strcpy(obj->c_str, str);
}

void StringAppend(String * obj, const char * str)
{
	int len = strlen(str);
	if (len + obj->length >= obj->capacity)
	{
		StringReallocate(obj, len + obj->length + 1);
		obj->capacity = len + obj->length + 1;
	}
	obj->length = len + obj->length;
	strcat(obj->c_str, str);
}


bool StringEqual(String * obj, const char * str)
{
	return !strcmp(obj->c_str, str);
}

void StringPushBack(String * obj, int ch)
{
	if (obj->length + 1 == obj->capacity)
	{
		StringReallocate(obj, obj->capacity * 2);
		memset(obj->c_str + obj->capacity, 0, sizeof (char) * obj->capacity);
		obj->capacity *= 2;
	}
	obj->c_str[obj->length++] = ch;		
}

void StringPopBack(String * obj)
{
	assert(obj->length);
	obj->c_str[--obj->length] = '\0';
}

void StringInsert(String * obj, int pos, int ch)
{
	
	if (obj->length + 1 == obj->capacity)
	{
		StringReallocate(obj, obj->capacity * 2);
		memset(obj->c_str + obj->capacity, 0, sizeof (char) * obj->capacity);
		obj->capacity *= 2;
	}
	int i;
	for (i = obj->length ;i > pos;i--)
		obj->c_str[i] = obj->c_str[i - 1];
	obj->c_str[i] = ch;
	obj->c_str[++obj->length] = '\0';
}

void StringErase(String * obj, size_t beg, size_t end)
{
	if (beg == end)
		return;
	assert(beg >= 0 && beg < obj->length && end >= 0 && end <= obj->length);
	int i, j;
	for (i = beg, j = end;j < obj->length;i++, j++)
		obj->c_str[i] = obj->c_str[j];
	obj->c_str[i] = '\0';
	obj->length -= end - beg;
}


void StringClear(String * obj)
{
	StringReallocate(obj, 5);
	memset(obj->c_str, 0, sizeof (char) * 5);
	obj->capacity = 5;
	obj->length = 0;
}

void StringFree(String * obj)
{
	free(obj->c_str);
	free(obj);
}


#endif
