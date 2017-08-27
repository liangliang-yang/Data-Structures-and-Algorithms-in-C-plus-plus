// MyHeap.h
// HW_8
// Created by Liangliang Yang on 07/13/2016

#ifndef MYHEAP_H
#define MYHEAP_H
#define _CRT_SECURE_NO_WARNINGS 

#include <string.h>
#include <cstring>
#include <string>
#include <vector>
#include<iostream>
using namespace std;

template <typename T>
class MyHeap
{

private:
	int K; // K-ary Heap
	vector<T> heap;  // process as a vector

public:


	MyHeap()
	{
		K = 2; //defalut as binary
	}

	MyHeap(int k)
	{
		K = k;
	}



	void reset(int k)
	{
		heap.clear();
		K = k;
	}



	~MyHeap()
	{
		heap.clear();
	}

	

	int getSize()
	{
		return heap.size();
	}

	bool IsEmpty()
	{
		return heap.empty();
	}


	int parent(int i)
	{
		if (i == 0)
		{
			return -1;
		}
		else
		{
			return (i-1)/K;
		}
	}

	int child(int i, int j) // get the jth child of ith node
	{
		return (K*i + j);
	}

	bool HasChild(int i) // return true if the node i has 1 or more children
	{
		return (int(heap.size()) > (K*i + 1));
	}

	int childNum(int i) // return the number of child for node i
	{
		int num = int(heap.size()) - (K*i + 1);
		return num;
	}

	int childMax(int i) // get the index of max child for a node
	{
		int maxIndex = K*i + 1; //set defalut as the first one
		int num = childNum(i);
		for (int j=1; j<=num; j++)
		{
			if(heap[K*i + j] > heap[maxIndex])
			{
				maxIndex = K*i +j;
			}
		}
		return maxIndex;
	}

	void swap(T& a, T& b)
	{
		T temp;
		temp = a;
		a = b;
		b = temp;
	}

	void add(const T& newItem)
	{
		int nodeIndex = heap.size();
		heap.push_back(newItem);
		siftup(nodeIndex);
	}

	void siftup(int nodeIndex)
	{
		int parentIndex = parent(nodeIndex);
		while (nodeIndex > 0 && heap[nodeIndex] > heap[parentIndex])
		{
			swap(heap[nodeIndex], heap[parentIndex]);
			nodeIndex = parentIndex;
			parentIndex = parent(nodeIndex);
		}

	}

	void siftdown(int nodeIndex)
	{
		
		while (HasChild(nodeIndex))
		{
			int maxchildIndex = childMax(nodeIndex);
			if(heap[maxchildIndex] > heap[nodeIndex])
			{
				swap(heap[nodeIndex], heap[maxchildIndex]);
				nodeIndex = maxchildIndex;
			}
			else
			{
				return;
			}
		}
	}

	void removeMax()
	{
		if (IsEmpty())
		{
			return;
		}
		else
		{
			int size = heap.size();
			T max = heap[0];
			swap(heap[0], heap[size-1]); // swap root and last value
			heap.pop_back();
			siftdown(0);  // siftdown root value
			cout << max << endl;
		}

	}



	void displayArray()
	{
		for (unsigned i=0; i<heap.size(); i++)
		{
			cout << heap[i] << ",";
		}
		cout << endl;
	}






};

#endif
