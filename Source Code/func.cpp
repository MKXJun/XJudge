#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <cstring>
#include <conio.h>
#include <vector>
#include <fstream>
#include <Windows.h>
#include <algorithm>
#include <map>
#include <ctime>
#include <cstdio>
using namespace std;

//用户信息
struct USER {
	char userID[20];
	int submissions;
	int accepts;
	int corrent_problems;
	vector<int> pass_pIDs;
} user;
//习题ID、标题、单道习题文件夹名、是否AC
struct PROBLEM {
	int pID;
	string title;
	string full_title;
	bool accepted;
};
//习题文件夹及内部问题
struct PROBLEM_FOLDER {
	string folder_name;
	vector<PROBLEM> problems;
};

string cwd = __FILE__;		//当前文件路径
vector<string> folders;		//习题文件夹
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
COORD pos = { 0, 0 }, screen_size = { 80, 160 };
CONSOLE_SCREEN_BUFFER_INFO binfo;
DWORD written;
vector<PROBLEM_FOLDER> problem_folders;		//所有习题文件夹及内部问题
string storage_folder;			//储存路径
map<int, string> found_pID;		//找到的习题ID

void delay(unsigned ms)
{
	time_t current_time = clock();
	while (clock() - current_time <= ms)
		continue;
}


void GetFolders()
{
	//查询Problems文件夹下所有习题文件夹并读入
	system("dir /b /ad Problems\\ > Folders.txt");
	ifstream fin;
	fin.open("Folders.txt");
	string str;
	while (getline(fin, str))
		folders.push_back(str);
	fin.close();
	system("del Folders.txt");
	PROBLEM_FOLDER tmp;
	for (size_t i = 0; i < folders.size(); ++i)
	{
		//查询习题文件夹下所有子习题的文件夹
		tmp.folder_name = folders[i];
		problem_folders.push_back(tmp);
		str = "dir /b /ad \"Problems\\" + problem_folders[i].folder_name + "\\\" > temp.txt";
		system(str.c_str());
		fin.open("temp.txt");
		PROBLEM ptmp;
		while (getline(fin, str))
		{
			ptmp.full_title = str;
			problem_folders[i].problems.push_back(ptmp);
		}
		//再读一遍用于读进题目ID和题目名
		fin.clear();
		fin.seekg(0, ios::beg);

		int id, pos = 0;
		while (fin >> id && getline(fin, str))
		{
			problem_folders[i].problems[pos].pID = id;
			problem_folders[i].problems[pos].title = str;
			auto it = find(user.pass_pIDs.begin(), user.pass_pIDs.end(), id);
			problem_folders[i].problems[pos].accepted = (it != user.pass_pIDs.end());
			++pos;
		}
		fin.close();
		system("del temp.txt");
	}
	//将读到的所有问题收集用于快速查题
	for (size_t i = 0; i < problem_folders.size(); ++i)
		for (size_t j = 0; j < problem_folders[i].problems.size(); ++j)
			if (found_pID.find(problem_folders[i].problems[j].pID) == found_pID.end())
				found_pID[problem_folders[i].problems[j].pID] = problem_folders[i].folder_name + "\\" + problem_folders[i].problems[j].full_title;
}


void init()
{
	SetConsoleScreenBufferSize(hOut, screen_size);
	SMALL_RECT rc = { 0, 0, 79, 39 };
	SetConsoleWindowInfo(hOut, true, &rc);
	cwd.erase(cwd.begin() + cwd.find_last_of('\\') + 1, cwd.end());
	system(cwd.substr(0, 2).c_str());	//转移至目标盘
	system(("cd \"" + cwd + "\"").c_str());		//转移至该程序所在位置
	system("cls");
	GetFolders();
}

void show_preface()
{
	ifstream fin;
	string str, lstr;
	fin.open("preface.txt");	//读取序言
	if (!fin.is_open())
	{
		cerr << "缺少preface.txt文件！重新解压恢复文件以让程序正常运行。\n按回车键结束\n";
		while (_getch() != '\r');
		exit(EXIT_FAILURE);
	}
	while (getline(fin, str))
		lstr += str + '\n';
	printf("%s", lstr.c_str());
	fin.close();
	while (_getch() != '\r');	//按回车键继续
}

