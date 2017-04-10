using namespace std;
void delay(unsigned ms);
void GetFolders();
void init();
void show_preface();
void set_storage_folder();
void load_user_info();
void show_problem(int pID);
void show_problem_list(int n);
void show_problem_folder();
void show_menu();



int main()
{
	init();		//初始化
	show_preface();		//显示前言
	set_storage_folder();	
	load_user_info();
	show_menu();

	return 0;
}