// Definition of Datastructure class, hw2 of TIE-20100/TIE-20106

#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <deque>
using std::deque;

#include <map>
using std::map;
using std::multimap;

#include <unordered_map>
using std::unordered_map;

#include <set>
using std::set;

#include <utility>
using std::pair;

#include <algorithm>
using std::sort;
using std::find;
using std::inplace_merge;

using PersonID = string;
PersonID const NO_ID = "";

using Salary = int;
Salary const NO_SALARY = -1;

struct Person {
        PersonID id;
        string name;
        Salary salary;
        string title;

        bool leader = false;
        PersonID bossid = NO_ID;
        vector<PersonID> underlings;
};

class Datastructure
{
public:
Datastructure();
~Datastructure();

void add_person(string name, PersonID id, string title, Salary salary);
void remove_person(PersonID id);

string get_name(PersonID id);
string get_title(PersonID id);
Salary get_salary(PersonID id);
vector<PersonID> find_persons(string name);
vector<PersonID> personnel_with_title(string title);

void change_name(PersonID id, string new_name);
void change_salary(PersonID id, Salary new_salary);

void add_boss(PersonID id, PersonID bossid);

unsigned int size();
void clear();

vector<PersonID> underlings(PersonID id);
vector<PersonID> all_underlings(vector<PersonID>& ids);
vector<PersonID> personnel_alphabetically();
vector<PersonID> personnel_salary_order();

// Find all the bosses (direct and indirect) of an ID
deque<PersonID> find_bosses(PersonID id);

PersonID find_ceo();
PersonID nearest_common_boss(PersonID id1, PersonID id2);
pair<unsigned int, unsigned int> higher_lower_ranks(PersonID id);

PersonID min_salary();
PersonID max_salary();

PersonID median_salary();
PersonID first_quartile_salary();
PersonID third_quartile_salary();

private:
// This map is used to find name quickly, and use the alphalist quick
// (map and set have been already sorted)
map<string, set<PersonID> > name_dict;

// We don't need to sort through salary since we got this
multimap<Salary, PersonID> salary_dict;

// Since we need to find person by ID alot then this unordered_map is ideal
unordered_map<PersonID, Person> id_dict;

// // Store the already sorted salary people
// vector<PersonID> salary_sort;

// // // Keep track of newly added people to merge them to the above vector later.
// // vector<PersonID> newly_added_people;
};

#endif // DATASTRUCTURE_HPP
