// Definition of Datastructure class, hw2 of TIE-20100/TIE-20106

#include "datastructure.hpp"

// For debug
#include <iostream>
using std::cerr;
using std::endl;

#include <algorithm>
using std::sort;
using std::find;

template <typename Type>
Type random_in_range(Type start, Type end)
{
        auto range = end - start;
        ++range;

        auto num = rand() % range;
        return static_cast<Type>(start + num);
}

Datastructure::Datastructure()
{
}

Datastructure::~Datastructure()
{
}

void Datastructure::add_person(string name, PersonID id, string title, Salary salary)
{
        Person new_person;
        new_person.id = id;
        new_person.name = name;
        new_person.title = title;
        new_person.salary = salary;

        id_dict.insert(pair<PersonID, Person>(id, new_person));

        // Push new person to the name dictionary
        if (name_dict.find(name) != name_dict.end())
        {
                name_dict[name].insert(id);
        }
        else
        {
                // This name has never been used before
                set<PersonID> new_set;
                new_set.insert(id);
                name_dict.insert(pair<string, set<PersonID>>(name, new_set));
        }

        salary_dict.insert(pair<Salary, PersonID>(salary, id));
}

void Datastructure::remove_person(PersonID id)
{
        PersonID boss_of_the_deleted = id_dict[id].bossid;

        if (boss_of_the_deleted != NO_ID)
        {
                vector<PersonID> &boss_underlings = id_dict[boss_of_the_deleted].underlings;

                // Remove that person from his/her boss's underlings list
                auto id_to_delete_it = find(boss_underlings.begin(), boss_underlings.end(), id);
                boss_underlings.erase(id_to_delete_it);

                if (id_dict[id].underlings.size() != 0)
                {
                        // Send all the underlings of the deleted to his/her boss
                        boss_underlings.insert(boss_underlings.end(),
                                               id_dict[id].underlings.begin(),
                                               id_dict[id].underlings.end());

                        // Assign new boss
                        for (auto underling : id_dict[id].underlings)
                        {
                                id_dict[underling].bossid = boss_of_the_deleted;
                        }
                }
        }
        else
        {
                // Remove the boss from the deleted's underlings
                if (id_dict[id].underlings.size() != 0)
                {
                        for (auto underling : id_dict[id].underlings)
                        {
                                id_dict[underling].bossid = NO_ID;
                        }
                }
        }

        // Remove the person from the name dictionary as well
        // We don't need to check if it can be found or not
        // I hope we don't call this function to delete unidentified person :(
        string name_of_the_deleted = id_dict[id].name;
        name_dict[name_of_the_deleted].erase(id);

        auto delete_from_salary_dict = salary_dict.equal_range(id_dict[id].salary);

        for (auto iter = delete_from_salary_dict.first;
             iter != delete_from_salary_dict.second; iter++)
        {
                if (iter->second == id)
                {
                        salary_dict.erase(iter);
                        break;
                }
        }

        if (id_dict[id].leader == true)
        {
                for (auto underling : id_dict[id].underlings)
                {
                        id_dict[underling].leader = true;
                }
        }

        id_dict.erase(id);
}

string Datastructure::get_name(PersonID id)
{
        return id_dict[id].name;
}

string Datastructure::get_title(PersonID id)
{
        return id_dict[id].title;
}

Salary Datastructure::get_salary(PersonID id)
{
        return id_dict[id].salary;
}

vector<PersonID> Datastructure::find_persons(string name)
{
        vector<PersonID> output;

        // Since the sorted name and id are in set
        // We need to convert it into vector
        for (auto current_id : name_dict[name])
        {
                output.push_back(current_id);
        }
        return output;
}

vector<PersonID> Datastructure::personnel_with_title(string title)
{
        vector<PersonID> output;

        for (auto current_pair : id_dict)
        {
                if (current_pair.second.title == title)
                {
                        output.push_back(current_pair.first);
                }
        }

        sort(output.begin(), output.end());
        return output;
}

void Datastructure::change_name(PersonID id, string new_name)
{
        string old_name = id_dict[id].name;
        id_dict[id].name = new_name;

        // Put the id to a new name key
        if (name_dict.find(new_name) == name_dict.end())
        {
                set<PersonID> new_set;
                new_set.insert(id);
                name_dict.insert(pair<string, set<PersonID>>(new_name, new_set));
        }
        else
        {
                name_dict[new_name].insert(id);
        }

        // Delete the id from the old name key
        auto name_iter = name_dict.find(old_name);
        if (name_iter != name_dict.end())
        {
                auto id_iter = name_iter->second.find(id);
                name_iter->second.erase(id_iter);
                if (name_iter->second.size() == 0)
                {
                        name_dict.erase(name_iter);
                }
        }
        else
        {
                // LOL Why we can't find the name though?
        }
}

void Datastructure::change_salary(PersonID id, Salary new_salary)
{
        Salary old_salary = id_dict[id].salary;

        auto equal_salary_people = salary_dict.equal_range(old_salary);
        for (auto iter = equal_salary_people.first;
             iter != equal_salary_people.second; iter++)
        {
                if (iter->second == id)
                {
                        salary_dict.erase(iter);
                        break;
                }
        }

        salary_dict.insert(pair<Salary, PersonID>(new_salary, id));
        id_dict[id].salary = new_salary;
}

void Datastructure::add_boss(PersonID id, PersonID bossid)
{
        if (id_dict[bossid].leader == false && id_dict[bossid].bossid == NO_ID)
        {
                id_dict[bossid].leader = true;
        }
        if (id_dict[id].leader == true)
        {
                id_dict[id].leader = false;
        }
        id_dict[id].bossid = bossid;
        id_dict[bossid].underlings.push_back(id);
}

