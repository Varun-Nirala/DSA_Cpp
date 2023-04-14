#ifndef __EDGE_H__
#define __EDGE_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "helper.h"

class Vertex;   //Forward Decleration for Edge Class

class Edge
{
    public:
        Edge(E_DIRECTION e_direction = BI_DIRECTIONAL, int weight = 0);
        ~Edge();

        void release();
        
        // Setters
        void SetWeight(int weight);
        void SetSrcVertex(Vertex *src);
        void SetDstVertex(Vertex *dst);

        // Getters
        int GetWeight() const;
        Vertex* GetSrcVertex();
        Vertex* GetDstVertex();

        void display() const;
        
    private:
        E_DIRECTION         m_eDIRECTION;
        int                 m_nWeight;
        Vertex              *m_vSrcVertex;
        Vertex              *m_vDstVertex;
};

#endif