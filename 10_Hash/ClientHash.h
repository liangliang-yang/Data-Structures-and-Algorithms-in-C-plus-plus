// ClientHash.h
// HW_10
// Created by Liangliang Yang on 07/24/2016

#ifndef CLIENTHASH_H
#define CLIENTHASH_H
#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include "Client.h"


using namespace std;

class ClientHash
{
private:

	unordered_map<string, Client> clientTable;

public:

	ClientHash() {};
	~ClientHash() {};

	void add_client(string& client_name, string& client_address)
	{
		if(clientTable.count(client_name) == 1)
		{
			clientTable[client_name].addNum();
			cout << "client already exists" << endl;
		}
		else
		{
			clientTable[client_name] = Client(client_name, client_address, 0);
			cout << "client " << client_name << " added" << endl;
		}
	}


	void client_makes_purchase(string& client_name)
	{
		if(clientTable.count(client_name) == 0)
		{
			cout << "client not found" << endl;
		}
		else
		{
			clientTable[client_name].addNum();
			cout << "client " << client_name << " has made " << clientTable[client_name].getNumber() << " purchases" << endl;
		}
	}


	void remove_client(string& client_name)
	{
		if(clientTable.count(client_name) == 0)
		{
			cout << "client not found" << endl;
		}
		else
		{
			clientTable.erase(client_name);
			cout << "client " << client_name << " was removed" << endl;
		}
	}

	void get_client_address(string& client_name)
	{
		if(clientTable.count(client_name) == 0)
		{
			cout << "client not found" << endl;
		}
		else
		{
			cout << clientTable[client_name].getAddress() << endl;
		}

	}



};


#endif