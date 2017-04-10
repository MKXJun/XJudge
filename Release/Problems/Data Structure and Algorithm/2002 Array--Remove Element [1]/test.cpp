#include <iostream>
#include <vector>
#include <ctime>
using namespace std;
int removeElement(vector<int>& nums, int val);
int main()
{
	vector<int> nums;
	int num, Size, val;
	cin >> Size;
	for (int i = 0;i < Size;++i)
	{
		cin >> num;
		nums.push_back(num);
	}
		
	cin >> val;
	
	
	clock_t runtime = clock();
	int res = removeElement(nums, val);
	runtime = clock() - runtime;
	FILE * ftime = fopen("runtime.txt", "w");
	fprintf(ftime, "%d", runtime > 1000 ? -1 : runtime);
	fclose(ftime);
	
	for (int i = 0;i < res;++i)
		cout << nums[i] << ' ';
	return 0;
}
