#include <iostream>
#include <string>
#include <cstdlib>
#include "Functions.h"
#include "Functions.cpp"
using namespace std;

enum choice { 
	ADD_TASK = 1,
	SHOW_ALL_TASKS,
	FIND_ONE_TASK,
	REMOVE_ONE_TASK,
	REMOVE_ALL_TASKS,
	EXIT
};


int main()
{
	while (true) {
		showmenu();
		cout << "What are you up to?";
		int user_choice = 0;
		cin >> user_choice;
		if (user_choice == ADD_TASK)
		{
			system("cls");
			string new_task;
			getline(cin, new_task);
			cout << "Task to add: ";
			getline(cin, new_task);
			add_task(new_task);

			system("pause");
		}
		else if (user_choice == SHOW_ALL_TASKS)
		{
			system("cls");
			show_all_tasks();
			system("pause");
		}
		else if (user_choice == FIND_ONE_TASK)
		{
			system("cls");
			string task_to_find;
			getline(cin, task_to_find);
			cout << "Task to find: enter key ";
			getline(cin, task_to_find);

			int n_found = 0;
			string* found_tasks = find_one_task(task_to_find, n_found); //указатель на указатель на 1 элемент массива

			if (found_tasks !=0)
			{
				cout << "Found tasks by ur key are: " << endl;
				for (int i = 0; i < n_found; i++)
				
					cout << found_tasks[i] << endl;
					delete[] found_tasks;
			}
			else
			{
				cout << "No tasks witch mentioned key" << endl;
			}
			system("pause");
		}
		else if (user_choice == REMOVE_ONE_TASK)
		{
			system("cls");

			int count=0;
			string* all_tasks_array = all_tasks(count); //поиск вскх заметок
			cout << "Found tasks: " << endl;
			for (int i = 0; i < count; i++) //вывод найденных в консоль
			{
				cout << "[" << i + 1 << "]" << all_tasks_array[i] << endl;
			}
			cout << "Number of note to remove: ";
			int choice = 0;
			cin >> choice;
			remove_one_task(all_tasks_array, count, choice);
			cout << "Mentioned task removed" << endl;

			delete[] all_tasks_array;
			system("pause");
		}
		else if (user_choice == REMOVE_ALL_TASKS)
		{
			system("cls");
			remove_all_tasks();
			cout << "All tasks removed" << endl; 

			system("pause");
		}
		else if (user_choice == EXIT)
		{
			system("cls");
			cout << "System exit" << endl;
		}
		else cout << "Error";
		break;
	}
}

