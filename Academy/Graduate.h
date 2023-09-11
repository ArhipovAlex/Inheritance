#pragma once
#include"Human.h"
#include"Student.h"
//////////////////////////////
//ÎÁÚßÂËÅÍÈÅ ÊËÀÑÑÀ GRADUATE//
class Graduate :public Student
{
	std::string subject;
public:
	const std::string& get_subject()const;
	void set_subject(const std::string& subject);

	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject);
	~Graduate();
	void print()const;
};
//ÊÎÍÅÖ ÎÁÚßÂËÅÍÈß ÊËÀÑÑÀ GRADUATE//
////////////////////////////////////