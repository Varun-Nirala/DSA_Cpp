#pragma once
#include <iostream>
#include <unordered_map>
#include <cassert>

using namespace std;

struct Node
{
    int             m_key{};
    int             m_value{};
    Node            *m_next{};
    Node            *m_prev{};

    Node(int key, int val)
        : m_key(key)
        , m_value(val)
    {}

    Node()
    {}
};

class Cache
{
public:
    Cache() = default;

    ~Cache() = default;

    inline int size() const { return m_size; }
    inline bool empty() const { return m_size == 0; }

    Node* push_front(int key, int val)
    {
        Node* temp = new Node(key, val);
        if (empty())
        {
            m_list.m_next = m_list.m_prev = temp;
        }
        else
        {
            m_list.m_next->m_prev = temp;
            temp->m_next = m_list.m_next;
            m_list.m_next = temp;
        }
        m_size++;
        return m_list.m_next;
    }

    Node* push_back(int key, int val)
    {
        Node* temp = new Node(key, val);
        if (empty())
        {
            m_list.m_next = m_list.m_prev = temp;
        }
        else
        {
            m_list.m_prev->m_next = temp;
            temp->m_prev = m_list.m_prev;
            m_list.m_prev = temp;
        }
        m_size++;
        return m_list.m_prev;
    }

    pair<int, int> front()
    {
        if (!empty())
            return { m_list.m_next->m_key, m_list.m_next->m_value };
        return { INT_MIN, INT_MIN };
    }

    pair<int, int> back()
    {
        if (!empty())
            return { m_list.m_prev->m_key, m_list.m_prev->m_value };
        return { INT_MIN, INT_MIN };
    }

    void moveToFront(Node* node)
    {
        if (node == m_list.m_next || !node)// if HEAD or NULL
            return;

        if (node == m_list.m_prev)// if tail
        {
            m_list.m_prev = node->m_prev;
            m_list.m_prev->m_next = nullptr;
        }

        // detach the node
        node->m_prev->m_next = node->m_next;
        if(node->m_next)
            node->m_next->m_prev = node->m_prev;
        
        m_list.m_next->m_prev = node;
        node->m_next = m_list.m_next;
        node->m_prev = nullptr;
        m_list.m_next = node;
    }

    void print()
    {
        cout << "size = " << m_size << ", Head = " << m_list.m_next << " , Tail = " << m_list.m_prev << endl;

        Node* p = m_list.m_next;
        while (p != nullptr)
        {
            cout << "[" << p << " | {" << p->m_key << ", " << p->m_value << " }]->";
            p = p->m_next;
        }
        cout << endl;
    }

private:
    Node        m_list{};          // next will have head node, and prev will have tail node
    int         m_size{};
};

class LRUCache
{
    unordered_map<int, Node*>       m_mm;       // key to index
    Cache                           m_cache;    // cache
    int                             m_cap{};

public:
    LRUCache(int capacity)
        :m_cap(capacity)
    {}

    int get(int key) {
        if (m_mm.count(key))
        {
            Node* p = m_mm[key];
            m_cache.moveToFront(p);
            return m_mm[key]->m_value;
        }
        return -1;
    }

    void put(int key, int value) {
        if (m_mm.count(key))
        {
            Node* p = m_mm[key];
            p->m_value = value;
            m_cache.moveToFront(p);
        }
        else if (m_cache.size() < m_cap)
        {
            m_mm[key] = m_cache.push_front(key, value);
        }
        else
        {
            const pair<int, int>& val = m_cache.back();
            Node* p = m_mm[val.first];
            m_mm.erase(val.first);

            p->m_key = key;
            p->m_value = value;
            m_cache.moveToFront(p);
            m_mm[key] = p;
        }
    }

    void print()
    {
        m_cache.print();
    }
};

void testLRU()
{
    //vector<string> inputCmd = { "put", "put", "get", "put", "get", "put", "get", "get", "get" };
    //int capacity = 2;
    //vector<int> input = { 1, 1, 2, 2, 1, 3, 3, 2, 4, 4 , 1 , 3 , 4 };
    //
    //vector<string> inputCmd = { "put", "put", "get", "put", "put", "get" };
    //int capacity = 2;
    //vector<int> input = { 2, 1, 2, 2, 2, 1, 1, 4, 1, 2 };

    vector<string> inputCmd = { "put", "put", "put", "put", "get", "get", "get", "get", "put", "get", "get", "get", "get", "get" };
    int capacity = 3;
    vector<int> input = { 1, 1, 2, 2, 3, 3, 4, 4, 4, 3, 2, 1, 5, 5, 1, 2, 3, 4, 5 };

    LRUCache* obj = new LRUCache(capacity);

    int i = 0;
    cout << "null, ";
    for (auto cmd : inputCmd)
    {
        if (cmd == "put")
        {
            int key = input[i++];
            int val = input[i++];

            cout << "Cmd = PUT , key = " << key << " , value = " << val << endl;
            obj->print();

            obj->put(key, val);
            cout << "null, ";
        }
        else if (cmd == "get")
        {
            int key = input[i++];

            cout << "Cmd = GET , key = " << key << endl;
            obj->print();
            int val = obj->get(key);
            cout << val << ", ";
        }
        else
        {
            assert("Invalid command");
        }
    }
}
