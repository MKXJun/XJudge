#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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

void CallFunc(String ** obj, char * func)
{
	if (!strcmp(func, "create"))
		*obj = StringCreate();
	else if (!strcmp(func, "pushback"))
	{
		char ch;
		while (isspace(ch = getchar()));
		StringPushBack(*obj, ch);
	}
	else if (!strcmp(func, "popback"))
		StringPopBack(*obj);
	else if (!strcmp(func, "assign"))
	{
		char str[1000];
		scanf("%s", str);
		StringAssign(*obj, str);
	}
	else if (!strcmp(func, "append"))
	{
		char str[1000];
		scanf("%s", str);
		StringAppend(*obj, str);
	}
	else if (!strcmp(func, "insert"))
	{
		int pos;
		char ch;
		scanf("%d", &pos);
		while (isspace(ch = getchar()));
		StringInsert(*obj, pos, ch);
	}
	else if (!strcmp(func, "erase"))
	{
		int beg, end;
		scanf("%d%d", &beg, &end);
		StringErase(*obj, beg, end);
	}
	else if (!strcmp(func, "equal"))
	{
		char str[1000];
		scanf("%s", str);
		printf("%d\n", StringEqual(*obj, str));
	}
	else if (!strcmp(func, "clear"))
	{
		StringClear(*obj);
	}
	else if (!strcmp(func, "free"))
	{
		StringFree(*obj);
	}
	else if (!strcmp(func, "print"))
	{
		printf("%s\n", (*obj)->c_str);
	}
}


int main()
{
	char str[100];
	String * obj;
	clock_t runtime = clock();
	while (~scanf("%s", str))
		CallFunc(&obj, str);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
}
