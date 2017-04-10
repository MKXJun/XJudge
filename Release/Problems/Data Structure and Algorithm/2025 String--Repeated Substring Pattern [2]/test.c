#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
bool repeatedSubstringPattern(char* str);
int main()
{
	char * str;
	int n;
	scanf("%d", &n);
	str = (char *)malloc(n + 1);
	scanf("%s", str);
	clock_t runtime = clock();
	printf("%d\n", repeatedSubstringPattern(str));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	free(str);
	return 0;
}
