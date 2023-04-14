#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "helper.h"
#include "Edge.h"
#include "Vertex.h"

class Graph
{
    public:
        Graph(E_DIRECTION e_GraphType = BI_DIRECTIONAL);
        ~Graph();
        
        void release();
        
        bool AddVertex(std::string sName);
        bool AddEdge(std::string sNameA, std::string sNameB, int weight = 0);
        
        bool HasVertex(std::string sName) const;
        
        // Return true if two vertices has direct path
        bool HasDirectEdge(std::string sNameA, std::string sNameB, bool bInOrder = true);
        
        // Return Weight of direct edge between two vertices
        bool GetWeight(std::string sNameA, std::string sNameB, int &weight, bool bInOrder = true);
        
        Vertex* GetVertex(std::string sName);
        
        std::vector<Edge *> GetEdges(std::string sNameA, std::string sNameB);
        
        bool RemoveVertex(std::string sName);
        
        bool RemoveEdge(std::string sNameA, std::string sNameB, int weight = 0, bool bInOrder = true);
        bool RemoveEdge(Edge *edge);
        
    private:
        Edge* CreateEdge(int weight = 0);
        Vertex* CreateVertex(std::string sName);

    private:
        const E_DIRECTION                   m_eGraphType;
        std::map<std::string, Vertex *>     m_mAllVertex;
};

#endif