#include <iostream>
#include <fstream>
#include <vector>
#include "MyGraph.h"

int main()
{
    MyGraph graph;

   ifstream ifile("test2_1.txt");
   int n;
   vector<float> satcost;

   ifile >> n;

   satcost.push_back(0.0);
   for (int i = 0; i < n; i++)
	{
	   float q;
           ifile >> q;
	   satcost.push_back(q);
	}

   int e;
   vector<Link> l;
   ifile >> e;
   int sat_conn;
   for (int i = 0; i < e; i++)
	{
	   Link s;
	   ifile >> s.v1 >> s.v2 >> s.w;
	   l.push_back(s);
	}
   cout << "Total # of houses " << n << endl;
   cout << "Links : ";
   for (int i = 0; i < l.size(); i++)
	cout << l[i] << " | ";
   cout << endl;
 
   pair<vector<Link>, vector<int> > res = graph.Prog2(satcost, l, sat_conn);

   cout << "\n----------\n\n";
   cout << "Satellite connected to house " << sat_conn << endl;
   cout << "Links : "; 
   for (int i = 0; i < res.first.size(); i++)
	{
	   cout << res.first[i] << " " << " | ";;
	}

//   for (int i = 0; i < res.second.size(); i++)
//	{
//	   cout << res.second[i] << " ";
//	}
   cout << "\n";
   
   cout << "Path to house 1 : ";
   for (int i =0; i < res.second.size(); i++)
	{
	   cout << res.second[i] << " ";
	}
   cout << endl;

   return 0;
}
