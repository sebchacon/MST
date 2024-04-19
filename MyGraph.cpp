#include <iostream>
#include "MyGraph.h"


/*
 * Name: Sebastian Chacon
 *
 * Step 1: read in satcost and find lowest number for starting node
 * Step 2: MST with starting node at satcost min
 * Step 3: Prims Algorithm
 * Step 4: Check in prog2
 * Step 5: return
 *
 */

ostream& operator<<(ostream& os, const Link& l) //print out Links by vertices 1, then 2, then its weight
{
   os << l.v1 << " " << l.v2 << " " << l.w;
   return os;
}

MyGraph::MyGraph()
{
    vector<int> vertices;
    vector<Link> edges;
} //constructor

MyGraph::MyGraph(int n)
{
    vector<int> vertices;
    vector<Link> edges;

    for(int i = 0; i < n; ++i)
    {
        vertices.push_back(i + 1);
    }
} //constructor passing in number of vertices for graph

MyGraph::MyGraph(const MyGraph&grap)
{
    vertices = grap.vertices;
    edges = grap.edges;
} //constructor by passing in itself

bool MyGraph::addEdge(int a, int b, float w)
{

    bool x = false;
    bool z = false;

    for(int i = 0; i < vertices.size(); ++i)
    {
        if(a == vertices[i])
        {
            x = true;
        }
        else if(b == vertices[i])
        {
            b = true;
        }
        if(a && b)
        {
            break;
        }
    }


    if(!(a || b))
    {
        return false;
    }

   return true;
} //given vertices a,b and its weight w. Add edge to Link structure

void MyGraph::output(ostream& os)
{
    os<< "Number of vertices: " << vertices.size() << std::endl;
    for(int i = 0; i < edges.size(); ++i)
    {
        if(edges[i].v1 > edges[i].v2)
        {
            os<< edges[i].v2 << " " << edges[i].v1 << " " << edges[i].w << std::endl;
        }
        else
        {
            os<< edges[i].v1 << " " << edges[i].v2 << " " << edges[i].w << std::endl;
        }
    }
} //print out number of vertices then the edges connecting them

pair<vector<Link>,float>  MyGraph::MST()
{
    /*
     * For this project I used Prims algorithm to implement my spanning tree
     * I used two vectors, res1 contains the links that are used to create our satellite connection and usedMST to track what vertices have been visited.
    */


    vector<Link> res1; //initialize vector to store our final tree
    vector<bool> usedMST(vertices.size(), false); //initialize our vector to check if visited, all are false since none have been visited
    usedMST[startConn] = true; //our beginning connection will be true since this is what we are given to start
    float finalWeight = 0.0; //weight starts at 0 and increments as we create our tree

    while(res1.size() < vertices.size() - 1) //Prims algorithm loops through k - 1 elements
    {
        float min = numeric_limits<float>::max(); //set our minimum high so it will catch anything lower to find min
        int parent = -1; //start at impossible natural value for an edge and change if valid, if not we will break later

        int v1; //vertices 1
        int v2; //vertices 2
        for(int i = 0; i < edges.size(); ++i) //check our edges for valid connection between the two vertices/homes
        {
            v1 = edges[i].v1; //set v1 and v2 to two vertices this edge touches
            v2 = edges[i].v2;
            float weight = edges[i].w; //weight of current edge

            if( (usedMST[v1] && !usedMST[v2])|| (usedMST[v2] && !usedMST[v1])) //check if either are unvisited
            {
                if(weight < min) //if one is unvisited, see if weight is smaller than our min, first iteration will always be
                {
                    min = weight; //set min to new weight
                    parent = i; //set our parent/key value to i
                }
            }
        }
        if(parent == -1) //if connection was not made, break
        {
            break;
        }

        res1.push_back(edges[parent]); //push back our link to res1
        finalWeight += min; //add weight to total

        int newVertex; //set both vertices to be visited now
        if (usedMST[edges[parent].v1])
            newVertex = edges[parent].v2;
        else
            newVertex = edges[parent].v1;
        usedMST[newVertex] = true;

    }

    return make_pair(res1, finalWeight); //send back final link set and our total weight
}


pair<vector<Link> , vector<int> > MyGraph::Prog2(vector<float> satcost, vector<Link> linkcost, int& sat_conn) //function handling referenced read in data and calling our MST
{
    vertices = satcost; //set private variable vertices to data satcost from txt file
    edges = linkcost; //set private variable edges to data linkcost from txt file
    int minWeight = vertices[1]; //test file pushes 0 at beginning so skip 0 and start at 1
    for(int i = 1; i < vertices.size(); ++i) //find cheapest vertices, test file pushes 0.0 so skip 0 or it will always start there
    {
        if(vertices[i] < minWeight) //if smaller, set equal and check for smaller
        {
            startConn = i; //starting connection at this index
            minWeight = vertices[i]; //new minimum cost
        }
    }
    sat_conn = startConn; //sat_conn is passed by reference so pass back our new sat_conn connection

    auto answers = MST(); //call MST and set return data to pair, auto is dynamic therefore builds/runs faster

    vector<Link> res1 = answers.first; //res 1 is our final link connection
    float finalWeight = answers.second; //finalweight is our total weight from the connections

    vector<int> path; //path from satellite to house 1
    path.push_back(0); //always start at 0
    path.push_back(sat_conn); //satellite connection will be next of course

    int begin = 1; //house 1
    int current = sat_conn; //where we currently our in our path, start at satellite connection
    vector<bool> usedVertex(satcost.size(), false); //vector showing what has or has not been visited

    while(current != begin) //while still on path
    {
        bool tf = false;
        usedVertex[current] = true; //vertex currently at is true
        for(const auto& edge : res1) //loop through our edges
        {
            if(edge.v1 == current && !usedVertex[edge.v2]) //if we are at vertex 1 in this edge and the other is unused
            {
                path.push_back(edge.v2); //push this vertex to our path
                current = edge.v2; //we are now at this vertex
                tf = true; //we made a connection
                break; //next iteration
            }
            else if(edge.v2 == current && !usedVertex[edge.v1]) //same case as above but for vice verse
            {
                path.push_back(edge.v1);
                current = edge.v1;
                tf = true;
                break;
            }
        }

        if(!tf) //if no connection, break
            break;
    }

    return make_pair(res1, path); //return our Links made and the path from 0, satellite connection, and to house 1
}

