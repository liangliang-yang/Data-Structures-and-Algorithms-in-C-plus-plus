// main.cpp
// HW_2
// Created by Liangliang Yang on 06/14/2016

#include "MyString.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	cout<< "Liangliang Yang, 11352247\n";

	MyString test_str;

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
            test_str.set(s);
        }

		//if(0==line.compare(0,7,"reverse"))
       // {
            //int start = (int)line.find('(') + 1;
            //int end = (int)line.find(')');
            //string word=line.substr(start ,end - start);
            //char* s=new char[word.length()+1];
            //strcpy(s, word.c_str());
            //test_str.reverse();
			//test_str.Write(cout);
			//cout << endl;

       // }

		else if(0==line.compare(0,14,"bad_char_table"))
        {
			int* table = test_str.bad_char_table();
			for (int i=0; i<256; i++)
			{
				cout << table[i] << ',';
			}

			cout << endl;
		}

		// *** test of freqTable()
		//else if(0==line.compare(0,4,"freq"))
        //{
		//	int* table = test_str.freqTable();
		//	for (int i=0; i<256; i++)
		//	{
		//		cout << table[i] << ',';
		//	}
		//}

		// *** test of isAnagram()
		//else if(0==line.compare(0,3,"isA"))
        //{
		//	bool isA;
		//	isA = test_str.isAnagram("Heiiq","iiHe");
		//	cout << isA <<endl;
		//}


        else if(0==line.compare(0,6,"substr"))
        {
            int start = 7;
            int end = (int)line.find(')');
            int comma = (int)line.find(',');
            int index;
            int length;
            index=stoi(line.substr(start ,comma - start));
            length=stoi(line.substr(comma + 1, end));

            MyString newString = test_str.Substring(index,length);
            newString.Write(cout);
			cout << endl;
        }


        else if(0==line.compare(0,7,"indexof"))
        {
            int start = 8;
            int end = (int)line.find(')');
            int comma = (int)line.find(',');
            
            string word=line.substr(start, comma - start);
            char* s=new char[word.length()+1];
            strcpy(s,word.c_str());
            int index=stoi(line.substr(comma + 1, end - comma));
            cout << test_str.indexof(s,index) <<endl;

        }

		else if(0==line.compare(0,5,"split"))
		{
			char c=line[6];
			vector<MyString> output;
			test_str.Split(c, output);
			for (int i = 0; i < output.size(); i++)
			{
				output[i].Write(cout);
				cout << ',';
			}
			cout << endl;

		}
        

		  else if(0==line.compare(0,8,"anagrams"))
		  {
			  // create a MyString with the word of candidates
			  MyString m_word;  
			  int start = (int)line.find('(') + 1;
			  int end = (int)line.find(')');
			  string word=line.substr(start, end - start);
              char* s=new char[word.length()+1];
              strcpy(s, word.c_str());
              m_word.set(s);


			  // use GetAnagrams to find and show the answer
			  vector<MyString> candidates;
			  vector<MyString> output;
			  m_word.Split(',', candidates);
			  test_str.GetAnagrams(candidates, output);
			  for (int i = 0; i < output.size(); i++)
			  {
				output[i].Write(cout);
				cout << ",";
				//cout << endl;
			  }
			  cout << endl;

		  }

        else if(0==line.compare(0,4,"quit"))
        {
            break;
        }
        else
        {
            cout<<"unknown command:"<<line<<"\n";
        }
    }
    
    cout<<"Done\n";
    
    return 0;

	
}