void set_storage_folder()
{
	system("cls");
	ifstream fin;
	FILE * fp = fopen("settings.txt", "r");
	if (!fp)
	{
		fclose(fp);
		printf("由于第一次使用，程序将收取代码的默认路径设置为：\n");
		printf("C:\\Users\\Administrator\\Desktop\\TEST\\\n");
		printf("将写好的代码存放到该路径下，按题目要求改源程序名，在程序内即可评测\n");
		printf("如果需要修改储存文件的位置，请修改setting.txt内的路径参数，然后再运行\n");
		printf("注意！不要随意修改setting.txt内的格式！\n");
		printf("按回车键继续\n");
		ofstream fout;
		fout.open("settings.txt", ios::out);
		fout << "Storage Folder:    C:\\Users\\Administrator\\Desktop\\TEST\\\n";
		fout.close();
		storage_folder = "C:\\Users\\Administrator\\Desktop\\TEST\\";
		string str = "md " + storage_folder + " 2> temp.txt";
		system(str.c_str());
		system("del temp.txt");
		while (_getch() != '\r');
		return;
	}
	fclose(fp);
	fin.open("settings.txt", ios::in);
	fin >> storage_folder >> storage_folder >> storage_folder;
	fin.close();
	string str = "md " + storage_folder + " 2> temp.txt";
	system(str.c_str());
	system("del temp.txt");
}

void load_user_info()
{
	system("cls");
	ifstream fin;
	FILE * fp = fopen("user.dat", "rb");
	if (!fp)
	{
		fclose(fp);
		int zero = 0;
		char userID[20];
		printf("输入用户名（建议英文、数字而非中文，不支持空格，4-12字符): \n");
		while (cin >> userID && (strlen(userID) > 12 || strlen(userID) < 4))
			printf("重新输入: ");
		while (getchar() != '\n');
		strcpy(user.userID, userID);
		ofstream fout;
		fout.open("user.dat", ios::out | ios::binary);
		fout.write(reinterpret_cast<char *>(userID), 20);
		fout.write(reinterpret_cast<char *>(&zero), 4);
		fout.write(reinterpret_cast<char *>(&zero), 4);
		fout.write(reinterpret_cast<char *>(&zero), 4);
		fout.close();
		user.submissions = user.accepts = 0;
		return;
	}
	fin.open("user.dat", ios::in | ios::binary);
	int num;
	fin.read(reinterpret_cast<char *>(user.userID), 20);
	fin.read(reinterpret_cast<char *>(&user.submissions), 4);
	fin.read(reinterpret_cast<char *>(&user.accepts), 4);
	fin.read(reinterpret_cast<char *>(&user.corrent_problems), 4);
	while (!fin.eof())
	{
		fin.read(reinterpret_cast<char *>(&num), 4);
		user.pass_pIDs.push_back(num);
	}
	user.pass_pIDs.erase(remove(user.pass_pIDs.begin(), user.pass_pIDs.end(), 0), user.pass_pIDs.end());
	user.pass_pIDs.erase(unique(user.pass_pIDs.begin(), user.pass_pIDs.end()), user.pass_pIDs.end());
	sort(user.pass_pIDs.begin(), user.pass_pIDs.end());
	fin.close();
	fstream fio;
	fio.open("user.dat", ios::in | ios::out | ios::binary);
	fio.seekg(32, ios::beg);
	for (size_t i = 0; i < user.pass_pIDs.size(); ++i)
		fio.write(reinterpret_cast<char *>(&user.pass_pIDs[i]), 4);
	fio.close();

	//取出已经完成题目的记录
	for (size_t i = 0; i < problem_folders.size(); ++i)
		for (size_t j = 0; j < problem_folders[i].problems.size(); ++j)
			if (find(user.pass_pIDs.begin(), user.pass_pIDs.end(), problem_folders[i].problems[j].pID) != user.pass_pIDs.end())
				problem_folders[i].problems[j].accepted = true;
}

