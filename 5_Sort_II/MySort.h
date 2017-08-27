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
	void Merge(Item* arr1, int left, int mid, int right); //declare the Merge method, which is the base function to sort two sorted array
	void MergeSort(Item* arr2, int left, int right); //declare the mergesort method
	void MergeSort(); 
	int partition(Item* arr3, int left, int right, int pivotIndex);
	void partition(int pivotIndex);
	void quicksort(Item* arr4, int left, int right);
	void quicksort();
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

void MySort::Merge(Item* arr1, int left, int mid, int right)
{
	int i, j, k;
	int n1 = mid - left +1;
	int n2 = right - mid;

	//create two subarrays, to hold arr[left....mif] and arr[mid...right]
	Item* subLeft = new Item[n1];
	Item* subRight = new Item[n2];

	for (i=0; i<n1; i++)
	{
		subLeft[i] = arr1[left + i];
	}

	for (j=0; j<n2; j++)
	{
		subRight[j] = arr1[mid + 1 + j];
	}

	// merge the two subarrays to one array
	i=0; j=0; k=left; //reset the three index numbers

	while (i < n1 && j < n2)
    {
        if (subLeft[i].Value <= subRight[j].Value)
        {
            arr1[k] = subLeft[i];
            i++;
        }
        else
        {
            arr1[k] = subRight[j];
            j++;
        }
        k++;
    }


	// after the while loop, there might be some items that have not been added to the new array, for example, 
	// if all the left items are smaller than the right ones, then none of the right ones is in the new array
	// we need to take care of these unsorted ones

	while (i < n1)
    {
        arr1[k] = subLeft[i];
        i++;
        k++;
    }

	while (j < n2)
    {
        arr1[k] = subRight[j];
        j++;
        k++;
    }

}


void MySort::MergeSort(Item* arr2, int left, int right)
{

	if(left < right)
	{
		int mid = (left + right)/2;

		MergeSort(arr2, left, mid); //sort the left part recursively
		MergeSort(arr2, mid+1, right); //sort the right part

		Merge(arr2, left, mid, right);
	}

}

void MySort::MergeSort()
{
	Item* newArr = copy();
	int left = 0;
	int right = arr_len - 1; // note here the right is arr_len-1, not arr_len

	MergeSort(newArr, left, right);

	display(newArr);
	delete[] newArr;
}


int MySort::partition(Item* arr3, int left, int right, int pivotIndex)
{
	int pivot = arr3[pivotIndex].Value;
	swap(arr3[pivotIndex], arr3[right]);

	int i = left - 1;
	for (int j=left; j<right; j++)
	{
		if (arr3[j].Value <= pivot)
		{
			i++;
			swap(arr3[i], arr3[j]);
		}
	}
	swap(arr3[i+1], arr3[right]);
	return (i+1);
}


void MySort::partition(int pivotIndex)
{
	Item* newArr = copy();
	int left = 0;
	int right = arr_len - 1; // note here the right is arr_len-1, not arr_len

	partition(newArr, left, right, pivotIndex);

	display(newArr);
	delete[] newArr;
}

void MySort::quicksort(Item* arr4, int left, int right)
{
	if (left < right)
	{
		int pivot;
		int mid = (right+left)/2;
		if (arr4[left].Value <= arr4[mid].Value <=arr4[right].Value || arr4[left].Value >= arr4[mid].Value >=arr4[right].Value)
		{ 
			pivot = mid;
		}
		else if (arr4[mid].Value <= arr4[left].Value <=arr4[right].Value || arr4[mid].Value >= arr4[left].Value >=arr4[right].Value)
		{
			pivot = left;
		}
		else
		{
			pivot = right;
		}
		// set the pivot to the median value 

		int pivotNew = partition(arr4, left, right, pivot);
		quicksort(arr4, left, pivotNew-1);
		quicksort(arr4, pivotNew+1, right);
	}

}

void MySort::quicksort()
{
	Item* newArr = copy();
	int left = 0;
	int right = arr_len - 1; // note here the right is arr_len-1, not arr_len

	quicksort(newArr, left, right);

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
