#include <algorithm>
#include <utility>
#include "Graph.h"

using namespace std;

Graph::Graph(E_DIRECTION e_GraphType)
    :m_eGraphType(e_GraphType)
{
}

Graph::~Graph()
{
    release();
}

void Graph::release()
{
    // TDOD:: Implement whole cleanup
    for(pair<string, Vertex *> pair : m_mAllVertex)
    {
        Vertex *vertex = pair.second;
        SAFE_DELETE(vertex);
    }
}

Edge* Graph::CreateEdge(int weight)
{
    Edge *edge = new Edge(m_eGraphType, weight);
    return edge;
}

Vertex* Graph::CreateVertex(string sName)
{
    Vertex *vertex = new Vertex(sName);
    return vertex;
}

bool Graph::AddVertex(string sName)
{
    if(!HasVertex(sName))
    {
        Vertex *vVertex = CreateVertex(sName);
        m_mAllVertex.insert(make_pair(sName, vVertex));
        vVertex = nullptr;
        return true;
    }
    else
    {
        LOG_INFO(__func__, __LINE__, "Vertex already present.");
        return false;
    }
}

bool Graph::AddEdge(string sNameA, string sNameB, int weight)
{
    Edge *edge = nullptr;
    Vertex *vSrcVertex = GetVertex(sNameA);
    Vertex *vDstVertex = GetVertex(sNameB);
    
    if(vSrcVertex && vSrcVertex)
    {
        int rWeight = 0;
        if(GetWeight(sNameA, sNameB, rWeight) && rWeight == weight)
        {
            return true;
        }
    }
    else if(vSrcVertex)
    {
        vDstVertex = CreateVertex(sNameB);
        if(!vDstVertex)
        {
            LOG_ERROR(__func__, __LINE__, "Recieved nullptr in call to CreateVeretx.", 1);
        }
        m_mAllVertex.insert(make_pair(sNameB, vDstVertex));
    }
    else if(vDstVertex)
    {
        vSrcVertex = CreateVertex(sNameA);
        if(!vSrcVertex)
        {
            LOG_ERROR(__func__, __LINE__, "Recieved nullptr in call to CreateVeretx.", 1);
        }
        m_mAllVertex.insert(make_pair(sNameA, vSrcVertex));
    }
    else
    {
        vSrcVertex = CreateVertex(sNameA);
        vDstVertex = CreateVertex(sNameB);
        if(!vSrcVertex || !vDstVertex)
        {
            LOG_ERROR(__func__, __LINE__, "Recieved nullptr in call to CreateVeretx.", 1);
        }
        m_mAllVertex.insert(make_pair(sNameA, vSrcVertex));
        m_mAllVertex.insert(make_pair(sNameB, vDstVertex));
    }
    
    // Add the Edge
    {
        edge = CreateEdge(weight);
        edge->SetSrcVertex(vSrcVertex);
        edge->SetDstVertex(vDstVertex);
        
        switch(m_eGraphType)
        {
            case UNI_DIRECTIONAL:
                vSrcVertex->PushOutEdge(edge);
                vDstVertex->PushInEdge(edge);
                break;
            case BI_DIRECTIONAL:
                vSrcVertex->PushInEdge(edge);
                vSrcVertex->PushOutEdge(edge);
                
                vDstVertex->PushInEdge(edge);
                vDstVertex->PushOutEdge(edge);
                break;
            default:
                LOG_ERROR(__func__, __LINE__, "Wrong Graph Type, Graph data is corrupted.", 1);
        }
    }
    return true;
}

bool Graph::HasVertex(string sName) const
{
    map<string, Vertex *>::const_iterator it = m_mAllVertex.find(sName);
    if(it != m_mAllVertex.end())
    {
        return true;
    }
    return false;
}

bool Graph::HasDirectEdge(string sNameA, string sNameB, bool bInOrder)
{
    int weight;
    return GetWeight(sNameA, sNameB, weight, bInOrder);
}

bool Graph::GetWeight(string sNameA, string sNameB, int &weight, bool bInOrder)
{
    weight = 0;
    bool rc = false;
    
    Vertex *vVertexA = GetVertex(sNameA);
    Vertex *vVertexB = GetVertex(sNameB);
    
    if(!vVertexA || !vVertexB)
    {
        rc = false;
    }
    else if(m_eGraphType == UNI_DIRECTIONAL && bInOrder)
    {
        vector<Edge *> vEdges = vVertexA->GetOutEdges();
        
        vector<Edge *>::iterator it = find_if(vEdges.begin(), vEdges.end(), [sNameB](Edge *e) { return (e->GetDstVertex()->GetName() == sNameB); });
        if(it != vEdges.end())
        {
            weight = (*it)->GetWeight();
            rc = true;
        }
    }
    else    // Both UNI_DIRECTIONAL without order and BI_DIRECTIONAL are same
    {
        vector<Edge *> vEdges = vVertexA->GetInEdges();
        
        vector<Edge *>::iterator it = find_if(vEdges.begin(), vEdges.end(), [sNameB](Edge *e) { return (e->GetDstVertex()->GetName() == sNameB); });
        if(it != vEdges.end())
        {
            weight = (*it)->GetWeight();
            rc = true;
        }
        
        if(!rc)
        {
            vEdges = vVertexB->GetInEdges();
        
            vector<Edge *>::iterator it = find_if(vEdges.begin(), vEdges.end(), [sNameB](Edge *e) { return (e->GetDstVertex()->GetName() == sNameB); });
            if(it != vEdges.end())
            {
                weight = (*it)->GetWeight();
                rc = true;
            }
        }
    }
    return rc;
}

Vertex* Graph::GetVertex(string sName)
{
    map<string, Vertex *>::iterator it = m_mAllVertex.find(sName);
    if(it != m_mAllVertex.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

vector<Edge *> Graph::GetEdges(string sNameA, string sNameB)
{
    
}

bool Graph::RemoveVertex(string sNameA)
{
}

bool Graph::RemoveEdge(string sNameA, string sNameB, int weight, bool bInOrder)
{
}

bool Graph::RemoveEdge(Edge *edge)
{
}