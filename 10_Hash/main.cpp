// main.cpp
// HW_10
// Created by Liangliang Yang on 07/24/2016

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include "Client.h"
#include "ClientHash.h"


using namespace std;


//void add_client(string& client_name, string& client_address)
//{
//	if ()
//	{
//
//	}
//
//}

int main()
{
	cout<< "Liangliang Yang, 11352247\n";

	ClientHash MyClient;


	
	while(true)
    {
        string line;
        getline(cin, line);

		if(0==line.compare(0,2,"//"))
		{
			continue;
		}
		
        else if(0==line.compare(0,10,"add_client"))
        {
            int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
			int comma = (int)line.find(',');
            string client_name = line.substr(start ,comma - start);
            string client_address = line.substr(comma + 1, end - comma - 1);
			
			MyClient.add_client(client_name, client_address);
        }

		else if(0==line.compare(0,21,"client_makes_purchase"))
		{
			int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
			string client_name = line.substr(start ,end-start);
			MyClient.client_makes_purchase(client_name);
		}

		else if(0==line.compare(0,13,"remove_client"))
		{
			int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
			string client_name = line.substr(start ,end-start);
			MyClient.remove_client(client_name);
		}

		else if(0==line.compare(0,18,"get_client_address"))
		{
			int start = (int)line.find('(') + 1;
            int end = (int)line.find(')') ;
			string client_name = line.substr(start ,end-start);
			MyClient.get_client_address(client_name);
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


