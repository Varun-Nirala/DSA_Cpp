#include <iostream>

#include "hash_map.h"

using namespace std;

template <typename Map, typename Key>
void findAndPrint(Map &mMap, const Key &key)
{
	cout << "Finding Key = " << key << "\n\t";
	auto it = mMap.find(key);

	if (it != mMap.end())
		cout << key << " maps to " << it->first << endl;
	else
		cout << key << " not found" << endl;
}

int main()
{
	HashMap::hash_map<int, int> myHashMap;

	for (int i = 1; i <= 10; ++i)
	{
		myHashMap.insert(make_pair(i, i * 10));
	}

	findAndPrint(myHashMap, 2);

	findAndPrint(myHashMap, 20);

	myHashMap.erase(2);
	findAndPrint(myHashMap, 2);

	myHashMap[20] = 200;
	findAndPrint(myHashMap, 200);

	HashMap::hash_map<string, int> mMap;

	mMap.insert(make_pair("KeyOne", 100));
	mMap.insert(make_pair("KeyTwo", 200));
	mMap.insert(make_pair("KeyThree", 300));

	for (auto it = mMap.begin(); it != mMap.end(); ++it)
	{
		cout << it->first << " -> " << it->second << endl;
	}

	for (auto &p : mMap)
	{
		cout << p.first << " -> " << p.second << endl;
	}

	getchar();

	return 0;
}