// Client.h
// HW_10
// Created by Liangliang Yang on 07/24/2016

#ifndef CLIENT_H
#define CLIENT_H
#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>


using namespace std;


class Client
{

private:
	string Name;
	string Address;
	int NumP;   // number of purchase

public:
	Client() {};
	Client(string &name, string &address, int num)
	{
		Name = name;
		Address = address;
		NumP = num;
	}
	~Client() {};

	string getAddress()  // get the address
	{
		return Address;
	}

	int getNumber() // get the number of purchase
	{
		return NumP;
	}

	void addNum()  // increase the number of purchase by 1
	{
		NumP += 1;
	}






















};


#endif