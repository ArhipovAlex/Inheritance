#include"Teacher.h"


///////////////////////////
//�������� ������ TEACHER//
const std::string& Teacher::get_speciality()const
{
	return speciality;
}
int Teacher::get_experience()const
{
	return experience;
}
void Teacher::set_speciality(const std::string& speciality)
{
	this->speciality = speciality;
}
void Teacher::set_experience(int experience)
{
	this->experience = experience;
}
Teacher::Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
{
	set_speciality(speciality);
	set_experience(experience);
	cout << "TConstructor:\t" << this << endl;
}
void Teacher::print()const
{
	Human::print();
	cout << speciality << " " << experience << " years\n";
}
//����� �������� ������ TEACHER//
/////////////////////////////////