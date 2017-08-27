// main.cpp
// HW_9
// Created by Liangliang Yang on 07/18/2016

#include "WeightedGraph.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int main()
{
	cout<< "Liangliang Yang, 11352247\n";

	WeightedGraph MyGraph;
		
	//string str1 = "A,B,C,D,E,F,G";
	//string str2 = "A,B,6;A,C,12;A,D,22;B,D,7;C,D,8;E,F,100;A,E,200";

	//MyGraph.set(str1,str2);

	//string A = "A";
	//string B = "B";
	//string C = "C";
	//string D = "D";
	//string E = "E";
	//string F = "F";
	//string G = "G";
	//string H = "H";

 //	cout << "degree is: " << MyGraph.GetDegree(H) << endl;

	//MyGraph.Shortest_Path(B,C);

 //	cout << "path length is: " << MyGraph.Shortest_Path(B,C).size() << endl;;

	//MyGraph.display(MyGraph.Shortest_Path(B,C));


	while(true)
    	{
        string line;
        getline(cin, line);

	if(0==line.compare(0,2,"//"))
	{
		continue;
	}
		
        else if(0==line.compare(0,3,"set"))
        {
            int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
			int pipe = (int)line.find('|');
            string strNode = line.substr(start ,pipe - start);
            string strEdge = line.substr(pipe + 1, end - pipe - 1);
			
			MyGraph.set(strNode, strEdge);
        }

	else if(0==line.compare(0,6,"degree"))
	{
	    int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
			
            string nodeName = line.substr(start ,end - start);
            cout << MyGraph.GetDegree(nodeName) << endl;
	}

	else if(0==line.compare(0,20,"shortest_path_length"))
        {
	    int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
	    int comma = (int)line.find(',');
	    string startnodeName = line.substr(start ,comma - start);
            string endnodeName = line.substr(comma + 1, end - comma - 1);
			
	    if (MyGraph.Shortest_Path(startnodeName,endnodeName).empty())
	    {
		cout << "no path" << endl;
	    }
	    else
	    {
		cout << MyGraph.pathLength(MyGraph.Shortest_Path(startnodeName,endnodeName)) << endl;
	    }

	}

	else if(0==line.compare(0,13,"shortest_path"))
        {
	    int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
	    int comma = (int)line.find(',');
	    string startnodeName = line.substr(start ,comma - start);
            string endnodeName = line.substr(comma + 1, end - comma - 1);

	    MyGraph.display(MyGraph.Shortest_Path(startnodeName,endnodeName));

	}




	else if(0==line.compare(0,4,"quit"))
        {
            break;
        }

        else
        {
            std::cout<<"unknown command:"<<line<<"\n";
        }



	}



	cout<<"Done\n";

	return 0;

}
