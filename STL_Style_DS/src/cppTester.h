#ifndef __CPP_TESTER_H__
#define __CPP_TESTER_H__

#include <vector>
#include <unordered_map>

namespace nsCpp_DS { namespace nsCpp_Tester {
void print(const char *msg, bool pass)
{
	if (pass)
	{
		printf("PASS : %s\n", msg);
	}
	else
	{
		printf("FAIL : %s\n", msg);
	}
}

void test_C_Stack(const char *msg)
{
	printf(msg);
	using namespace nsC_DS::nsC_Stack;
	const int maxSize = 9;
	Stack<int> stack(maxSize);

	bool ret = true;
	print("Stack empty test.", (size(stack) == 0));

	int arr[maxSize] = { 15, 10, 20, 8, 12, 18, 25, 19, 30 };
	//int arrSize = sizeof(arr) / sizeof(arr[0]);

	for (int i = 0; i < maxSize; i++)
	{
		push(stack, arr[i]);
	}

	print("Stack size test.", (size(stack) == maxSize));

	for (int i = maxSize - 1; i >= 0; --i)
	{
		int value;
		if (!top(stack, value) || value != arr[i])
		{
			ret = false;
			break;
		}
		pop(stack);
	}
	
	print("Stack after all pop, size test.", (size(stack) == 0));
	print("Stack final test.\n\n", ret);
}

void test_C_List(const char *msg)
{
	printf(msg);
	using namespace nsC_DS::nsC_List;
	int arr[] = { 15, 10, 20, 8, 12, 18, 25, 19, 30, 15, 10, 20, 8, 12, 18, 25, 19, 30 };
	int arrSize = sizeof(arr) / sizeof(arr[0]);

	List<int>* list = createList<int>();

	bool ret = true;
	print("List empty test.", (size(list) == 0));
	for (int i = 0; i < arrSize; i++)
	{
		pushFront(list, arr[i]);
	}
	print("List size test.", (size(list) == arrSize));

	std::vector<int> vec;
	traverse(list, vec);
	for (int i = arrSize - 1, j = 0; i >= 0; --i, ++j)
	{
		if (vec[i] != arr[j])
		{
			ret = false;
			break;
		}
	}
	
	print("List pushFront test.", ret);
	deleteList(list);
	print("List delete test.", size(list) == 0 && list == nullptr);

	list = createList<int>();

	for (int i = 0; i < arrSize; i++)
	{
		pushBack(list, arr[i]);
	}
	print("List size test.", (size(list) == arrSize));
	vec.clear();

	traverse(list, vec);
	for (int i = 0; i < arrSize; ++i)
	{
		if (vec[i] != arr[i])
		{
			ret = false;
			break;
		}
	}
	print("List pushBack test.", ret);
	deleteList(list);
	print("List delete test.\n\n", size(list) == 0 && list == nullptr);
}

void test_C_BST_InsertTester(nsC_DS::nsC_BST::Node<int> *&pRoot, bool bRecursive, std::vector<int> vec)
{
	bool ret = true;
	for (auto val : vec)
	{
		if (bRecursive)
		{
			ret = insertRecursive(pRoot, val);
		}
		else
		{
			ret = insertIterative(pRoot, val);
		}
		if (!ret)
			break;
		bRecursive = !bRecursive;
	}
	print("BST insertion test.", ret);
}

void test_C_BST_InsertCorrectnessTester(nsC_DS::nsC_BST::Node<int> *&pRoot, std::vector<int> vec)
{
	std::unordered_map<int, int> mm;
	for (auto val : vec)
	{
		mm[val]++;
	}

	bool ret = true;
	std::vector<std::pair<int, int>> out;
	inorder(pRoot, out);
	for (auto it : out)
	{
		if (!mm.count(it.first) || mm[it.first] != it.second)
		{
			ret = false;
			break;
		}
	}
	print("BST Inorder correctness test.", ret);

	ret = true;
	out.clear();
	preorder(pRoot, out);
	for (auto it : out)
	{
		if (!mm.count(it.first) || mm[it.first] != it.second)
		{
			ret = false;
			break;
		}
	}
	print("BST preorder correctness test.", ret);

	ret = true;
	out.clear();
	postorder(pRoot, out);
	for (auto it : out)
	{
		if (!mm.count(it.first) || mm[it.first] != it.second)
		{
			ret = false;
			break;
		}
	}
	print("BST postorder correctness test.", ret);
}

void test_C_BST_SearchTester(nsC_DS::nsC_BST::Node<int> *&pRoot, std::vector<int> vec)
{
	bool ret = true;
	int value = 1;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (vec[i] == value)
		{
			value++;
		}
		if (!search(pRoot, vec[i]))
		{
			ret = false;
			break;
		}
	}
	print("BST search test.", ret);
	ret = !search(pRoot, value);
	print("BST search test.", ret);
}

void test_C_BST_RemoveTester(nsC_DS::nsC_BST::Node<int> *&pRoot, std::vector<int> vec)
{
	std::unordered_map<int, int> mm;
	for (auto val : vec)
	{
		mm[val]++;
	}

	bool ret = true;
	int value;
	int count;
	for (auto it : mm)
	{
		value = it.first;
		count = it.second;

		for (int i = 0; i < count; ++i)
		{
			pRoot = remove(pRoot, it.first);
		}
		if (search(pRoot, value))
		{
			ret = false;
			break;
		}
	}
	print("BST Remove test.", ret);
}

void test_C_BST(const char* msg)
{
	printf(msg);
	using namespace nsC_DS::nsC_BST;
	Node<int>* pRoot{};

	std::unordered_map<char, std::vector<int>> tests;

	tests.emplace(std::make_pair('A', std::vector<int>{ 15, 10, 20, 8, 12, 18, 25, 19, 30, 15, 10, 20, 8, 12, 18, 25, 19, 30 }));
	tests.emplace(std::make_pair('B', std::vector<int>{ 15, 10, 20, 8, 12, 18, 25, 19, 30 }));
	tests.emplace(std::make_pair('C', std::vector<int>{ 15 }));

	bool ret = true;
	bool bRecursive = true;
	for (auto& it : tests)
	{
		std::vector<int> vec(it.second);
		test_C_BST_InsertTester(pRoot, bRecursive, vec);
		test_C_BST_SearchTester(pRoot, vec);
		test_C_BST_InsertCorrectnessTester(pRoot, vec);
		test_C_BST_RemoveTester(pRoot, vec);
	}
}
}}
#endif //__CPP_TESTER_H__