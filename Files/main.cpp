#include<iostream>
#include<fstream>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;

std::string findIP(std::string const& str, int n = 15) {
	if (str.length() < n) {
		return str;
	}

	return str.substr(0, n);
}
std::string findMAC(std::string const& str, int n = 15) {
	if (str.length() < n) {
		return str;
	}

	return str.substr(0, n);
}

//#define WRITE_TO_FILE
//#define READ_FROM_FILE
#define RAW_READY

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	std::ofstream fout;							//1) Создали поток
	fout.open("File.txt", std::ios_base::app);	//2) Открыли поток (доп ", std::ios_base::app" позволяет открывать файл для дозаписи а не создавать каждый раз заново
	fout << "Hello Files" << endl;				//3) Пишем в поток
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
#ifdef RAW_READY
	std::ifstream fin;
	fin.open("201 RAW.txt");
	if (fin.is_open())
	{
		//TODO: read file
		std::ofstream fout;
		fout.open("201 ready.txt");
		const int SIZE = 18;
		char ip_buffer[SIZE] = {};
		char mac_buffer[SIZE] = {};
		while (!fin.eof())
		{
			fin >> ip_buffer >> mac_buffer;
			fout << mac_buffer << "\t" << ip_buffer << endl;
		}
		fin.close();
		system("notepad 201 ready.txt");
	}
	else
	{
		std::cerr << "Error: File not found" << endl;
	}
	fout.close();
#endif //RAW_READY
}