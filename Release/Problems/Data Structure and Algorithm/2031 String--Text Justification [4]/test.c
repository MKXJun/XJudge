#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
char** fullJustify(char** words, int wordsSize, int maxWidth, int* returnSize);

int main()
{
	char tmp[1000] = "";
	char ** words = (char **)malloc(sizeof (char *) * 100000);
	int n = 0, maxWidth, returnSize, i;
	scanf("%d", &maxWidth);
	while (~scanf("%s", tmp))
	{
		words[n] = (char *)malloc(sizeof (char) * (strlen(tmp) + 1));
		strcpy(words[n], tmp);
		n++;
	}
	clock_t runtime = clock();
	char ** res = fullJustify(words, n, maxWidth, &returnSize);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	for (i = 0;i < returnSize;++i)
	{
		printf("%s\n", res[i]);
		free(res[i]);
	}
	free(res);
	for (i = 0;i < n;++i)
		free(words[i]);
	free(words[i]);
	return 0;	
}
