#include"Graduate.h"

////////////////////////////
//ÎÏÈÑÀÍÈÅ ÊËÀÑÑÀ GRADUATE//
const std::string& Graduate::get_subject()const
{
	return subject;
}
void Graduate::set_subject(const std::string& subject)
{
	this->subject = subject;
}

Graduate::Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject)
	:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
{
	set_subject(subject);
	cout << "GConstructor:\t" << this << endl;
}
Graduate::~Graduate()
{
	cout << "GDetructor:\t" << this << endl;
}
void Graduate::print()const
{
	Student::print();
	cout << subject << endl;
}
//ÊÎÍÅÖ ÎÏÈÑÀÍÈß ÊËÀÑÑÀ GRADUATE//
//////////////////////////////////