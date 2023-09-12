#include"Human.h"
#include"Student.h"
#include"Teacher.h"
#include"Graduate.h"
#include<fstream>;

void print(Human* group[], const int n);
void save(Human* group[], const int n, const char sz_filename[]);

std::ostream operator<<(std::ostream& os, const Human& obj)
{
	return os << obj.get_last_name() << " " << obj.get_first_name() << " " << obj.get_age() << " лет.";
}
//#define INHERITANCE_CHECK

void main()
{
#ifdef INHERITANCE_CHECK
	setlocale(LC_ALL, "");
	Human human("Montana", "Antonio", 25);
	human.print();

	Student student("Pincman", "Jessie", 22, "Chemistry", "WW_220", 90, 95);
	student.print();

	Teacher teacher("White", "Walter", 50, "Chemistry", 20);
	teacher.print();

	Graduate graduate("Schrader", "Hank", 40, "Criminalistic", "OBN", 80, 70, "How to catch Heisenberg");
	graduate.print();
#endif //INHERITANCE_CHECK 
	Human* group[] =
	{
		new Student("Pincman", "Jessie", 22, "Chemistry", "WW_220", 90, 95),
		new Teacher("White", "Walter", 50, "Chemistry", 20),
		new Graduate("Schrader", "Hank", 40, "Criminalistic", "OBN", 80, 70, "How to catch Heisenberg"),
		new Student("Vercetti","Tomas",30,"Theif","Vice",98,99),
		new Teacher("Diaz","Ricardo", 50,"Weapon distribution",25)
	};
	print(group, sizeof(group) / sizeof(group[0]));
	for (int i = 0; i < sizeof(group) / sizeof(group[0]); i++)
	{
		delete group[i];
	}
}

void print(Human* group[], const int n)
{
	cout << delimiter << endl;
	for (int i = 0; i < n; i++)
	{
		group[i]->print();
		cout << delimiter << endl;
	}
}
void save(Human* group[], const int n, const char sz_filename[])
{
	std::ofstream fout(sz_filename);

	fout.close();
}