#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
char* longestCommonPrefix(char** strs, int strsSize);

int main()
{
	int n, i;
	scanf("%d", &n);
	while (getchar() != '\n');
	char ** strs = (char **)malloc(sizeof (char *) * n);
	for (i = 0;i < n;++i)
	{
		strs[i] = (char *)malloc(100);
		gets(strs[i]);
	}
	clock_t runtime = clock();
	printf("%s\n",longestCommonPrefix(strs, n));
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (i = 0;i < n;++i)
		free(strs[i]);
	free(strs);
	return 0;
}
