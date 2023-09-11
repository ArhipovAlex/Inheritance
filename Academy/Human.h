#pragma once
#include<iostream>
//using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n---------------------------------\n"
#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

///////////////////////////
//ÎÁÚßÂËÅÍÈÅ ÊËÀÑÑÀ HUMAN//
class Human
{
	std::string last_name;
	std::string first_name;
	int age;
public:
	const std::string& get_last_name();
	const std::string& get_first_name();
	int get_age();
	void set_last_name(const std::string& last_name);
	void set_first_name(const std::string& first_name);
	void set_age(int age);
	//		Constructors:
	Human(HUMAN_TAKE_PARAMETERS);
	~Human();
	virtual void print()const;
};
//ÊÎÍÅÖ ÎÁÚßÂËÅÍÈß ÊËÀÑÑÀ HUMAN//
/////////////////////////////////