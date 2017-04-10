#include <stdio.h>
#include <time.h>
char* reverseString(char* s);

int main()
{
	char str[1000];
	gets(str);
	clock_t runtime = clock();
	printf("%s", reverseString(str));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	return 0;
}
