
#include "My234tree.h"
#include "Student.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int main()
{
	cout<< "Liangliang Yang, 11352247\n";

	My234tree<Student> test234tree;

	while(true)
    	{
        string line;
        getline(cin, line);

		
        if(0==line.compare(0,3,"add"))
        {
            int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
	    int comma = (int)line.find(',');
            string name = line.substr(start ,comma - start);
            int id = stoi(line.substr(comma + 1, end - comma - 1));
			Student stu = Student(name,id);
			test234tree.Add(stu);

        }

	else if (0==line.compare(0,17,"countValuesInNode"))
	{
		int start = (int)line.find('(') + 1;
            	int end = (int)line.find(')') ;
		int key = stoi(line.substr(start, end - start));
		cout << test234tree.countValuesInNode(key) << endl;
	}

	else if (0==line.compare(0,7,"getName"))
	{
		int start = (int)line.find('(') + 1;
            	int end = (int)line.find(')') ;
		int key = stoi(line.substr(start, end - start));
		test234tree.getName(key);
	}

	else if (0==line.compare(0,8,"getLevel"))
	{
		int start = (int)line.find('(') + 1;
            	int end = (int)line.find(')') ;
		int key = stoi(line.substr(start, end - start));
		cout << test234tree.getLevel(key) << endl;
	}

	else if (0==line.compare(0,11,"countLevels"))
	{
		cout << test234tree.countLevels() << endl;
	}

	else if (0==line.compare(0,7,"display"))
	{
		test234tree.DisplayTree();
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
