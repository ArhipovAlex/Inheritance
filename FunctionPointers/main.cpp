#include<iostream>
using namespace std;

const char* Hello()
{
	return "Hello";
}
int Sum(int a, int b)
{
	return a + b;
}

void main()
{
	setlocale(LC_ALL, "");
	cout<<Hello<<endl;//Адрес функции
	const char*(*pHello)() = Hello;
	cout<<pHello<<endl;//Адрес функции в указателе
	cout<<pHello()<<endl;//Вызов функции через указатель
	
	cout << Sum(2, 3) << endl;
	cout << Sum << endl;
	int (*pSum)(int, int) = Sum;
	cout << pSum << endl;
	cout << pSum(3, 4) << endl;
}