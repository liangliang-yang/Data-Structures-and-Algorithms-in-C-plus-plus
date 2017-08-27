#include "MyHeap.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int main()
{
	cout<< "Liangliang Yang, 11352247\n";
	MyHeap<int> testMyHeap;

	

	while(true)
    	{
        string line;
        getline(cin, line);

		if(0==line.compare(0,5,"reset"))
        {
            int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
			int k = stoi(line.substr(start, end - start));
			
			testMyHeap.reset(k);
		}
  
		else if(0==line.compare(0,3,"add"))
		{
			int start = (int)line.find('(') + 1;
			int end = (int)line.find(')') ;
			int value = stoi(line.substr(start, end - start));
			testMyHeap.add(value);
		}

		else if(0==line.compare(0,6,"remove"))
		{
			testMyHeap.removeMax();
		}

		else if (0==line.compare(0,7,"display"))
		{
			testMyHeap.displayArray();
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
