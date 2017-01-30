// Definition of Datastructure class, hw3 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
using std::cerr;
using std::endl;

// Helper function to return a random (enough) number in range start-end
// I.e. random_in_range(1,4) produces a random number between 1, 2, 3, or 4.
template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = rand() % range;
    return static_cast<Type>(start+num);
}


Datastructure::Datastructure()
{

}

Datastructure::~Datastructure()
{

}

void Datastructure::add_person(std::string name, int salary)
{
}

unsigned int Datastructure::size()
{
}

void Datastructure::clear()
{
}

vector<Person *> Datastructure::personnel_alphabetically()
{
}

vector<Person *> Datastructure::personnel_salary_order()
{
}

Person* Datastructure::min_salary()
{
}

Person* Datastructure::max_salary()
{
}

Person* Datastructure::median_salary()
{
}

Person* Datastructure::first_quartile_salary()
{
}

Person* Datastructure::third_quartile_salary()
{
}
