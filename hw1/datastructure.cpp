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

// Mode determines how the data be sorted (by name or by salary)
// mode == 'n' : Sort by name, mode == 's': Sort by salary
void merge(vector<Person*>& A,int begin, int middle, int end, char mode) {
        vector<Person*> B;
        for (int i = begin; i<=end; i++) {
            B.push_back(A[i]);
        }
        int i = begin;
        int j = begin;
        int k = middle + 1;
        if (mode == 'n') {
                while (j <= middle && k <= end) {
                        if (B[j-begin]->name <= B[k-begin]->name) {
                                A[i] = B[j-begin];
                                ++j;
                        } else {
                                A[i] = B[k-begin];
                                ++k;
                        }
                        ++i;
                }
                k = j>middle ? 0 : (middle-end);
                for (j=i; j<=end; ++j) {
                        A[j] = B[j+k-begin];
                }
        }
        else if (mode == 's') {
                while ((j <= middle) && (k <= end)) {
                        if (B[j-begin]->salary <= B[k-begin]->salary) {
                                A[i] = B[j-begin];
                                ++j;
                        } else {
                                A[i] = B[k-begin];
                                ++k;
                        }
                        ++i;
                }
                k = j>middle ? 0 : (middle-end);
                for (j=i; j<=end; ++j) {
                        A[j] = B[j+k-begin];
                }
        }
}

void merge_sort(vector<Person*>& A, int begin, int end, char mode) {
        if (begin<end) {
                int middle = (begin + end)/2;
                merge_sort(A, begin, middle, mode);
                merge_sort(A, middle + 1, end, mode);
                merge(A, begin, middle, end, mode);
        }
}

Datastructure::Datastructure()
{

}

Datastructure::~Datastructure()
{

}

void Datastructure::add_person(std::string name, int salary)
{
        Person to_be_added;
        to_be_added.name = name;
        to_be_added.salary = salary;
        _personnel.push_back(to_be_added);
        _sorted_alphabetically = false;
        _sorted_salary_order = false;
}

unsigned int Datastructure::size()
{
        return _personnel.size();
}

void Datastructure::clear()
{
        _personnel.clear();
        _personnel_alphabetically.clear();
        _personnel_salary_order.clear();
        _sorted_salary_order = false;
        _sorted_alphabetically = false;
}

vector<Person *> Datastructure::personnel_alphabetically()
{
        if (_sorted_alphabetically) {
                return _personnel_alphabetically;
        }
        _personnel_alphabetically.clear();
        for (size_t i=0; i < _personnel.size(); ++i) {
                _personnel_alphabetically.push_back(&_personnel[i]);
        }
        merge_sort(_personnel_alphabetically, 0,
                   _personnel_alphabetically.size() - 1, 'n');
        _sorted_alphabetically = true;
        return _personnel_alphabetically;
}

vector<Person *> Datastructure::personnel_salary_order()
{
        if (_sorted_salary_order) {
                return _personnel_salary_order;
        }
        _personnel_salary_order.clear();
        for (size_t i=0; i < _personnel.size(); ++i) {
                _personnel_salary_order.push_back(&_personnel[i]);
        }
        merge_sort(_personnel_salary_order, 0,
                   _personnel_salary_order.size()-1, 's');
        _sorted_salary_order = true;
        return _personnel_salary_order;
}

Person* Datastructure::min_salary()
{
        if (!_sorted_salary_order) {
                personnel_salary_order();
        }
        return _personnel_salary_order.front();
}

Person* Datastructure::max_salary()
{
        if (!_sorted_salary_order) {
                personnel_salary_order();
        }
        return _personnel_salary_order.back();
}

Person* Datastructure::median_salary()
{
        if (!_sorted_salary_order) {
                personnel_salary_order();
        }
        int index = _personnel_salary_order.size()/2;
        return _personnel_salary_order[index];
}

Person* Datastructure::first_quartile_salary()
{
        if (!_sorted_salary_order) {
                personnel_salary_order();
        }
        int index = _personnel_salary_order.size()/4;
        return _personnel_salary_order[index];
}

Person* Datastructure::third_quartile_salary()
{
        if (!_sorted_salary_order) {
                personnel_salary_order();
        }
        int index = 3*_personnel_salary_order.size()/4;
        return _personnel_salary_order[index];
}
