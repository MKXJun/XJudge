#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char* addBinary(char* a, char* b);
int main()
{
	char a[100], b[100];
	scanf("%s%s", a, b);
	clock_t runtime = clock();
	char * res = addBinary(a, b);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	printf("%s\n", res);
	free(res);
	return 0;
}
