#pragma once
#include"Human.h"
/////////////////////////////
//Œ¡⁄ﬂ¬À≈Õ»≈  À¿——¿ TEACHER//
#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience
class Teacher :public Human
{
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const;
	int get_experience()const;
	void set_speciality(const std::string& speciality);
	void set_experience(int experience);
	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS);
	~Teacher();
	void print()const;
};
// ŒÕ≈÷ Œ¡⁄ﬂ¬À≈Õ»ﬂ  À¿——¿ TEACHER//
///////////////////////////////////