#include <stdio.h>
#include <string.h>
#include <time.h>
typedef struct {
	int * data;
	size_t size;		
	size_t capacity;	
} Vector;

Vector * VectorCreate(size_t numsOfElement);
void VectorReallocate(Vector * vec, int newSize);
void VectorPushBack(Vector * vec, int val);
void VectorPopBack(Vector * vec);
void VectorClear(Vector * vec);
void VectorInsertValue(Vector * vec, size_t pos, int val);
void VectorErase(Vector * vec, size_t beg, size_t end);
void VectorFree(Vector * vec);

void CallFunc(Vector ** obj, char * func)
{
	if (!strcmp(func, "create"))
	{
		int val;
		scanf("%d", &val);
		*obj = VectorCreate(val);
	}
	else if (!strcmp(func, "pushback"))
	{
		int val;
		scanf("%d", &val);
		VectorPushBack(*obj, val);
	}
	else if (!strcmp(func, "popback"))
		VectorPopBack(*obj);
	else if (!strcmp(func, "clear"))
		VectorClear(*obj);
	else if (!strcmp(func, "insert"))
	{
		int pos, val;
		scanf("%d%d", &pos, &val);
		VectorInsertValue(*obj, pos, val);
	}
	else if (!strcmp(func, "erase"))
	{
		int beg, end;
		scanf("%d%d", &beg, &end);
		VectorErase(*obj, beg, end);
	}
	else if (!strcmp(func, "print"))
	{
		int i;
		for (i = 0;i < (*obj)->size;++i)
			printf("%d ", (*obj)->data[i]);
		puts("");
	}
	else if (!strcmp(func, "free"))
		VectorFree(*obj);
}

int main()
{
	char str[100];
	Vector * obj;
	clock_t runtime = clock();
	while (~scanf("%s", str))
		CallFunc(&obj, str);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	return 0;
}
