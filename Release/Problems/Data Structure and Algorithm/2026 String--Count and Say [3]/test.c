#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
char* countAndSay(int n);

int main()
{
	int n;
	scanf("%d", &n);
	char * res;
	
	clock_t runtime = clock();
	res = countAndSay(n);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	printf("%s\n", res);
	free(res);
	return 0;
}
