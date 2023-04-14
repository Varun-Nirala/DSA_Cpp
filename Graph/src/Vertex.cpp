#include "Vertex.h"
#include <vector>
#include <algorithm>

using namespace std;

Vertex::Vertex(string sName)
    :m_sName(sName)
{
}

Vertex::~Vertex()
{
    release();
}

void Vertex::release()
{
    // TODO::update all incoming edges and remove all outgoing edges
    for_each(m_vInWardEdge.begin(), m_vInWardEdge.end(), [this](Edge *edge) { return RemoveInEdge(edge); });
    for_each(m_vOutWardEdge.begin(), m_vOutWardEdge.end(), [this](Edge *edge) { return RemoveOutEdge(edge); });
}

bool Vertex::PushInEdge(Edge *edge)
{
    if(!edge)
    {
        return false;
    }
    RemoveInEdge(edge);
    m_vInWardEdge.push_back(edge);
    return true;
}

bool Vertex::PushOutEdge(Edge *edge)
{
    if(!edge)
    {
        return false;
    }
    RemoveOutEdge(edge);
    m_vOutWardEdge.push_back(edge);
    return true;
}

string Vertex::GetName() const
{
    return m_sName;
}

const vector<Edge *>& Vertex::GetInEdges() const
{
    return m_vInWardEdge;
}

const vector<Edge *>& Vertex::GetOutEdges() const
{
    return m_vOutWardEdge;
}

int Vertex::sizeOfInEdge() const
{
    return m_vInWardEdge.size();
}

int Vertex::sizeOfOutEdge() const
{
    return m_vOutWardEdge.size();
}

bool Vertex::RemoveInEdge(Edge *edge)
{
    if(!edge)
    {
        return true;
    }
    
    vector<Edge *>::iterator it = find(m_vInWardEdge.begin(), m_vInWardEdge.end(), edge);
    if(it != m_vInWardEdge.end())
    {
        Vertex *vertex = (*it)->GetSrcVertex();
        if(vertex)
        {
            vertex->RemoveOutEdge(*it);
        }
        m_vInWardEdge.erase(it);
    }
    
    SAFE_DELETE(edge);
    return true;
}

bool Vertex::RemoveOutEdge(Edge *edge)
{
    if(!edge)
    {
        return true;
    }
    
    vector<Edge *>::iterator it = find(m_vOutWardEdge.begin(), m_vOutWardEdge.end(), edge);
    if(it != m_vOutWardEdge.end())
    {
        Vertex *vertex = (*it)->GetDstVertex();
        if(vertex)
        {
            vertex->RemoveOutEdge(*it);
        }
        m_vInWardEdge.erase(it);
    }
    
    SAFE_DELETE(edge);
    return true;
}

bool Vertex::RemoveEdge(Edge *edge)
{
    if(!edge)
    {
        return true;
    }
    bool rc = RemoveInEdge(edge) || RemoveOutEdge(edge);
    SAFE_DELETE(edge);
    return rc;
}

void Vertex::display()
{
    cout << "Name : " << m_sName;
    cout << "No. of InWard Edges : " << sizeOfInEdge();
    cout << "No. of OutWard Edges : " << sizeOfOutEdge();
    
    cout << "InWard Edges :: Start -> \n";
    for(Edge *e : m_vInWardEdge)
    {
        e->display();
    }
    cout << "\nInWard Edges :: End.";
    
    cout << "\n\nOutWard Edges :: Start -> \n";
    for(Edge *e : m_vOutWardEdge)
    {
        e->display();
    }
    cout << "\nOutWard Edges :: End.";
}