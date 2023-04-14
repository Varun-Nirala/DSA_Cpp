#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "helper.h"
#include "Edge.h"

class Vertex
{
    public:
        Vertex(std::string sName);
        ~Vertex();

        void release();

        bool PushInEdge(Edge *edge);
        bool PushOutEdge(Edge *edge);

        std::string GetName() const;
        const std::vector<Edge *>& GetInEdges() const;
        const std::vector<Edge *>& GetOutEdges() const;
        int sizeOfInEdge() const;
        int sizeOfOutEdge() const;

        bool RemoveInEdge(Edge *edge);
        bool RemoveOutEdge(Edge *edge);
        bool RemoveEdge(Edge *edge);

        void display();
        
    private:
        std::string             m_sName;
        std::vector<Edge *>     m_vInWardEdge;
        std::vector<Edge *>     m_vOutWardEdge;
};

#endif