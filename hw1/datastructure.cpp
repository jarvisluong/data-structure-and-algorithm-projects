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
template <typename T>
void merge(vector<T*> A, int begin, int middle, int end, char mode) {
        vector<T*> B;
        for (unsigned int index = 0; index < A.size(); ++index) {
                B.push_back(A[index])
        }
        int i = begin;
        int j = end;
        int k = middle + 1;
        if (mode == 'n') {
                while (j <= middle && k <= end) {
                        if (B[j]->name <= B[k]->name) {
                                A[i] = B[j];
                                j++;
                        } else {
                                A[i] = B[k];
                                k++;
                        }
                        i++
                }
                if (j > middle) {
                        k = 0;
                } else {
                        k = middle - end;
                }
                j = i;
                while (j< end) {
                        A[j] = B[j+k];
                }
        }
        if (mode == 's') {
                while (j <= middle && k <= end) {
                        if (B[j]->salary <= B[k]->salary) {
                                A[i] = B[j];
                                j++;
                        } else {
                                A[i] = B[k];
                                k++;
                        }
                        i++
                }
                if (j > middle) {
                        k = 0;
                } else {
                        k = middle - end;
                }
                j = i;
                while (j< end) {
                        A[j] = B[j+k];
                }
        }
}

template <typename T>
void merge_sort(vector<T*> A, int begin, int end, char mode) {
        if (A.size() > 0) {
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
        Person to_be_added(name, salary);
        _personnel.push_back(to_be_added);
}

unsigned int Datastructure::size()
{
        return _personnel.size()
}

void Datastructure::clear()
{
        _personnel.clear();
        _personnel_alphabetically.clear();
        _personnel_salary_order.clear();
}

vector<Person *> Datastructure::personnel_alphabetically()
{
        for (int i=0; i < _personnel.size(); i++) {
                _personnel_alphabetically.push_back(_personnel[i]);
        }
        merge_sort(_personnel_alphabetically, 0, _personnel_alphabetically.size()-1,
                   'n');
        return _personnel_alphabetically;
}

vector<Person *> Datastructure::personnel_salary_order()
{
        for (int i=0; i < _personnel.size(); i++) {
                _personnel_salary_order.push_back(_personnel[i]);
        }
        merge_sort(_personnel_salary_order, 0,
                   _personnel_salary_order.size()-1, 'n');
        return _personnel_salary_order;
}

Person* Datastructure::min_salary()
{
        if (_personnel_salary_order.size() != _personnel.size()) {
                personnel_salary_order();
        }
        return _personnel_salary_order[0];
}

Person* Datastructure::max_salary()
{
        if (_personnel_salary_order.size() != _personnel.size()) {
                personnel_salary_order();
        }
        return _personnel_salary_order[_personnel_salary_order.size()-1];
}

Person* Datastructure::median_salary()
{
        if (_personnel_salary_order.size() != _personnel.size()) {
                personnel_salary_order();
        }
        int index = _personnel_salary_order.size()/2;
        return _personnel_salary_order[index];
}

Person* Datastructure::first_quartile_salary()
{
        if (_personnel_salary_order.size() != _personnel.size()) {
                personnel_salary_order();
        }
        int index = _personnel_salary_order.size()/4;
        return _personnel_salary_order[index];
}

Person* Datastructure::third_quartile_salary()
{
        if (_personnel_salary_order.size() != _personnel.size()) {
                personnel_salary_order();
        }
        int index = 3*_personnel_salary_order.size()/4;
        return _personnel_salary_order[index];
}
