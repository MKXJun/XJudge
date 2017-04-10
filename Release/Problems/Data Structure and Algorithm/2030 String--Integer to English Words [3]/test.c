#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char* numberToWords(int num);
int main()
{
	int num;
	scanf("%d", &num);
	
	clock_t runtime = clock();
	char * res = numberToWords(num);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	printf("%s\n", res);
	free(res);
	return 0;
}
