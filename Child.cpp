#include "Child.hpp"

void Child::doSetAge(int age_passed)
{
	age = age_passed;
}

int Child::doGetAge()
{
	return age;
}

std::string Child::doGetName()
{
	return name;
}
