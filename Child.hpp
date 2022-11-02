#ifndef _CHILD_H
#define _CHILD_H

#include "Parent.hpp"
#include <string>

class Child final: public Parent
{
public:
	Child(std::string namepassed, int agepassed) : Parent(namepassed, agepassed) {
		name = namepassed;
		age = agepassed;
	};


protected:

private:
	virtual void doSetAge(int agepassed) override;	
	virtual int doGetAge(void) override;
	virtual std::string doGetName(void) override;
	std::string name;
	int age;
};

#endif
