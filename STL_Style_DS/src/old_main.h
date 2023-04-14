#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <stack>
#include <cmath>
#include <string>

//Searching
#include "binarySearch.h"

//Sorting
#include "bubbleSort.h"
#include "selectionSort.h"
#include "insertionSort.h"
#include "quickSort.h"
#include "mergeSort.h"
#include "heapSort.h"
#include "test.h"
#include <unordered_set>
#include <set>
#include "LRU.h"
#include <cassert>
#include "heap.h"
#include "multiplyStrings.h"
#include "groupAnagrams.h"
#include "AddTwoNumbersList.h"

#include "addVectorMultiThread.h"

#include "MySharedPtr.h"

using namespace std;



#include <iostream>

//Searching
#include "binarySearch.h"

//Sorting
#include "bubbleSort.h"
#include "selectionSort.h"
#include "insertionSort.h"
#include "quickSort.h"
#include "mergeSort.h"
#include "heapSort.h"

//Longest common subsequence
#include "LCS.h"

#include "BST.h"

#include "PriorityQueue.h"

#include "BigNumber.h"

using namespace std;

void testSearching()
{
	test_binSearch();
}

void testSorting()
{
	test_bubbleSort();
	test_selectionSort();
	test_insertionSort();
	test_quickSort();
	test_mergeSort();
	test_heapSort();
}

void testLCS()
{
	cout << findLCS("XMJYAUZ", "MZJAWXU") << endl;

	//cout << findLCS("GAC", "AGCAT") << endl;
	//cout << findLCS("AGGTAB" , "GXTXAYB") <<  endl;
	//cout << findLCS("ABCDGH", "AEDFHR") << endl;
}



// MBition test START
void calculateUniqueSubStr(const string& s, set<string>& subMap)
{
    if (s.size() < 3) return;

    string prefix = s.substr(0, s.size() - 1);
    string suffix = s.substr(1);

    
    if (!subMap.count(prefix))
    {
        subMap.insert(prefix);
        calculateUniqueSubStr(prefix, subMap);
    }

    if (!subMap.count(suffix))
    {
        subMap.insert(suffix);
        calculateUniqueSubStr(suffix, subMap);
    }
}

long substringCalculator(string s) {
    set<string> subMap;

    for (int i = 0; i < s.size() - 1; ++i)
    {
        subMap.insert(string(1, s[i]));
        subMap.insert(s.substr(i, 2));
    }

    calculateUniqueSubStr(s, subMap);

    for (auto a : subMap)
    {
        cout << a << endl;
    }

    return subMap.size();
}
// MBittion test end

int maxSumSubArray(const vector<int>& arr, int sId, int eId)
{
    int max_end_here = 0;
    int ans = 0;

    while (sId <= eId)
    {
        max_end_here += arr[sId++];

        if (max_end_here > ans)
        {
            ans = max_end_here;
        }

        if (max_end_here < 0)
        {
            max_end_here = 0;
        }
    }
    return ans;
}

// Complete the maxSubsetSum function below.
int maxSubsetSum(vector<int> arr) {

    if (arr.size() < 3) return 0;

    bool anyPositive = false;
    for (auto a : arr)
    {
        if (a > 0)
        {
            anyPositive = true;
            break;
        }
    }

    if (!anyPositive) return 0; // return 0, if no positive numbers

    //divide the problem into finding the max contiguous subarray problem, by creating 2 arr with non-adjacent values

    int mid = 0;
    for (int i = 1, j = arr.size() - 2; i < j; i++, j--)
    {
        mid = i + 1;
        swap(arr[i], arr[j]);
    }

    return max(maxSumSubArray(arr, 0, mid), maxSumSubArray(arr, mid, arr.size() - 1));
}

