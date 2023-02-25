#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void showmenu()
{
	cout << "[1] Add task\n[2] Show all tasks\n[3] Find task\n[4] Remove task\n[5] Remove all\n[6] Exit." << endl;
}
void add_task(const string& new_task)
{
	cout << new_task << endl;
	ofstream file("notes.txt", ios::app);
	if (!file.is_open())
	{
		cout << "File is not opened";
		exit(EXIT_FAILURE);
	}
	file << new_task << endl;
	file.close();
	cout << "Task added" << endl;
}
void show_all_tasks()
{
	ifstream file("notes.txt");
	if (!file.is_open())
	{
		cout << "No tasks yet" << endl;
		return;
	}
	string one_task;
	cout << "All tasks u've got for now:\n";
	for (int i = 1; !file.eof(); i++)
	{
		getline(file, one_task);
		if (one_task.empty())
			continue;
		cout << '[' << i << ']' << one_task << endl;
	}
	file.close();
}
string* find_one_task(const string& task_to_find, int& n_count)
{
	ifstream file("notes.txt");
	if (!file.is_open())
	{
		cout << "No notes yet" << endl;
		return nullptr;
	}

	string one_task;
	string *found_tasks = nullptr; //указатели на 1 эл массива main
	string *found_tasks_temp=nullptr; //temporary
	int count = 0; //amount of dound tasks

	while (!file.eof())
	{
		getline(file, one_task);//or cin instead of file
		if (one_task.find(task_to_find) != -1) //проверка на наличие ключа в заметке
		{
			count++;
			found_tasks_temp = new string[count]; //выделение памяти для нужного кол-ва строк с задачами
			for (int i = 0; i < count - 1; i++) //все что найдено закидывается в этот массив
			{
				found_tasks_temp[i] = found_tasks[i];
				found_tasks_temp[count - 1] = one_task; // фиксируем, если есть нужная часть и записываем в конец временного массива

				delete[] found_tasks; //удаление старого содержимого
				found_tasks = found_tasks_temp; //указатель на новый массив

				found_tasks_temp = nullptr;
			}
		}
	}
	file.close();
	n_count = count;
	return found_tasks;
}
string* all_tasks(int& n_count)
{
	string* all_tasks = nullptr;
	string* all_tasks_ptr = nullptr;

	ifstream file("notes.txt");
	if (!file.is_open())
	{
		cout << "File not opened";
		exit(EXIT_FAILURE);
	}
	string one_task;
	int count = 0;
	//int count_of_found_tasks = 0;
	while(!file.eof())
	{
		getline(file, one_task);
		if (one_task.empty()) continue;
		
		count++;
		all_tasks_ptr = new string[count];

		for (int i = 0; i < count - 1; i++) //добавл нов задача
		{
			all_tasks_ptr[i] = all_tasks[i];
			all_tasks_ptr[count - 1] = one_task; //новая задача
			delete[] all_tasks;

			all_tasks = all_tasks_ptr;//all_tasks указывает на новый массив
			all_tasks_ptr = nullptr;
		}
	}
	file.close();
	n_count = count;
	return all_tasks;
}
void remove_one_task(string* all_tasks_array, int count, int choice)
{
	ofstream file("notes.txt");
	if (!file.is_open())
	{
		cout << "[-]Error! File not opened" << endl;
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < count; i++) //запись заметок без выбранной пользователем
	{
		if (i == choice-1) continue; //пропуск заметки с choice-1
		file << all_tasks_array[i] << endl;
	}

	file.close();
}
void remove_all_tasks()
{
	fstream file("notes.txt", ios::out | ios::trunc);
	if (file.is_open())
	{
		cout << "[-] File is not opened" << endl;
		exit(EXIT_FAILURE);
	}
	file.close();
}