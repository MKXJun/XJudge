#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
void rotate(vector<vector<int> >& matrix);

int main()
{
	vector<vector<int> > image;
	int num, n;
	cin >> n;
	image.resize(n);
	for (int i = 0;i < n;++i)
	{
		image[i].resize(n);
		for (int j = 0;j < n;++j)
			cin >> image[i][j];
	}
	clock_t runtime = clock();
	rotate(image);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);	
	
	for (int i = 0;i < n;++i)
	{
		for (int j = 0;j < n;++j)
			cout << image[i][j] << ' ';
		cout << endl;
	}
	return 0;
}