unsigned int Datastructure::size()
{
        return id_dict.size();
}

void Datastructure::clear()
{
        id_dict.clear();
        name_dict.clear();
        salary_dict.clear();
}

vector<PersonID> Datastructure::underlings(PersonID id)
{
        sort(id_dict[id].underlings.begin(), id_dict[id].underlings.end());
        return(id_dict[id].underlings);
}

vector<PersonID> Datastructure::all_underlings(vector<PersonID> &ids)
{
        vector<PersonID> output;
        for (auto id : ids)
        {
                output.insert(output.end(), id_dict[id].underlings.begin(),
                              id_dict[id].underlings.end());
        }
        return output;
}

vector<PersonID> Datastructure::personnel_alphabetically()
{
        vector<PersonID> output;

        // Two for loops but it is actually O(n)
        // Since it just takes all the ids
        for (auto pair_id : name_dict)
        {
                for (auto ids : pair_id.second)
                {
                        output.push_back(ids);
                }
        }
        return output;
}

vector<PersonID> Datastructure::personnel_salary_order()
{
        vector<PersonID> output;

        for (auto salary_pair : salary_dict)
        {
                output.push_back(salary_pair.second);
        }

        return output;
}

PersonID Datastructure::find_ceo()
{
        vector<PersonID> leaders;
        for (auto current_pair : id_dict)
        {
                // If freelancer (i.e no boss and no underlings) is spotted
                if (current_pair.second.bossid == NO_ID && current_pair.second.underlings.size() == 0)
                {
                        return NO_ID;
                }
                if (current_pair.second.leader == true)
                {
                        leaders.push_back(current_pair.first);
                }
        }
        if (leaders.size() != 1)
        {
                return NO_ID;
        }
        else
        {
                return leaders.front();
        }
}

deque<PersonID> Datastructure::find_bosses(PersonID id)
{
        if (id_dict[id].bossid == NO_ID)
        {
                return deque<PersonID>();
        }
        else
        {
                PersonID nearest_boss = id_dict[id].bossid;
                auto output = find_bosses(nearest_boss);
                output.push_front(nearest_boss);
                return output;
        }
}

PersonID Datastructure::nearest_common_boss(PersonID id1, PersonID id2)
{
        deque<PersonID> id1_bosses = find_bosses(id1);
        deque<PersonID> id2_bosses = find_bosses(id2);

        if (id1_bosses.size() == 0 || id2_bosses.size() == 0)
        {
                return NO_ID;
        }

        if (id1_bosses.size() <= id2_bosses.size())
        {
                int rank_difference = id2_bosses.size() - id1_bosses.size();
                for (int i = 0; i < id1_bosses.size(); ++i)
                {
                        if (id1_bosses[i] == id2_bosses[i + rank_difference])
                        {
                                return id1_bosses[i];
                        }
                }
                return NO_ID;
        }
        else
        {
                int rank_difference = id1_bosses.size() - id2_bosses.size();
                for (int i = 0; i < id2_bosses.size(); ++i)
                {
                        if (id2_bosses[i] == id1_bosses[i + rank_difference])
                        {
                                return id2_bosses[i];
                        }
                }
                return NO_ID;
        }
}

pair<unsigned int, unsigned int> Datastructure::higher_lower_ranks(PersonID id)
{
        PersonID ceo = find_ceo();
        if (ceo == NO_ID)
        {
                return {0, 0};
        }
        if (id == ceo)
        {
                return {0, id_dict.size() - 1};
        }

        int rank = find_bosses(id).size();

        vector<PersonID> higher_rank_people = {ceo};
        vector<PersonID> previous_rank_people = {ceo};

        for (int i = 1; i < rank; ++i)
        {
                vector<PersonID> current_rank_people = all_underlings(previous_rank_people);
                higher_rank_people.reserve(higher_rank_people.size() + current_rank_people.size());
                higher_rank_people.insert(higher_rank_people.end(),
                                          current_rank_people.begin(), current_rank_people.end());
                previous_rank_people.clear();
                previous_rank_people.insert(previous_rank_people.end(),
                                            current_rank_people.begin(), current_rank_people.end());
        }

        vector<PersonID> equal_rank_people = all_underlings(previous_rank_people);

        int higher_rank_number = higher_rank_people.size();
        int lower_rank_number = id_dict.size() - higher_rank_number - equal_rank_people.size();
        return {higher_rank_number, lower_rank_number};
}

PersonID Datastructure::min_salary()
{
        return salary_dict.begin()->second;
}

PersonID Datastructure::max_salary()
{
        return (std::prev(salary_dict.end()))->second;
}

PersonID Datastructure::median_salary()
{
        int place = salary_dict.size() / 2;
        auto iter = salary_dict.begin();
        for (int i = 0; i < place; i++)
        {
                iter = std::next(iter);
        }
        return iter->second;
}

PersonID Datastructure::first_quartile_salary()
{
        int place = salary_dict.size() / 4;
        auto iter = salary_dict.begin();
        for (int i = 0; i < place; i++)
        {
                iter = std::next(iter);
        }
        return iter->second;
}

PersonID Datastructure::third_quartile_salary()
{
        int place = salary_dict.size() * 3 / 4;
        auto iter = salary_dict.begin();
        for (int i = 0; i < place; i++)
        {
                iter = std::next(iter);
        }
        return iter->second;
}
