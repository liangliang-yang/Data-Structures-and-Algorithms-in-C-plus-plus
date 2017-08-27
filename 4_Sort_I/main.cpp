// main.cpp
// HW_4
// Created by Liangliang Yang on 06/24/2016

#include "MyString.h"
#include "MySort.h"
#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

int main()
{
	cout<< "Liangliang Yang, 11352247\n";

	MySort test;

    while(true)
    {
        string line;
        getline(cin, line);
        
        //process the command here
        
        if(0==line.compare(0,3,"set"))
        {
            int start = (int)line.find('(') + 1;
            int end = (int)line.find(')');
            string word=line.substr(start ,end - start);
            char* s=new char[word.length()+1];
            strcpy(s, word.c_str());
            test.set(s);

        }

		else if(0==line.compare(0,6,"insert"))
        {

			test.InsertSort();

        }

		else if(0==line.compare(0,5,"shell"))
        {
            int start = (int)line.find('(') + 1;
            int end = (int)line.find(')');
            string word=line.substr(start ,end - start);
            char* s=new char[word.length()+1];
            strcpy(s, word.c_str());

			vector<MyString> gap_str;
			vector<int> gap;
			MyString(s).Split(',',gap_str);

			int i=0;
			for (i=0; i<gap_str.size(); i++)
			{

				gap.push_back(stoi(string(gap_str[i].getValue())));
			}

			test.ShellSort(gap);

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