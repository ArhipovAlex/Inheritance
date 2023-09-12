#include<iostream>
#include<fstream>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	std::ofstream fout;							//1) Создали поток
	fout.open("File.txt", std::ios_base::app);	//2) Открыли поток (доп ", std::ios_base::app" позволяет открывать файл для дозаписи а не создавать каждый раз заново
	fout << "Hello Files"<<endl;				//3) Пишем в поток
	fout << "Сам привет!\n";
	fout.close();								//4) Когда поток не нужен, закрываем его
	system("notepad File.txt");
#endif //WRITE_TO_FILE
#ifdef READ_FROM_FILE
	std::ifstream fin;
	fin.open("File.txt");
	if (fin.is_open())
	{
		//TODO: read file
		const int SIZE = 10240;
		char sz_buffer[SIZE] = {};
		while (!fin.eof())
		{
			//fin >> sz_buffer; //читает до пробела
			fin.getline(sz_buffer, SIZE); //.getline читает с пробелами построчно
			cout << sz_buffer << endl;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
#endif //READ_FROM_FILE

}