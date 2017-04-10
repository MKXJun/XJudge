#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
int romanToInt(char* s);

int main()
{
	char str[100];
	clock_t runtime = clock();
	while (~scanf("%s", str))
		printf("%d ", romanToInt(str));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	return 0;
}
