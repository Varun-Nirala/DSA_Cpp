#ifndef __ADD_TWO_NUMBERS_LIST_2_H__
#define __ADD_TWO_NUMBERS_LIST_2_H__

#include <iostream>
#include <stack>
#include "helper.h"

namespace nsCP
{
class Solution2 {
public:
    void test()
    {
        printf("Test : Solution2  -> Add Two Lists : START\n");
        std::cout << "Add two lists : \n\n";
        ListNode<int>* l1 = createList<int>({ 2, 4, 3 });
        ListNode<int>* l2 = createList<int>({ 5, 6, 7 });

        ListNode<int>* p = addTwoNumbers(l1, l2);
        print(l1, "List 1 : ");
        print(l2, "List 2 : ");

        print(p, "There Sum : ");
        printf("Test : Solution2  -> Add Two Lists : END\n\n");
    }

private:
    template<typename T>
    ListNode<T>* addTwoNumbers(ListNode<T>* l1, ListNode<T>* l2)
    {
        if (!l1 && !l2)
            return nullptr;

        if (!l1)
            return l2;

        if (!l2)
            return l1;

        std::stack<T> s1, s2;

        while (l1)
        {
            s1.push(l1->val);
            l1 = l1->next;
        }

        while (l2)
        {
            s2.push(l2->val);
            l2 = l2->next;
        }

        const T NAN_ = -100;

        T sum = 0;
        int carry = 0;
        ListNode<T>* ans = new ListNode<T>(NAN_);
        ListNode<T>* p = ans;
        ListNode<T>* prev = nullptr;
        while (!s1.empty() && !s2.empty())
        {
            sum = carry + s1.top() + s2.top();
            s1.pop();
            s2.pop();
            carry = sum / 10;
            p->val = sum % 10;
            p->next = new ListNode<T>(NAN_);
            prev = p;
            p = p->next;
        }

        while (!s1.empty())
        {
            sum = carry + s1.top();
            s1.pop();
            carry = sum / 10;
            p->val = sum % 10;
            p->next = new ListNode<T>(NAN_);
            prev = p;
            p = p->next;
        }

        while (!s2.empty())
        {
            sum = carry + s2.top();
            s2.pop();
            carry = sum / 10;
            p->val = sum % 10;
            p->next = new ListNode<T>(NAN_);
            prev = p;
            p = p->next;
        }

        if (carry)
        {
            p->val = sum;
        }
        else
        {
            if (prev)
            {
                prev->next = nullptr;
            }
            free(p);
            p = nullptr;
        }
        prev = nullptr;

        //reverse ans
        return reverseList(ans);
    }
};
}
#endif  // __ADD_TWO_NUMBERS_LIST_2_H__
