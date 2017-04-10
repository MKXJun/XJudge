#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
int removeDuplicates(vector<int>& nums);
int main()
{
	int num;
	vector<int> nums;
	while (cin >> num)
		nums.push_back(num);
		
	clock_t runtime = clock();
	int res = removeDuplicates(nums);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);	
	
	for (int i = 0;i < res;++i)
		cout << nums[i] << ' ';
	return 0;
}
