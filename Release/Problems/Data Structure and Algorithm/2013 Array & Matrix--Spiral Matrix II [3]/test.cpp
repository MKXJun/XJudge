#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
vector<vector<int> > generateMatrix(int n);
int main()
{
	int n;
	scanf("%d", &n);
	
	clock_t runtime = clock();
	vector<vector<int> > matrix = generateMatrix(n);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < n;++j)
			cout << matrix[i][j] << ' ';
		cout << endl;
	}
	return 0;
}
