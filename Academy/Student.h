#pragma once
#include"Human.h"

/////////////////////////////
//Œ¡⁄ﬂ¬À≈Õ»≈  À¿——¿ STUDENT//
#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance
class Student : public Human
{
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const;
	const std::string& get_group()const;
	double get_rating()const;
	double get_attendance()const;
	void set_speciality(const std::string& speciality);
	void set_group(const std::string& group);
	void set_rating(double rating);
	void set_attendance(double attendance);

	//		Constructors:
	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS);
	~Student();
	void print()const;
};
// ŒÕ≈÷ Œ¡⁄ﬂ¬À≈Õ»ﬂ  À¿——¿ STUDENT//
///////////////////////////////////