// Subarray Count :
//          Given an Array of N Elements:
//          Find the count of sub-arrays, such that the product of elements in it is ODD
long long countSubarray(int N, vector<int> A) {
    // Write your code here
    int64_t ans = 0;

    int lastEvenNumId = -1;
    int oddNumsCount = 0;
    for (int i = 0; i < N; ++i)
    {
        if (A[i] % 2 == 0)
        {
            oddNumsCount = i - lastEvenNumId - 1;

            ans += (oddNumsCount * (oddNumsCount + 1) / 2);
            lastEvenNumId = i;
        }
    }

    oddNumsCount = N - lastEvenNumId - 1;
    ans += (oddNumsCount * (oddNumsCount + 1) / 2);

    return ans;
}

int** MatMalloc(int r, int c)
{
    int headerSize = r * sizeof(int*);
    int dataSize = r * c * sizeof(int);

    int** rawPtr = (int **)malloc(headerSize + dataSize);

    int* buf = (int *) (rawPtr + r);

    for (int i = 0; i < r; ++i)
    {
        rawPtr[i] = (int *)(buf + i * c);
    }
    return rawPtr;
}

void testMatMalloc()
{
    int r = 2;
    int c = 5;
    int** mat = MatMalloc(r, c);

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void helper(int lt, int rt, string str)
{
    if (lt == 0 && rt == 0)
    {
        cout << str << endl;
    }

    if (lt > 0)
    {
        helper(lt - 1, rt, str + "(");
    }

    if (rt > 0 && lt < rt)
    {
        helper(lt, rt - 1, str + ")");
    }
}

void createAllValidParen(int num)
{
    helper(num, num, "");
}

class Solution6 {
    vector<vector<int>> move{ {-1, 0},   //top
                             {0, -1},   // left
                             {1, 0},    //bottom
                             {0, 1} };    //right


    int solve(vector<vector<int>>& vec, int r, int c, int rows, int cols)
    {
        if (r >= rows || c >= cols)
            return 0;

        int nextR = -1;
        int nextC = -1;
        int nextMin = vec[r][c];
        for (const auto& dir : move)
        {
            int rr = r + dir[0];
            int cc = c + dir[1];
            if (rr >= 0 && rr < rows && cc >= 0 && cc < cols && vec[rr][cc] > 1)
            {
                cout << rr << ", " << cc << endl;
                if (vec[rr][cc] > vec[r][c])
                {
                    if (nextR == -1 && nextC == -1)
                    {
                        nextR = rr;
                        nextC = cc;
                    }
                    if (nextMin >= vec[rr][cc])
                    {
                        nextMin = vec[rr][cc];
                        nextR = rr;
                        nextC = cc;
                    }
                }
            }
        }
        if (nextR != -1 && nextC != -1)
        {
            vec[r][c] = 1;
            return solve(vec, nextR, nextC, rows, cols) + 1;
        }
        return -1;
    }
public:
    int cutOffTree(vector<vector<int>>& forest) {
        if (forest[0][0] == 0)
            return -1;

        return solve(forest, 0, 0, forest.size(), forest[0].size());
    }
};


using namespace std;

long MOD = pow(10, 9) + 7;

typedef struct Node
{
	int         m_data;
	Node        *m_pParent;
	set<Node *> m_sChild;

	Node(int val, Node *parent = nullptr)
		:m_data(val)
		, m_pParent(parent)
	{}
}Node;

class Tree
{
public:
	Tree(vector<vector<int>> vec);
	~Tree();

	int dist(int u, int v);

	void levelOrder();

private:
	map<int, Node *>    m_mAllNode;
	Node                *m_pRoot;
	map<string, int>    m_mDistance;
};

Tree::Tree(vector<vector<int>> vec)
:m_pRoot(nullptr)
{
	Node *u = nullptr, *v = nullptr;
	int size = vec.size();

	if (size)
	{
		m_pRoot = new Node(vec[0][0]);
		m_mAllNode[m_pRoot->m_data] = m_pRoot;
	}

	for (int i = 0; i < size; ++i)
	{
		auto x = m_mAllNode.find(vec[i][0]);
		if (x != m_mAllNode.end())
		{
			u = x->second;
		}
		else
		{
			u = new Node(vec[i][0]);
			m_mAllNode[u->m_data] = u;
		}

		x = m_mAllNode.find(vec[i][1]);
		if (x != m_mAllNode.end())
		{
			v = x->second;
		}
		else
		{
			v = new Node(vec[i][1]);
			m_mAllNode[v->m_data] = v;
		}

		v->m_pParent = u;
		u->m_sChild.insert(v);
	}
}

Tree::~Tree()
{
	for (auto x : m_mAllNode)
	{
		delete x.second;
	}
	m_pRoot = nullptr;
}

int Tree::dist(int u, int v)
{
	int ans = 0;

	string key = to_string(u) + "," + to_string(v);

	auto it = m_mDistance.find(key);
	if (it != m_mDistance.end())
	{
		return it->second;
	}

	key = to_string(v) + "," + to_string(u);
	it = m_mDistance.find(key);
	if (it != m_mDistance.end())
	{
		return it->second;
	}

	auto uN = m_mAllNode.find(u);
	auto vN = m_mAllNode.find(v);

	set<int> visited;

	if (uN != m_mAllNode.end() && vN != m_mAllNode.end())
	{
		stack<Node *> s;
		s.push(uN->second);
		bool inserted = false;
		while (!s.empty())
		{
			inserted = false;
			Node *curr = s.top();

			s.pop();

			if (curr->m_data == v)
			{
				break;
			}

			if (curr->m_pParent && visited.find(curr->m_pParent->m_data) == visited.end())
			{
				inserted = true;
				s.push(curr->m_pParent);
			}
			for (auto x : curr->m_sChild)
			{
				if (visited.find(x->m_data) == visited.end())
				{
					inserted = true;
					s.push(x);
				}
			}
			if (inserted)
				ans++;
			visited.insert(curr->m_data);
		}
	}

	m_mDistance[key] = ans;

	return ans;
}

void Tree::levelOrder()
{
	if (m_mAllNode.empty())
	{
		return;
	}

	Node *p = m_mAllNode.begin()->second;

	queue<Node *> q;
	q.push(p);
	while (!q.empty())
	{
		p = q.front();
		q.pop();

		cout << "Child of : " << p->m_data << " , are :: ";

		for (auto x : p->m_sChild)
		{
			q.push(x);
			cout << x->m_data << " ";
		}
		cout << "\n";
	}
}

int print(int n)
{
	printf("Num = %d\n", n);
	return n;
}

int old_main()
{
	int n, m;

	cin >> n >> m;
	int a, b;

	vector<vector<int>> vec;
	vector<vector<int>> q;

	for (int i = 0; i < n - 1; ++i)
	{
		cin >> a >> b;
		vec.push_back(vector<int>{ a, b});
	}

	for (int i = 0; i < m; ++i)
	{
		cin >> a;
		vector<int> v;
		while (a--)
		{
			cin >> b;
			v.push_back(b);
		}
		q.push_back(v);
	}

	Tree tree(vec);

	int size;
	long ans;

	int u, v;
	for (int i = 0; i < q.size(); ++i)
	{
		ans = 0;
		size = q[i].size();
		if (size == 2)
		{
			u = q[i][0];
			v = q[i][1];
			ans = (u * v * tree.dist(u, v));
		}
		else if (size > 2)
		{
			for (int j = 0; j < size - 1; j++)
			{
				for (int k = j + 1; k < size; k++)
				{
					u = q[i][j];
					v = q[i][k];
					ans += (u * v * tree.dist(u, v));
				}
			}
		}
		cout << ans % MOD << "\n";
	}

	test_binSearch();

	test_bubbleSort();
	test_selectionSort();
	test_insertionSort();
	test_quickSort();
	test_mergeSort();
	test_heapSort();

	getchar();
	getchar();
	
	
	//vector<int> vec{ 9, 6, 15, 7, 1 };
    //int expectedAns = 7; // {15, 7, 1}, {15, 7}, {7, 1}, {9}, {15}, {7}, {1}
    //countSubarray(vec.size(), vec);

    //subStrSearch("", "abcdabca");

    Solution6 sol;

    vector<vector<int>> vec{ {1, 2, 3}, {0, 0, 4}, {7, 6, 5} };

    cout << sol.cutOffTree(vec) << endl;

    return 0;
	
	return 0;
}