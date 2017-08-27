// MySort.h
// HW_4
// Created by Liangliang Yang on 06/24/2016

#ifndef MYSORT_H
#define MYSORT_H
#define _CRT_SECURE_NO_WARNINGS 



#include <string.h>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include "MyString.h"

using namespace std;

struct Item
{
    int Value;
    int Index;
};


class MySort
{
private:
	Item* arr;
	int arr_len;


public:
    MySort(); // constructor
    Item* set(char* s);
	int getLength(Item* arr); //get the length or size of a array 
	Item* copy(); // a copy function, in order to duplicate the current array
	void swap(Item& a,Item& b); // helper function, swap two Items
    void InsertSort(); // declare the insertsort method
	void ShellSort(vector<int> gap); //declare the shellsort method
    ~MySort(); //destructor

	//display functions
	void display(ostream& stream); //display for the class
	void display(Item* arr); //display for an array
};


MySort::MySort()
{
    arr_len=0;
    arr=NULL;
}

MySort::~MySort()
{
    if (arr != NULL) delete[] arr;
    arr_len = 0;
}


Item* MySort::copy()
{
	Item* newArr = new Item[arr_len];
	int i=0;
	for (i=0; i<arr_len; i++)
	{
		newArr[i] = arr[i];
	}
	return newArr;
}

Item* MySort::set(char* s)
{
	MyString m_str = MyString(s);
	vector<MyString> v1;
	m_str.Split(';', v1);
	arr_len = v1.size();
	arr = new Item[arr_len];

	for (int i = 0; i < v1.size(); i++)
	{
		vector<MyString> v2;
		v1[i].Split(',',v2);
		char* str0 =  v2[0].getValue();
		char* str1 =  v2[1].getValue();
		arr[i].Value = stoi(string(str0)); //here stoi can not apply directly to MyString type, char* will be ok
		arr[i].Index = stoi(string(str1));
		v2.clear();
	}
	return arr;
}

void MySort::swap(Item& a,Item& b)  
{
	Item temp;
    temp=a;
    a=b;
    b=temp;
}

void MySort::InsertSort()  // actually it is gap==1, so in shellsort, when change 1 to gap[k], it will be similar
{
	Item* newArr = copy(); // make a copy of the current array

	for (int i=0; i<arr_len; i++)
	{
		int j=i;
		while (j>0 && newArr[j].Value < newArr[j-1].Value)
		{
			swap(newArr[j], newArr[j-1]);
			j--;
		}
	}

	display(newArr);
	delete[] newArr;

}


void MySort::ShellSort(vector<int> gap)  // The easy way to remember this algorithm is to compare it with insertsort, as insertsort is shell(1)
{
	Item* newArr = copy();
	for (int k=0; k<gap.size(); k++)
	{
		for (int i=gap[k]-1; i<arr_len; i++)
		{
			int j=i;
			while(j>=gap[k] && newArr[j].Value < newArr[j-gap[k]].Value) // here j>=gap[k]  instead of j>0, in order to make sure that the j-gap[k] >= 0
			{
				swap(newArr[j], newArr[j-gap[k]]);
				j=j-gap[k];
			}
		}
	}

	display(newArr);
	delete[] newArr;
}




void MySort::display(ostream& stream)
{
    
    for(int i=0;i<arr_len;i++)
    {
        stream<<arr[i].Value;
		stream << ',';
		stream<<arr[i].Index;
        stream << ';';
    }
	stream << '\n';
}

void MySort::display(Item* arr)
{
	for(int i=0;i<arr_len;i++)
    {
        cout<<arr[i].Value;
		cout << ',';
		cout<<arr[i].Index;
        cout << ';';
    }
	cout << endl;

}







































#endif
