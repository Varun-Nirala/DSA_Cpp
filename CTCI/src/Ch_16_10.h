#pragma once
/*
	Living people :	Given a list of people with their birth and death years, implement a method to compute the year with the
					most number of people alive. You may assume that all people were born between 1900 and 2000(inclusive). If
					a person was alive during any portion of that year they should be included in that year's count.
					For example , Person(birth = 1908, death = 1909) is included in the counts for both 1908 and 1909.
*/

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Person
{
public:
	int birth;
	int death;

	Person(int b, int d)
		: birth(b)
		, death(d)
	{}
};

class Solution_16_10
{
	vector<int> getSortedYears(const vector<Person> &people, bool byBirth)
	{
		vector<int> vec;
		vec.resize(people.size());

		if (byBirth)
		{
			for (int i = 0; i < people.size(); ++i)
			{
				vec[i] = people[i].birth;
			}
		}
		else
		{
			for (int i = 0; i < people.size(); ++i)
			{
				vec[i] = people[i].death;
			}
		}

		sort(vec.begin(), vec.end());
		return vec;
	}
public:
	// Running time is O (P log P)
	int yearWithMostLivingPeople_1(const vector<Person> &people, int minYear, int maxYear)
	{
		(void)maxYear;
		vector<int> births = getSortedYears(people, true);
		vector<int> deaths = getSortedYears(people, false);

		int birthIndex = 0;
		int deathIndex = 0;
		int currentlyAlive = 0;
		int maxAlive = 0;
		int maxAliveYear = minYear;

		while (birthIndex < births.size())
		{
			if (births[birthIndex] <= deaths[deathIndex])
			{
				currentlyAlive++;
				if (currentlyAlive > maxAlive)
				{
					maxAlive = currentlyAlive;
					maxAliveYear = births[birthIndex];
				}
				birthIndex++;
			}
			else if (births[birthIndex] > deaths[deathIndex])
			{
				currentlyAlive--;
				deathIndex++;
			}
		}

		return maxAliveYear;
	}

	//More optimal solution O(R + P) , where is R is range of year
	int yearWithMostLivingPeople_2(const vector<Person> &people, int minYear, int maxYear)
	{
		vector<int> populationDelta = getPopulationDeltas(people, minYear, maxYear);
		return minYear + getMaxAliveYear(populationDelta);
	}

private:
	int getMaxAliveYear(const vector<int> &populationDelta)
	{
		int maxAliveYear = 0;
		int maxAlive = 0;
		int currentlyAlive = 0;

		for (int year = 0; year < populationDelta.size(); ++year)
		{
			currentlyAlive += populationDelta[year];
			if (currentlyAlive > maxAlive)
			{
				maxAlive = currentlyAlive;
				maxAliveYear = year;
			}
		}
		return maxAliveYear;
	}

	vector<int> getPopulationDeltas(const vector<Person> &people, int minYear, int maxYear)
	{
		vector<int> populationDelta;
		populationDelta.resize(maxYear - minYear + 2);		// One extra space

		for (auto &p : people)
		{
			int birth = p.birth - minYear;
			populationDelta[birth]++;

			int death = p.death - minYear;
			populationDelta[death + 1]--;
		}
		return populationDelta;
	}
};

void test_Ch_16_10()
{
	vector<Person> people = {
		{1912, 1915},
		{1920, 1990},
		{1910, 1998},
		{1901, 1972},
		{1910, 1998},
		{1923, 1982},
		{1913, 1998},
		{1990, 1998},
		{1983, 1999},
		{1975, 1994}
	};
	Solution_16_10 sol;

	int minYear = 1900;
	int maxYear = 2000;
	cout << sol.yearWithMostLivingPeople_1(people, minYear, maxYear) << endl;
	cout << sol.yearWithMostLivingPeople_2(people, minYear, maxYear) << endl;
}