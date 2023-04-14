#pragma once

/*
	Towers of Hanoi :	In this classic problem of Tower of Hanoi, you have 3 towers and N disks of different sizes which can
						slide onto any tower. The puzzle starts with disks sorted in ascending order of size from top to bottom
						(i.e. each disk sits on top of an even larger one).
							You have the following constraints :
								1). only one disk can be moved at a time.
								2). a disk is slid off the top of one tower onto another tower.
								3). a disk connot be placed on top of a smaller disk.
						Write a program to move the disks from the first tower to the last using stacks.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

class Tower
{
public:
	Tower(int id)
		: m_index(id)
	{}

	int index()
	{
		return m_index;
	}

	void add(int disk)
	{
		if (!disks.empty() && disks.top() <= disk)
		{
			cout << "Error placing disk : " << disk << endl;
		}
		else
		{
			disks.push(disk);
		}
	}

	void moveTopTo(Tower &t)
	{
		int topVal = disks.top();
		disks.pop();
		t.add(topVal);
	}

	void moveDisks(int n, Tower &destination, Tower &buffer)
	{
		if (n > 0)
		{
			moveDisks(n - 1, buffer, destination);
			moveTopTo(destination);
			buffer.moveDisks(n - 1, destination, *this);
		}
	}
private:
	int			m_index;
	stack<int>	disks;
};

class Solution
{
public:
	Solution()
		: towers({ 0, 1, 2 })
	{}

	void moveAllDisks(int numOfDisk)
	{
		if (numOfDisk <= 0)
			return;

		for (int i = numOfDisk - 1; i >= 0; --i)
			towers[0].add(i);

		towers[0].moveDisks(numOfDisk, towers[2], towers[1]);
	}
private:
	vector<Tower> towers;
};

int main()
{
	Solution sol;
	int n = 3;

	sol.moveAllDisks(n);

	return 0;
}
