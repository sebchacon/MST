#include <iostream>
#include <vector>

using namespace std;

struct Link {

public:
   int v1, v2;
   float w;

};

ostream& operator<<(ostream&, const Link&);

class MyGraph {

public:
   MyGraph();
   MyGraph(const MyGraph&);
   MyGraph(int n);

   bool addEdge(int a, int b, float w);
   void output(ostream& os);
   pair<vector<Link>, float > MST();
   pair<vector<Link>, vector<int> > Prog2(vector<float> satcost, vector<Link> linkcost, int& sat_conn);
private:
    vector<float> vertices;
    vector<Link> edges;
    int startConn;
};