void show_problem(int pID)
{
	string str = "Problems\\" + found_pID[pID] + "\\Description.txt";
	ifstream fin;
	fstream fio;
	char str_pID[20];
	sprintf(str_pID, "%d", pID);
	fin.open(str.c_str());
	if (!fin.is_open())
	{
		system("cls");
		printf("找不到题目描述文件！按回车返回上一层\n");
		while (_getch() != '\r');
		return;
	}
	vector<string> strs;
	while (getline(fin, str))
		strs.push_back(str);
	fin.close();
	int n;
	while (1)
	{
		system("cls");
		for (size_t i = 0; i < strs.size(); i++)
			printf("%s\n", strs[i].c_str());
		printf("\n编写好代码后将文件保存在:\n%s\n", storage_folder.c_str());
		printf("将文件名修改为%d.c或%d.cpp\n", pID, pID);
		printf("输入编号: (1)使用C语言提交(ANSI C)\n");
		printf("          (2)使用C语言提交(C99)\n");
		printf("          (3)使用C++提交(C++98)\n");
		printf("          (4)使用C++提交(C++11)\n");
		printf("          (0)返回上一层\n");
		if (!scanf("%d", &n) || n < 0 || n > 4)
		{
			while (getchar() != '\n');
			continue;
		}
		while (getchar() != '\n');
		if (!n)
			break;

		//增加提交次数
		fio.open("user.dat", ios::in | ios::out | ios::binary);
		user.submissions++;
		fio.seekp(20, ios::beg);
		fio.write(reinterpret_cast<char *>(&user.submissions), 4);
		fio.close();
		//检测是否有要联合编译的源文件
		bool single_compile = true;
		str = "dir /b /on \"Problems\\" + found_pID[pID] + "\\test.c\" > temp.txt 2> temp2.txt";
		system(str.c_str());
		fin.open("temp.txt");
		fin >> str;
		fin.close();
		if (str == "test.c")
			single_compile = false;

		system("del temp.txt");
		system("del temp2.txt");

		switch (n)
		{
		case 1:  str = single_compile ? "bin\\gcc.exe \"" + storage_folder + str_pID + ".c\" -o \"" + cwd + "Problems\\" + found_pID[pID] + "\\test.exe\" -O2 -m32"
			: "bin\\gcc.exe \"" + storage_folder + str_pID + ".c\" \"Problems\\" + found_pID[pID] + "\\test.c\" -o \"" + cwd + "Problems\\" + found_pID[pID] + "\\test.exe\" -O2 -m32";
			break;
		case 2:  str = single_compile ? "bin\\gcc.exe \"" + storage_folder + str_pID + ".c\" -o \"" + cwd + "Problems\\" + found_pID[pID] + "\\test.exe\" -O2 -std=c99 -m32"
			: "bin\\gcc.exe \"" + storage_folder + str_pID + ".c\" \"Problems\\" + found_pID[pID] + "\\test.c\" -o \"" + cwd + "Problems\\" + found_pID[pID] + "\\test.exe\" -O2 -std=c99 -m32";
			break;
		case 3:  str = single_compile ? "bin\\g++.exe \"" + storage_folder + str_pID + ".cpp\" -o \"" + cwd + "Problems\\" + found_pID[pID] + "\\test.exe\" -O2 -m32"
			: "bin\\g++.exe \"" + storage_folder + str_pID + ".cpp\" \"Problems\\" + found_pID[pID] + "\\test.cpp\" -o \"" + cwd + "Problems\\" + found_pID[pID] + "\\test.exe\" -O2 -m32";
			break;
		case 4:  str = single_compile ? "bin\\g++.exe \"" + storage_folder + str_pID + ".cpp\" -o \"" + cwd + "Problems\\" + found_pID[pID] + "\\test.exe\" -O2 -std=c++11 -m32"
			: "bin\\g++.exe \"" + storage_folder + str_pID + ".cpp\" \"Problems\\" + found_pID[pID] + "\\test.cpp\" -o \"" + cwd + "Problems\\" + found_pID[pID] + "\\test.exe\" -O2 -std=c++11 -m32";
			break;
		}
		system(str.c_str());
		str = "dir /b \"Problems\\" + found_pID[pID] + "\\test.exe\" > temp.txt";
		system(str.c_str());
		fin.open("temp.txt");
		fin >> str;
		fin.close();
		system("del temp.txt");
		if (str == "test.exe")
		{
			bool ac = true;
			vector<string> testcase_input, testcase_output;
			//寻找测试示例
			str = "dir /b /on \"Problems\\" + found_pID[pID] + "\\test*.in\" > temp.txt";
			system(str.c_str());
			fin.open("temp.txt");
			while (getline(fin, str))
				testcase_input.push_back(str);
			fin.close();
			system("del temp.txt");
			//缺乏测试示例的情况
			if (!testcase_input.size())
			{
				printf("缺乏测试示例，按回车键继续\n");
				str = "del \"Problems\\" + found_pID[pID] + "\\test.exe";
				system(str.c_str());
				while (_getch() != '\r');
				continue;
			}


			str = "dir /b /on \"Problems\\" + found_pID[pID] + "\\test*.out\" > temp.txt";
			system(str.c_str());
			fin.open("temp.txt");
			while (getline(fin, str))
				testcase_output.push_back(str);
			fin.close();
			system("del temp.txt");

			if (!testcase_output.size() || testcase_input.size() != testcase_output.size())
			{
				printf("缺乏测试示例，按回车键继续\n");
				str = "del \"Problems\\" + found_pID[pID] + "\\test.exe\"";
				system(str.c_str());
				while (_getch() != '\r');
				continue;
			}

			//开始运行并比对结果
			vector<string> out1, out2;

			for (size_t i = 0; i < testcase_input.size(); ++i)
			{
				out1.clear();
				out2.clear();
				bool compare_result = true;
				str = "\"\"" + cwd + "Problems\\" + found_pID[pID] + "\\test.exe\" < \"" + cwd + "Problems\\" + found_pID[pID] + "\\" + testcase_input[i] + "\" > test.txt\"";
				system(str.c_str());
				str = "Problems\\" + found_pID[pID] + "\\" + testcase_output[i];
				fin.open(str.c_str());
				while (getline(fin, str))
					out1.push_back(str);
				fin.close();
				printf("测试示例%d... ", i + 1);


				//打开保存结果的文件并提取出来
				fin.open("test.txt");
				while (getline(fin, str))
					out2.push_back(str);
				fin.close();

				//读取运行时间
				clock_t runtime;
				fin.open("runtime.txt");
				fin >> runtime;
				fin.close();

				if (runtime == -1)
				{
					ac = false;
					printf("超时\n");
				}
				else if (out1.size() != out2.size())
				{
					ac = false;
					printf("结果错误或输出格式错误 用时: %dms\n", runtime);
				}
				else
				{
					for (size_t j = 0; j < out1.size(); ++j)
						if (out1[j] != out2[j])
						{
							ac = compare_result = false;
							break;
						}
					if (!compare_result)
						printf("结果错误  用时: %dms\n", runtime);
					else
						printf("正确    用时: %dms\n", runtime);
				}
			}

			system("del test.txt");
			str = "del \"Problems\\" + found_pID[pID] + "\\test.exe\"";
			system(str.c_str());

			fio.open("user.dat", ios::in | ios::out | ios::binary);
			fio.seekp(24, ios::beg);
			if (ac)
			{
				printf("完成题目！\n");
				user.accepts++;
				fio.write(reinterpret_cast<char *>(&user.accepts), 4);
				//检测是否做重复题目，没有则进入
				if (find(user.pass_pIDs.begin(), user.pass_pIDs.end(), pID) == user.pass_pIDs.end())
				{
					user.corrent_problems++;
					user.pass_pIDs.push_back(pID);
					fio.write(reinterpret_cast<char *>(&user.corrent_problems), 4);
					fio.seekp(0, ios::end);
					fio.write(reinterpret_cast<char *>(&pID), 4);
					bool found_ac_pID = false;
					for (size_t j = 0; j < problem_folders.size() && !found_ac_pID; ++j)
					{
						for (size_t k = 0; k < problem_folders[j].problems.size(); ++k)
							if (problem_folders[j].problems[k].pID == pID)
							{
								found_ac_pID = true;
								problem_folders[j].problems[k].accepted = true;
								break;
							}
					}
				}
			}
			fio.close();
		}
		else
			printf("编译错误！检查程序。\n");

		printf("按回车键继续。\n");
		while (_getch() != '\r');
	}

}

