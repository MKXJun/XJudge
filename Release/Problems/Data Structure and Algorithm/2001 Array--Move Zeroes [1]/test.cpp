#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
void moveZeroes(vector<int>& nums);

int main()
{
	vector<int> nums;
	int num, Size;
	cin >> Size;
	while (cin >> num)
		nums.push_back(num);
		
	clock_t runtime = clock();
	moveZeroes(nums);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (int i = 0;i < Size - 1;++i)
		cout << nums[i] << ' ';
	cout << nums[Size - 1] << endl;
	return 0;
}
