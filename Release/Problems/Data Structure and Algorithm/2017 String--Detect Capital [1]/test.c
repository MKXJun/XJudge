#include <stdio.h>
#include <time.h>
#include <stdbool.h>
bool detectCapitalUse(char* word);

int main()
{
	char str[100000];
	gets(str);
	
	clock_t runtime = clock();
	printf("%d",detectCapitalUse(str));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	return 0;
}