void show_problem_list(int n)
{
	int page = (problem_folders[n - 1].problems.size() + 24) / 25, page_pos = 1, op;
	page = !page ? 1 : page;
	string str = "\"" + problem_folders[n - 1].folder_name + "\\\"";
	while (1)
	{
		system("cls");
		int lines = 0;
		printf("题目ID     题目名                                                     通过\n");
		for (size_t i = 0; 25 * (page_pos - 1) + i < problem_folders[n - 1].problems.size() && i < 25; ++i, lines++)
			printf("%-10d%-60s%s\n", problem_folders[n - 1].problems[25 * (page_pos - 1) + i].pID,
				problem_folders[n - 1].problems[25 * (page_pos - 1) + i].title.c_str(),
				problem_folders[n - 1].problems[25 * (page_pos - 1) + i].accepted ? "是" : "否");
		for (; lines < 25; lines++)
			puts("");
		printf("\n                     第%d页，共%d页\n", page_pos, page);
		printf("输入数字: (0) 后退    (1) 上一页    (2) 下一页    (题目ID) 进入题目\n");

		if (!scanf("%d", &op))
		{
			while (getchar() != '\n');
			continue;
		}

		while (getchar() != '\n');
		bool is_found = false;
		for (size_t i = (page_pos - 1) * 25; i < problem_folders[n - 1].problems.size() && i < page_pos * 25; i++)
			if (problem_folders[n - 1].problems[i].pID == op)
			{
				is_found = true;
				break;
			}
		if (is_found)
			show_problem(op);
		else if (op == 1)
		{
			page_pos--;
			page_pos = !page_pos ? 1 : page_pos;
		}
		else if (op == 2)
		{
			page_pos++;
			page_pos = page_pos > page ? page : page_pos;
		}
		else if (op == 0)
			return;
	}
}

