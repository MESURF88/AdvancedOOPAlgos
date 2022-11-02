#ifndef _BRAINCHILD_H
#define _BRAINCHILD_H

#include "Parent.hpp"
#include <string>

class BrainChild final: public Parent
{
public:
	BrainChild(std::string namepassed, int agepassed) : Parent(namepassed, agepassed) {
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
