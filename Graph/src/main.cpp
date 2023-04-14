#include <iostream>
#include <string>
#include <algorithm>
#include "helper.h"
#include "Graph.h"
#include "sstream"
using namespace std;

typedef enum E_OPERATION
{
    // A = ADD, S = SEARCH, R = REMOVE, V = VIEW
    EXIT = 0,
    A_VERTEX,
    A_EDGE,
    S_VERTEX,
    S_EDGE,
    V_VERTEX,
    V_EDGE,
    R_VERTEX,
    R_EDGE,
    CLEAR,          // CLEAR WHOLE GRAPH
    CREATE_UNI,     // CREATE UNI_DIRECTIONAL NEW GRAPH
    CREATE_BI,      // CREATE BI_DIRECTIONAL NEW GRAPH
    MAX
}E_OPERATION;

E_OPERATION Menu();

Graph* CreateGraph(E_DIRECTION eDirection);   //TODO:: Using it for noe, should use a Factory for it, and other Create Methods

int main(int argc, char **argv)
{
	Graph *graph = nullptr;
    E_OPERATION choice;
    bool bAgain = true;
    string sNameA, sNameB;
    bool bIsWeightedGraph = true;
    int weight;
    int input;
    bool success;
    
    E_DIRECTION eDirection;
    
    while(bAgain)
    {
        choice = Menu();

        switch(choice)
        {
            case CREATE_UNI:
            {
                cout << "Is graph weighted? (Press 0 for No): ";
                weight = ReadInput<int>();
                if(!weight)
                {
                    bIsWeightedGraph = false;
                }
                
                eDirection = UNI_DIRECTIONAL;
                SAFE_DELETE(graph);
                graph = CreateGraph(UNI_DIRECTIONAL);
                if(!graph)
                {
                    LOG_ERROR(__func__, __LINE__, "Failed to create Graph.", 1);
                }
                weight = 0;
                break;
            }
            case CREATE_BI:
            {
                cout << "Is graph weighted? (Press 0 for No): ";
                weight = ReadInput<int>();
                if(!weight)
                {
                    bIsWeightedGraph = false;
                }
                eDirection = BI_DIRECTIONAL;
                SAFE_DELETE(graph);
                graph = CreateGraph(BI_DIRECTIONAL);
                if(!graph)
                {
                    LOG_ERROR(__func__, __LINE__, "Failed to create Graph.", 1);
                }
                weight = 0;
                break;
            }
            case A_VERTEX:
            {
                cout << "Enter Vertex Name : ";
                sNameA = ReadInput<string>();
                graph->AddVertex(sNameA);
                break;
            }
            case A_EDGE:
            {
                if(eDirection == UNI_DIRECTIONAL)
                {
                    cout << "Enter SrcVertex Name : ";
                    sNameA = ReadInput<string>();
                    cout << "Enter DstVertex Name : ";
                    sNameB = ReadInput<string>();
                }
                else
                {
                    cout << "Enter Vertex A Name : ";
                    sNameA = ReadInput<string>();
                    cout << "Enter Vertex B Name : ";
                    sNameB = ReadInput<string>();
                }
                
                if(bIsWeightedGraph)
                {
                    cout << "Enter weight of the Edge : ";
                    weight = ReadInput<int>();
                }
                
                graph->AddEdge(sNameA, sNameB, weight);
                
                break;
            }
            case S_VERTEX:
            {
                cout << "Enter Vertex name : ";
                sNameA = ReadInput<string>();
                if(graph->HasVertex(sNameA))
                {
                    cout << "Vertex Found : " << sNameA << endl;
                }
                break;
            }
            case S_EDGE:
            {
                if(eDirection == UNI_DIRECTIONAL)
                {
                    cout << "Enter SrcVertex Name : ";
                    sNameA = ReadInput<string>();
                    cout << "Enter DstVertex Name : ";
                    sNameB = ReadInput<string>();
                    if(graph->HasDirectEdge(sNameA, sNameB))
                    {
                        success = true;
                        cout << "Edge Found. " << sNameA << "->" << sNameB << endl;
                        break;
                    }
                    if(!success)
                    {
                        if(graph->HasDirectEdge(sNameA, sNameB, false))
                        {
                            cout << "Found but in reverse order, i.e " << sNameB << " -> " << sNameA << endl;
                        }
                    }
                }
                else
                {
                    cout << "Enter Vertex A Name : ";
                    sNameA = ReadInput<string>();
                    cout << "Enter Vertex B Name : ";
                    sNameB = ReadInput<string>();
                    if(graph->HasDirectEdge(sNameA, sNameB, false))
                    {
                        cout << "Edge Found. " << sNameA << "->" << sNameB << endl;
                    }
                }
                break;
            }
            case R_VERTEX:
            {
                cout << "Enter Vertex name : ";
                sNameA = ReadInput<string>();
                if(graph->HasVertex(sNameA))
                {
                    success = graph->RemoveVertex(sNameA);
                    if(success)
                    {
                        cout << "Vertex : " << sNameA << ", Removed Successfully." << endl;
                    }
                    else
                    {
                        string msg;
                        msg = "Vertex : " + sNameA + " , Found but error while deleting.";
                        LOG_ERROR(__func__, __LINE__, msg, 1);
                    }
                }
                else
                {
                    cout << "Vertex Not Found." << endl;
                }
                break;
            }
            case R_EDGE:
            {
                if(eDirection == UNI_DIRECTIONAL)
                {
                    cout << "Enter SrcVertex Name : ";
                    sNameA = ReadInput<string>();
                    cout << "Enter DstVertex Name : ";
                    sNameB = ReadInput<string>();
                }
                else
                {
                    cout << "Enter Vertex A Name : ";
                    sNameA = ReadInput<string>();
                    cout << "Enter Vertex B Name : ";
                    sNameB = ReadInput<string>();
                }
                
                vector<Edge *> edges = graph->GetEdges(sNameA, sNameB);
                
                if(edges.size() == 0)
                {
                    cout << "No edge found between those two Vertices." << endl;
                }
                else if(edges.size() == 1)
                {
                    graph->RemoveEdge(edges[0]);
                    cout << "Removed Successfully.";
                }
                else
                {
                    cout << "More than one Edges found.\n";
                    cout << "Enter\n";
                    cout << "0. To remove all Edges.\n";
                    cout << "1. To see weight and select.\n";
                    
                    input = ReadInput<int>();
                    
                    if(!input)
                    {
                        for(Edge *e : edges)
                        {
                            graph->RemoveEdge(e);
                        }
                        cout << "All Edges Removed Successfully." << endl;
                    }
                    else
                    {
                        for(Edge *e : edges)
                        {
                            e->display();
                        }
                    
                        cout << "Enter the weight.";
                    
                        weight = ReadInput<int>();
                    
                        vector<Edge *>::iterator it = find_if(edges.begin(), edges.end(), [weight](Edge *e) { return (e->GetWeight() == weight);} );
                    
                        if(it != edges.end())
                        {
                            // Should always be true
                            graph->RemoveEdge(*it);
                            cout << "Edge Removed Successfully." << endl;
                        }
                    }
                }
                break;
            }
            case CLEAR:
            {
                SAFE_DELETE(graph);
                break;
            }
            case EXIT:
            {
                bAgain = false;
                break;
            }
        }
    }
    
    SAFE_DELETE(graph);
return 0;
}