void show_problem_folder()
{
	int choices = problem_folders.size();
	int n;
	while (1)
	{
		system("cls");
		for (int i = 0; i < choices; ++i)
			printf("%d   %s\n", i + 1, problem_folders[i].folder_name.c_str());
		printf("0    返回上一层\n");
		printf("输入序号选择\n");

		if (!scanf("%d", &n))
		{
			while (getchar() != '\n');
			continue;
		}

		while (getchar() != '\n');
		if (n == 0)
			return;
		else if (n > 0 && n <= choices)
			show_problem_list(n);
	}
}

void show_menu()
{
	char ch;
	while (1)
	{
		system("cls");
		printf("主菜单\n");
		printf("1   题目文件夹\n");
		printf("2   快速搜索题目\n");
		printf("3   用户信息\n");
		printf("输入序号选择\n");
		ch = getchar();
		while (getchar() != '\n');
		if (ch == '1')
			show_problem_folder();
		else if (ch == '2')
		{
			while (1)
			{
				system("cls");
				printf("快速搜索\n输入题号，0返回上一层: ");
				int id;
				if (!scanf("%d", &id))
				{
					while (getchar() != '\n');
					continue;
				}
				if (!id)
					break;
				else if (found_pID.find(id) != found_pID.end())
					show_problem(id);
			}

		}
		else if (ch == '3')
		{
			system("cls");
			printf("用户信息\n");
			printf("用户名: %s\n", user.userID);
			printf("提交次数: %d\n", user.submissions);
			printf("正确次数: %d\n", user.accepts);
			printf("正确题目数: %d\n", user.corrent_problems);
			printf("完成题目编号:  ");
			for (size_t i = 0; i < user.pass_pIDs.size(); ++i)
				printf("%d ", user.pass_pIDs[i]);
			printf("\n按回车键返回上层\n");
			while (_getch() != '\r');
		}

	}
}

