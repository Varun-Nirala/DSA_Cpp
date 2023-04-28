#include <iostream>
#include "2_AddTwoNumbersList.h"
#include "23_Merge_k_Sorted_Lists.h"
#include "43_MultiplyStrings.h"
#include "49_GroupAnagrams.h"
#include "51_N_Queens.h"
#include "55_JumpGame.h"
#include "59_SpiralMatrixII.h"
#include "79_WordSearch.h"
#include "92_ReverseLinkedList_II.h"
#include "143_ReorderList.h"
#include "328_OddEvenLinkList.h"
#include "437_PathSum_III.h"
#include "707_DesignLinkList.h"
#include "832_FlippingAnImage.h"
#include "994_RottenOranges.h"
#include "1002_FindCommonChars.h"
#include "1007_MinimumDominoRotationsForEqualRow.h"
#include "1071_GCD_Of_Strings.h"
#include "1221_SplitAStringInBalancedStrings.h"

#include "bitManipulation.h"
#include "codeVsZombies.h"
#include "cuttingPaperSquares.h"
#include "smallestHeightTriangle.h"
#include "summingTheN_Series.h"

using namespace std;

int main()
{
	nsCP::Solution2 sol2;
	nsCP::Solution2 sol23;
	nsCP::Solution2 sol43;
	nsCP::Solution2 sol49;
	nsCP::Solution2 sol51;
	nsCP::Solution2 sol55;
	nsCP::Solution2 sol59;
	nsCP::Solution2 sol79;
	nsCP::Solution2 sol92;
	nsCP::Solution2 sol143;
	nsCP::Solution2 sol328;
	nsCP::Solution2 sol437;
	nsCP::Solution2 sol707;
	nsCP::Solution2 sol832;
	nsCP::Solution2 sol994;
	nsCP::Solution2 sol1002;
	nsCP::Solution2 sol1007;
	nsCP::Solution2 sol1071;
	nsCP::Solution2 sol1221;

	sol2.test();
	sol23.test();
	sol43.test();
	sol49.test();
	sol51.test();
	sol55.test();
	sol59.test();
	sol79.test();
	sol92.test();
	sol143.test();
	sol328.test();
	sol437.test();
	sol707.test();
	sol832.test();
	sol994.test();
	sol1002.test();
	sol1007.test();
	sol1071.test();
	sol1221.test();
	
	test_bitManipulation();
	test_smallestHeightTriangle();
	test_codeVsZombies();
	test_summingTheN_Series();
	return 0;
}

