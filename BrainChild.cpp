#include "BrainChild.hpp"

void BrainChild::doSetAge(int age_passed)
{
	age = age_passed;
}

int BrainChild::doGetAge()
{
	return age;
}

std::string BrainChild::doGetName()
{
	return "Brain"+name;
}
