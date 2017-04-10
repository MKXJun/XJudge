#include <stdio.h>
#include <string.h>
#include <time.h>
int countSegments(char * s);

int main()
{
	char str[10000], ch;
	memset(str, 0, sizeof str);
	int i = 0;
	while ((ch = getchar()) != EOF)
		str[i++] = ch;
		
	clock_t runtime = clock();
	printf("%d\n", countSegments(str));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	return 0;
}
