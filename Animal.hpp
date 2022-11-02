#ifndef _ANIMAL_H
#define _ANIMAL_H

#include <string>

class Animal
{
public:
	Animal(std::string namepassed, int agepassed);

	virtual ~Animal() = default;

	bool operator < (Animal const& rhs) const
	{
		return this->age < rhs.age;
	};
	virtual void setName(std::string namepassed) { name = namepassed;  };
	std::string getName() const { return name; };
	int getAge() const { return age; };
protected:

private:
	std::string name;
	int age;
};

#endif
