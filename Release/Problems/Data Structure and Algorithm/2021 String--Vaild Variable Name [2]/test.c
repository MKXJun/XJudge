#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

bool isValid(const char * str);
int main()
{
	char str[100];
	gets(str);
	clock_t runtime = clock();
	printf("%d\n", isValid(str));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	return 0;	
}
