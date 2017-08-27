// main.cpp
// HW_1
// Created by Liangliang Yang on 06/11/2016

#include "Stack.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    std::cout<< "Liangliang Yang, 11352247\n";
    Stack myStack;
    while(true)
    {
        string line;
        getline(cin, line);
        
        if(line.compare(0,4,"push")==0)
        {
            int value;
            value=stoi(line.substr(5));
            myStack.Push(value);
        }
        else if(line.compare(0,3,"pop")==0)
        {
            myStack.Pop();
        }
        else if(line.compare(0,7,"reverse")==0)
        {
            myStack.Reverse();
        }
        else if(line.compare(0,7,"display")==0)
        {
            myStack.Display(cout);
        }

        else if(line.compare(0,7,"isempty")==0)
        {
            printf("%s\n", myStack.IsEmpty()? "true": "false");
        }
        else if(line.compare(0,4,"quit")==0)
        {
            break;
        }
        else
        {
        std::cout<<"unknown command!"<<line<<"\n";
        }
    }

     std::cout<<"Done\n";
}
