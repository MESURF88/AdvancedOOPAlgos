#ifndef _PARENT_H
#define _PARENT_H

#include <string>

class Parent
{
public:
	Parent(std::string namepassed, int agepassed);

	virtual ~Parent() = default;



	void setAge(int agepassed) { doSetAge(agepassed); };
	int getAge(void) { return doGetAge(); };
	std::string getName(void) { return doGetName(); };
protected:

private:
	virtual void doSetAge(int agepassed) = 0;
	virtual int doGetAge(void) = 0;	
	virtual std::string doGetName(void) = 0;
	std::string name;
	int age;
};

#endif