Graph* CreateGraph(E_DIRECTION eDirection)
{
    Graph *graph = new Graph(eDirection);
    return graph;
}

int toInt(E_OPERATION e_operation)
{
    return static_cast<E_OPERATION>(e_operation);
}

E_OPERATION Menu()
{
    int choice = -1;
    bool bAgain = true;
    
    while(bAgain)
    {
        cout << "Enter your Choice : \n";
        cout << toInt(CREATE_UNI)   << "    To Create UNI_DIRECTIONAL new graph.\n";
        cout << toInt(CREATE_BI)    << "    To Create BI_DIRECTIONAL new graph.\n";
        cout << toInt(A_VERTEX)     << "    To Add a Vertex.\n";
        cout << toInt(A_EDGE)       << "    To Add an Edge.\n";
        cout << toInt(S_VERTEX)     << "    To Search a Vertex.\n";
        cout << toInt(S_EDGE)       << "    To Search an Edge.\n";
        cout << toInt(R_VERTEX)     << "    To remove a Vertex.\n";
        cout << toInt(R_EDGE)       << "    To remove an Edge.\n";
        cout << toInt(CLEAR)        << "    To Clear whole graph.\n";
        cout << toInt(EXIT)         << "    To Exit.\n";
            
        choice = ReadInput<int>();
    
        if(choice >= 0 && choice <= toInt(MAX))
        {
            bAgain = false;
        }
        else
        {
            cout << "Please enter correct choice.\n";
        }
    }
    
    return static_cast<E_OPERATION>(choice);
}
