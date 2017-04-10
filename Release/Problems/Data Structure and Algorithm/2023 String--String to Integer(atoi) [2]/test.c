#include <stdio.h>
#include <time.h>
int myAtoi(char* str);
int main()
{
	char str[1000];
	scanf("%s", str);
	clock_t runtime = clock();
	printf("%d\n", atoi(str));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	return 0;
}
