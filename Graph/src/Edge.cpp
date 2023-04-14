#include "Edge.h"
#include "Vertex.h"
#include "helper.h"

using namespace std;

Edge::Edge(E_DIRECTION e_direction, int weight)
    :m_eDIRECTION(e_direction)
    ,m_nWeight(weight)
    ,m_vSrcVertex(nullptr)
    ,m_vDstVertex(nullptr)
{
    
}

Edge::~Edge()
{
    release();
}

void Edge::release()
{
    // TODO:: No work required as such now
}

void Edge::SetWeight(int weight)
{
    m_nWeight = weight;
}

void Edge::SetSrcVertex(Vertex *src)
{
    SAFE_RELEASE(m_vSrcVertex);
    m_vSrcVertex = src;
}

void Edge::SetDstVertex(Vertex *dst)
{
    SAFE_RELEASE(m_vDstVertex);
    m_vDstVertex = dst;
}

int Edge::GetWeight() const
{
    return m_nWeight;
}

Vertex* Edge::GetSrcVertex()
{
    return m_vSrcVertex;
}

Vertex* Edge::GetDstVertex()
{
    return m_vDstVertex;
}

void Edge::display() const
{
    cout << "EdgeType : " << DirectionEnumtoString(m_eDIRECTION);
    cout << "Source : " << m_vSrcVertex->GetName();
    cout << "Destination : " << m_vDstVertex->GetName();
    cout << "Weight : " << m_nWeight << endl;
 }