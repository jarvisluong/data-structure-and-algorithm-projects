// Definition of Datastructure class, hw1 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
using std::string;

#include <vector>
using std::vector;

struct Person
{
        string name;
        int salary;
};

class Datastructure
{
public:
Datastructure();
~Datastructure();

void add_person(string name, int salary);

unsigned int size();
void clear();

vector<Person*> personnel_alphabetically();
vector<Person*> personnel_salary_order();

Person* min_salary();
Person* max_salary();

Person* median_salary();
Person* first_quartile_salary();
Person* third_quartile_salary();

private:
//  Store the raw data with names and salaries of employees
vector<Person> _personnel;
vector<Person*> _personnel_alphabetically;
vector<Person*> _personnel_salary_order;

// Check if the vector has been sorted or not
bool _sorted_alphabetically = false;
bool _sorted_salary_order = false;
};

#endif // DATASTRUCTURE_HPP
