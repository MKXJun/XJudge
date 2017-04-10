#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char* intToRoman(int num);
int main()
{
	char * str;
	int n;
	clock_t runtime = clock();
	while (~scanf("%d", &n))
	{
		str = intToRoman(n);
		printf("%s ", str);
		free(str);
	}
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	return 0;
}
