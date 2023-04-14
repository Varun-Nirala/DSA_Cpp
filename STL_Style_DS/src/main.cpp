#include <iostream>
#include <xutility>
#include <vector>
#include <string>
#include "Tree/trieTree.h"
#include "DynamicProgramming/solveSudoku.h"
#include "DynamicArray/buffer.h"
#include "Common/helper.h"
#include "Common/allocator_traits.h"
#include "DynamicArray/dynamicVector.h"
#include "Sorting/sorting_N2.h"
#include "Sorting/sorting_NLogN.h"
#include "List/singleList.h"
#include "List/doubleList.h"
#include "DisJointSet.h"
#include "priorityQueue.h"

#include "cppFeatures.h"
#include "Common/testClass.h"

#include "PowerSet.h"

using std::cout;
using std::endl;
using namespace nsCpp_DS;

using namespace std;

int main(int /*argc*/, char** /*argv*/)
{
	/*ns_Util::test_CppFeatures();
	
	//test_DynamicVector();
	test_TrieTree();
	test_SudokuSolver();
	test_Buffer();

	test_SortingN2();
	test_SortingNLogN();
	test_SingleList();
	test_DoubleList();

	ns_Util::test_PowerSet();
	test_DisJointSet();*/

    //test_SortingNLogN();
	TrieTree_testAll();
	PriorityQueue_testAll();

	return 0;
}