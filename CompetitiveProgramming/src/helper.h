#ifndef __HELPER_H__
#define __HELPER_H__

#include <initializer_list>
#include <iostream>
#include <vector>
#include <string>

namespace nsCP
{
template<typename T>
struct ListNode
{
    T           val{};
    ListNode    *next{};

    ListNode() : val(0), next(nullptr) {}
    ListNode(T x) : val(x), next(nullptr) {}
    ListNode(T x, ListNode<T> *next) : val(x), next(next) {}
};

template<typename T>
struct TreeNode
{
    T               val{};
    TreeNode        *lc{};
    TreeNode        *rc{};
    TreeNode() : val(0), lc(nullptr), rc(nullptr) {}
    TreeNode(T x) : val(x), lc(nullptr), rc(nullptr) {}
    TreeNode(T x, TreeNode* left, TreeNode* right) : val(x), lc(left), rc(right) {}
};

template<typename T>
TreeNode<T>* createTree(const std::vector<T> &vec, const T &null)
{
    size_t id = 0;
    size_t size = vec.size();

    TreeNode<T>* root = new TreeNode<T>(vec[id++]);
    std::queue<TreeNode<T>*> q;
    q.push(root);

    TreeNode<T>* p = nullptr;
    while (id < size)
    {
        p = q.front();
        q.pop();
        if (vec[id] != null)
        {
            p->lc = new TreeNode(vec[id]);
            q.push(p->lc);
        }
        id++;
        if (vec[id] != null)
        {
            p->rc = new TreeNode(vec[id]);
            q.push(p->rc);
        }
        id++;
    }

    return root;
}

template<typename T>
ListNode<T>* createList(std::initializer_list<T> elements)
{
    ListNode<T> *head{};
    ListNode<T> *p{};

    for (auto a : elements)
    {
        if (!head)
        {
            p = head = new ListNode<T>(a);
        }
        else
        {
            p->next = new ListNode<T>(a);
            p = p->next;
        }
    }
    return head;
}

template<typename T>
ListNode<T>* createList(std::vector<T> elements)
{
    ListNode<T>* head{};
    ListNode<T>* p{};

    for (auto a : elements)
    {
        if (!head)
        {
            p = head = new ListNode<T>(a);
        }
        else
        {
            p->next = new ListNode<T>(a);
            p = p->next;
        }
    }
    return head;
}

template<typename T>
void print(ListNode<T>* root, const std::string msg = "")
{
    std::cout << msg << '\n';
    std::cout << "PRINTING LIST\n";
    while (root)
    {
        std::cout << root->val << " -> ";
        root = root->next;
    }
    std::cout << "NULL\n\n";
}

template<typename T>
void print(std::vector<T>& vec, const std::string msg = "")
{
    std::cout << msg << '\n';
    std::cout << "PRINTING VEC of SIZE = " << vec.size() << '\n';
    for (auto& a : vec)
    {
        std::cout << a << " , ";
    }
    std::cout << "\n\n";
}

template<typename T>
void print(std::vector<std::vector<T>>& grid, const std::string msg = "")
{
    std::cout << msg << '\n';
    std::cout << "PRINTING GRID\n";

    for (size_t i = 0; i < grid.size(); ++i)
    {
        for (size_t j = 0; j < grid[i].size(); ++j)
        {
            std::cout << grid[i][j] << " , ";
        }
        std::cout << '\n';
    }
    std::cout << "\n\n";
}

void print(std::string str, size_t totalTest, size_t failed)
{
    printf("%s\n", str.c_str());
    printf("Total Test = %5zu", totalTest);
    if (failed < totalTest)
    {
        printf(" , Passed = %5zu", totalTest - failed);
    }

    if (failed > 0)
    {
        printf(" , Failed = %5zu", failed);
    }
    printf("\n");
}

inline int as_int(char ch) { return ch - '0'; }
inline char as_char(int num) { return static_cast<char>(num + '0'); }

template<typename T>
ListNode<T>* reverseList(ListNode<T>* head)
{
    ListNode<T>* curr = head;
    ListNode<T>* next = nullptr;
    ListNode<T>* prev = nullptr;

    while (curr)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
}

#endif //#ifndef __HELPER_H__