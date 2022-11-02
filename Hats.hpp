#ifndef _HATS_H
#define _HATS_H
#include <iostream>
#include <string>

class Strategy {
public:
    virtual ~Strategy() {}
    virtual void algorithmInterface() = 0;
};

class ConcreteStrategyA : public Strategy {
    ~ConcreteStrategyA() {}

    void algorithmInterface() {
        std::cout << "Concrete Strategy A" << std::endl;
    }
};

class ConcreteStrategyB : public Strategy {
    ~ConcreteStrategyB() {}

    void algorithmInterface() {
        std::cout << "Concrete Strategy B" << std::endl;
    }
};

class ConcreteStrategyC : public Strategy {
    ~ConcreteStrategyC() {}

    void algorithmInterface() {
        std::cout << "Concrete Strategy C" << std::endl;
    }
};

class Hat {
public:
    Hat(Strategy* s) : strategy(s) {}
    ~Hat() {
        delete strategy;
    }

    void contextInterface() {
        strategy->algorithmInterface();
    }
private:
    Strategy* strategy;
};

class Person {
	public:
		Person(std::string firstName, std::string lastName, int yearOfBirth)
		{
			this->firstName = firstName;
			this->lastName = lastName;
			this->yearOfBirth = yearOfBirth;
		};
		std::string printFirst() const
		{

			return this->firstName;
		}
		//friend std::ostream& operator<<(std::ostream& os, const Person& person);
	private:
		friend class PersonCompare;
		std::string firstName;
		std::string lastName;
		int yearOfBirth;
};

class PersonCompare {
	public:
		enum Criterion { NAME, BIRTHYEAR};
	private:
		Criterion criterion;
	public:
		PersonCompare(Criterion criterion) : criterion(criterion) {}
		bool operator()(const Person& p1, const Person& p2) const {
		switch (criterion) {
			case NAME: 
			    return p1.firstName < p2.firstName;
				break;
			case BIRTHYEAR: 
				return p1.yearOfBirth < p2.yearOfBirth;
				break;
		}
	}
};

#endif
