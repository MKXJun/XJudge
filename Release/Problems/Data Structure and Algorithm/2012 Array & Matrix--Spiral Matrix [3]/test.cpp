#include <iostream>
#include <vector>
#include <ctime>

using namespace std;
vector<int> spiralOrder(vector<vector<int> >& matrix);

int main()
{
	int m, n;
	cin >> m >> n;
	vector<vector<int> > matrix(m, vector<int>(n));
	for (int i = 0;i < m;i++)
		for (int j = 0;j < n;j++)
			cin >> matrix[i][j];	
	
	clock_t runtime = clock();
	vector<int> vec = spiralOrder(matrix);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (int i = 0;i < vec.size();++i)
		cout << vec[i] << ' ';
	return 0;
}
