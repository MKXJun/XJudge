#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
bool canConstruct(char* ransomNote, char* magazine);

int main()
{
	char a[1000], b[1000];
	scanf("%s%s", a, b);
	clock_t runtime = clock();
	printf("%d\n", canConstruct(a, b));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	return 0;
}
