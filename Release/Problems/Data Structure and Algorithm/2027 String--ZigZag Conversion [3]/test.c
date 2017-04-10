#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char* convert(char* s, int numRows);

int main()
{
	int n, i = 1;
	char source[100000];
	gets(source);
	scanf("%d", &n);
	clock_t runtime = clock();
	char * res = convert(source, n);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	printf("%s\n", res);
	free(res);
	return 0;
}
