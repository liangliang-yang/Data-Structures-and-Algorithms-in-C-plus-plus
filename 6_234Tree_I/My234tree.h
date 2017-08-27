// My234tree.h
// HW_6
// Created by Liangliang Yang on 07/02/2016

#pragma once

#include "Student.h"
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template <typename T>
class My234tree
{
private:
	struct treeNode
	{
		// declare the three values in the tree node
		T* A;
		T* B;
		T* C;

		// at most four child pointers
		treeNode* L;
		treeNode* M1;
		treeNode* M2;
		treeNode* R;

		// constructor to initialize the node with one value and no child
		treeNode(T* valA)
		{
			//A = valA;
			A = new T(*valA);
			B = C = NULL;
			L = M1 = M2 = R =NULL;
		}



		treeNode(T* valA, treeNode* leftA, treeNode* rightA)
		{
			//A = valA;
			A = new T(*valA);
			//same here
			//L = new treeNode(*leftA);
			//M1 = new treeNode(*rightA);
			L = leftA;
			M1 = rightA;

			B = C = NULL;
			M2 = R =NULL;
		}

		bool IsFull()
		{
			return (A != NULL && B != NULL && C != NULL);
			// return (C != NULL);
		}

		bool IsTwo() // check if the node contains two values
		{
			return (A != NULL && B != NULL && C == NULL);
		}

		bool IsOne() // check if the node contains one values
		{
			return (A != NULL && B == NULL && C == NULL);
		}

		bool IsEmpty() // check if the node is empty
		{
			return (A == NULL && B == NULL && C == NULL);
		}

		bool IsLeaf()
		{
			return (L == NULL && M1 == NULL && M2 == NULL && R == NULL);
			// return (L == NULL);
		}

		void DeleteDate()
		{
			if (A != NULL) {delete A; A = NULL;}
			if (B != NULL) {delete B; B = NULL;}
			if (C != NULL) {delete C; C = NULL;}
		}
	
		bool ContainsKey(int key)
		{
			if (C && C->GetKey() == key) { return true; }
			if (B && B->GetKey() == key) { return true; }
			if (A->GetKey() == key) { return true; }
			return false;
		}

		bool ContainsKey_and_getName(int key)
		{
			if (C && C->GetKey() == key) 
			{
				cout << C->getName() << endl;
				return true; 
			}
			if (B && B->GetKey() == key) 
			{ 
				cout << B->getName() << endl;
				return true; 
			}
			if (A->GetKey() == key) 
			{ 
				cout << A->getName() << endl;
				return true; 
			}
			return false;
		}

		void DisplayNode()
		{
			if(C) 
			{
				A->write();
				B->write();
				C->write();
				cout << endl;
			}
			else if(B)
			{
				A->write();
				B->write();
				cout << endl;
			}
			else
			{
				A->write();
				cout << endl;
			}
		}


		int countValues()
		{
			if (C != NULL) { return 3; }
			else if (B != NULL) { return 2; }
			else if (C != NULL) { return 1; }
			else { return 0; }
		}


	};
	treeNode* m_root;

public:
	My234tree(void)
	{
		m_root = NULL;
	}


	~My234tree(void)
	{
		DeleteTree(m_root);
		m_root = NULL;
	}

	// the DeleteTree() function will use recursive function to delete the whole tree

	void DeleteTree(treeNode* root)
	{
		if (root)
		{
			root -> DeleteDate();
			DeleteTree(root -> L);
			DeleteTree(root -> M1);
			DeleteTree(root -> M2);
			DeleteTree(root -> R);

			delete root;

		}
	}


	bool FindKey(int key)
	{
		bool findit = false;
		treeNode* currentNode = m_root;

		while (findit == false && currentNode != NULL) // while have not find the key till the end of the tree
		{
			if (currentNode->A->GetKey() == key)
			{
				findit = true;
			}

			else if (currentNode->A->GetKey() > key)  // case if key is smaller than A
			{
				currentNode = currentNode->L; 
			}

			else  // case if the key is bigger than A, also contain several cases 
			{
				if (currentNode->B == NULL)
				{
					currentNode = currentNode->M1;
				}
				else  //  case A < key < B
				{
					if (currentNode->B->GetKey() == key)
					{
						findit = true;
					}

					else if (currentNode->B->GetKey() > key)
					{
						currentNode = currentNode->M1;
					}

					else // case key > B
					{
						if (currentNode->C == NULL)
						{
							currentNode = currentNode->M2;
						}
						else // case B < key < C
						{
							if (currentNode->C->GetKey() == key)
							{
								findit = true;
							}

							else if (currentNode->C->GetKey() > key)
							{
								currentNode = currentNode->M2;
							}

							else // case key > D
							{
								currentNode = currentNode->R;
							}
						}
					}
				}
			}
		}

		return findit;
	}


	treeNode* FindParent(treeNode* child)
	{
	
		treeNode* currentNode = m_root;
		int key = child->A->GetKey();

		if (child == currentNode)  // check first if the child is the root of the tree
		{
			return NULL;
		}
		else
		{
			if (child == currentNode->L || child == currentNode->M1 || child == currentNode->M2 || child == currentNode->R) //Parent is parent of child
			{
				return currentNode;
			}
			else
			{
				while (!currentNode->IsLeaf)  // while the node is not leaf
				{
					if (currentNode->A->GetKey() > key)  // case if key is smaller than A
					{
						currentNode = currentNode->L; 
					}
					else  // case if the key is bigger than A, also contain several cases 
					{
						if (currentNode->B == NULL)  // if B is empty
						{
							currentNode = currentNode->M1;
						}
						else 
						{
							if (currentNode->B->GetKey() > key)   // A < key < B
							{
								currentNode = currentNode->M1;
							}
							else // key > B
							{
								if (currentNode->C == NULL)   // if C is empty
								{
									currentNode = currentNode->M2;
								}
								else
								{
									if (currentNode->C->GetKey() > key)   // B < key < C
									{
										currentNode = currentNode->M2;
									}
									else 
									{
										currentNode = currentNode->R;
									}
								}
							}
						}
					}
				}
			}
		}
	
		return currentNode;
	}




	treeNode* FindNode(T& obj)
	{
		T* newObj = new T(obj);
		int key = newObj->GetKey();
		treeNode* currentNode = m_root;
		treeNode* targetNode = NULL;

		while (currentNode)  // do until the node is a leaf
		{
			if (currentNode->C)
			{
				if (currentNode->A->GetKey()==key || currentNode->B->GetKey()==key || currentNode->C->GetKey()==key)
				{
					targetNode = currentNode;
					targetNode->DisplayNode();
					return targetNode;
				}
				else 
				{
					currentNode = Branch(currentNode, newObj);
				}
			}
			else if (currentNode->B)
			{
				if (currentNode->A->GetKey()==key || currentNode->B->GetKey()==key)
				{
					targetNode = currentNode;
					targetNode->DisplayNode();
					return targetNode;
				}
				else 
				{
					currentNode = Branch(currentNode, newObj);
				}
			}

			else
			{
				if (currentNode->A->GetKey()==key)
				{
					targetNode = currentNode;
					targetNode->DisplayNode();
					return targetNode;
				}
				else 
				{
					currentNode = Branch(currentNode, newObj);
				}
			}

		}

		return targetNode;

	}

	void getName(int key)
	{
		treeNode* currentNode = m_root;
		bool findit = false;

		while (currentNode)
		{
			if (currentNode->ContainsKey_and_getName(key))
			{
				findit = true;
				return;
			}
			else 
			{
				currentNode = Branch(currentNode, key);
			}
		}

		if (findit == false)
		{
			cout << "(student not found)" << endl;
		}
	}


	//void getName(int key)
	//{
	//	treeNode* currentNode = m_root;
	//	bool findit = false;

	//	if (!FindKey(key))
	//	{
	//		cout << "(student not found)" << endl;
	//	}
	//	else
	//	{
	//		while (currentNode)  // do until the node is a leaf
	//		{
	//			if (currentNode->C)
	//			{
	//				if (currentNode->A->GetKey()==key) 
	//				{ 
	//					cout << currentNode->A->getName() << endl; 
	//					findit = true;
	//					return;
	//				}
	//				else if (currentNode->B->GetKey()==key)
	//				{ 
	//					cout << currentNode->B->getName() << endl; 
	//					findit = true;
	//					return;
	//				}

	//				else if (currentNode->C->GetKey()==key)
	//				{ 
	//					cout << currentNode->C->getName() << endl; 
	//					findit = true;
	//					return;
	//				}
	//				else
	//				{
	//					while (currentNode->L)
	//					{
	//						currentNode = Branch(currentNode, key);
	//					}
	//				}
	//			}
	//			else if (currentNode->B)
	//			{
	//				if (currentNode->A->GetKey()==key) 
	//				{ 
	//					cout << currentNode->A->getName() << endl; 
	//					findit = true;
	//					return;
	//				}
	//				else if (currentNode->B->GetKey()==key)
	//				{ 
	//					cout << currentNode->B->getName() << endl; 
	//					findit = true;
	//					return;
	//				}
	//				else 
	//				{
	//					while (currentNode->L)
	//					{
	//						currentNode = Branch(currentNode, key);
	//					}
	//				}
	//			}

	//			else
	//			{
	//				if (currentNode->A->GetKey()==key) 
	//				{ 
	//					cout << currentNode->A->getName() << endl; 
	//					findit = true;
	//					return;
	//				}
	//				else 
	//				{
	//					while (currentNode->L)
	//					{
	//						currentNode = Branch(currentNode, key);
	//					}
	//				}
	//			}

	//		}
	//	}
	//
	//}

	int getLevel(int key)
	{
		int level = -1;
		int count = -1;
		treeNode* currentNode = m_root;

		while (currentNode)  
		{
			if (currentNode->C)
			{
				if (currentNode->A->GetKey()==key || currentNode->B->GetKey()==key || currentNode->C->GetKey()==key)
				{
					level = count + 1;
					return level;
				}
				else 
				{
					currentNode = Branch(currentNode, key);
					count = count + 1;
				}
			}
			else if (currentNode->B)
			{
				if (currentNode->A->GetKey()==key || currentNode->B->GetKey()==key)
				{
					level = count + 1;
					return level;
				}
				else 
				{
					currentNode = Branch(currentNode, key);
					count = count + 1;
				}
			}

			else
			{
				if (currentNode->A->GetKey()==key)
				{
					level = count + 1;
					return level;
				}
				else 
				{
					currentNode = Branch(currentNode, key);
					count = count + 1;
				}
			}

		}

		return level;

	}


	int countValuesInNode(int key)
	{
		int count = -1;
		treeNode* currentNode = m_root;

		while (currentNode)  // do until the node is a leaf
		{
			if (currentNode->C)
			{
				if (currentNode->A->GetKey()==key || currentNode->B->GetKey()==key || currentNode->C->GetKey()==key)
				{
					count = 3;
					return count;
				}
				else 
				{
					currentNode = Branch(currentNode, key);
				}
			}
			else if (currentNode->B)
			{
				if (currentNode->A->GetKey()==key || currentNode->B->GetKey()==key)
				{
					count = 2;
					return count;
				}
				else 
				{
					currentNode = Branch(currentNode, key);
				}
			}

			else
			{
				if (currentNode->A->GetKey()==key)
				{
					count = 1;
					return count;
				}
				else 
				{
					currentNode = Branch(currentNode, key);
				}
			}

		}

		return count;

	}


	void swap(T* obj1, T* obj2)
	{
		T* temp;
		temp = obj1;
		obj1 = obj2;
		obj2 = temp;
	}

	treeNode* SplitNode(treeNode* Node) //()
	{
		
		treeNode* newNode = new treeNode(Node->B);
		treeNode* newLeft = new treeNode(Node->A);
		treeNode* newRight = new treeNode(Node->C); 

	

		newNode->L = newLeft;
		newNode->M1 = newRight;


		newLeft->L = Node->L;
		newLeft->M1 = Node->M1;

		newRight->L = Node->M2;
		newRight->M1 = Node->R;

		m_root = newNode;



		return m_root;
	
	}

	treeNode* SplitNode2(treeNode* Node) //()
	{
		treeNode* newNode = new treeNode(Node->B);
		treeNode* newLeft = new treeNode(Node->A);
		treeNode* newRight = new treeNode(Node->C); 

	

		newNode->L = newLeft;
		newNode->M1 = newRight;


		newLeft->L = Node->L;
		newLeft->M1 = Node->M1;

		newRight->L = Node->L;
		newRight->M1 = Node->M1;

		m_root = newNode;



		return m_root;
	
	}

	treeNode* Split(treeNode* N, treeNode* P)
	{
		 if (P == NULL)  //split m_root
		 {
		 	P= SplitNode(N); //N.SplitNode();
	     }


		if (P->B) //parent has 2 values
		{
			if (N == P->L)
			{
				T* temp1 = P->A;
				T* temp2 = P->B;
				treeNode* temp3 = P->M1;
				treeNode* temp4 = P->M2;

				P->A = N->B;
				P->B = temp1;
				P->C = temp2;
				P->L = new treeNode(N->A, N->L, N->M1);
				P->M1 = new treeNode(N->C, N->M2, N->R);
				P->M2 = temp3;
				P->R = temp4;

				return P;
			}
			if (N == P->M1)
			{
				T* temp1 = P->B;
				treeNode* temp2 = P->M2;

				P->B = N->B;
				P->A = P->A;  // not changed
				P->C = temp1;
				P->L = P->L;  // not changed
				P->M1 = new treeNode(N->A, N->L, N->M1);
				P->M2 = new treeNode(N->C, N->M2, N->R);
				P->R = temp2;

				return P;
			}
			if (N == P->M2)
			{
				P->A = P->A;
				P->B = P->B;  // not changed
				P->C = N->B;
				P->L = P->L;
				P->M1 = P->M1; // not changed
				P->M2 = new treeNode(N->A, N->L, N->M1);
				P->R = new treeNode(N->C, N->M2, N->R);

				return P;
			}

		}
		else  // parent has 1 value
		{
			if (N == P->L)
			{
				T* temp1 = P->A;
				treeNode* temp2 = P->M1;

				P->A = N->B;
				P->B = temp1;
				P->L = new treeNode(N->A, N->L, N->M1);
				P->M1 = new treeNode(N->C, N->M2, N->R);
				P->M2 = temp2;

				return P;
			}

			if (N == P->M1)
			{
				P->A = P->A;  //not changed
				P->B = N->B;
				P->L = P->L;
				P->M1 = new treeNode(N->A, N->L, N->M1);
				P->M2 = new treeNode(N->C, N->M2, N->R);

				return P;
			}
		}
		return P;
	}


	//template <typename T>
	void AddtoLeaf(treeNode* Node, T* newObj)
	{
		if (Node->IsEmpty())   // looks like it will not happen
		{
			Node->A = newObj;
		}

		else if (Node->IsOne()) 
		{
			Node->B = newObj;
			if (Node->A->GetKey() > newObj->GetKey())
			{
				//swap(Node->A, Node->B);
				T* temp;
				temp = Node->A;
				Node->A = Node->B;
				Node->B = temp;
			}
		}
	
		else if (Node->IsTwo())
		{
			Node->C = newObj;
			if (Node->A->GetKey() < newObj->GetKey() && newObj->GetKey() < Node->B->GetKey())
			{
				//swap(Node->B, Node->C);
				T* temp;
				temp = Node->B;
				Node->B = Node->C;
				Node->C = temp;
			}
			if (Node->A->GetKey() > newObj->GetKey())
			{
				T* temp1;
				T* temp2;
				temp1 = Node->A;
				temp2 = Node->B;
				Node->A = Node->C;
				Node->B = temp1;
				Node->C = temp2;
				//swap(Node->B, Node->C);
				//swap(Node->A, Node->B);
			}
		}

	}



	treeNode* Branch(treeNode* Node, T* obj)
	{
		if (Node->A->GetKey() > obj->GetKey())
		{
			Node = Node->L;
		}
		else if (!Node->B || Node->B->GetKey() > obj->GetKey())
		{
			Node = Node->M1;
		}
		else if (!Node->C || Node->C->GetKey() > obj->GetKey())
		{
			Node = Node->M2;
		}
		else
		{
			Node = Node->R;
		}

	

		return Node;
	}

	treeNode* Branch(treeNode* Node, int key)
	{

		if (Node->A->GetKey() > key)
		{
			Node = Node->L;
		}
		else if (!Node->B || Node->B->GetKey() > key)
		{
			Node = Node->M1;
		}
		else if (!Node->C || Node->C->GetKey() > key)
		{
			Node = Node->M2;
		}
		else
		{
			Node = Node->R;
		}

	return Node;

	}




	void testfun(T& obj)
	{
		cout << "point1" << endl;
		T* newObj = new T(obj);
		cout << (*newObj).getID() << endl;
		cout << newObj->getID() << endl;
		cout << newObj->GetKey() << endl;
		cout << newObj->getName() << endl;
	}




	bool Add(const T& obj)
	{

		T* newObj = new T(obj);
		int newKey = newObj->GetKey();


		if (m_root == NULL) // case if the tree is empyty
		{
			treeNode* newRoot = new treeNode(newObj);
			m_root = newRoot;
			return true;
		}


		treeNode* currentNode = m_root;
		treeNode* parentNode = NULL;

		while (currentNode != NULL)
		{
			if (currentNode->ContainsKey(newKey))
			{
				return false;
			}

			if (currentNode->IsFull())
			{
				currentNode = Split(currentNode, parentNode);  
				//parentNode = currentNode;  
			}
	
			if (currentNode->IsLeaf())
			{
				AddtoLeaf(currentNode, newObj);
				return true;
			}

			parentNode = currentNode;
			currentNode = Branch(currentNode, newObj);
		}
	
		return true;


	
	}

	void Display(treeNode* n)
	{
		if (n == NULL)  
		{
			return;
		}

		else if (n->IsOne()) 
		{
			Display(n->L);
			n->A->write();
			Display(n->M1);
		}
	
		else if (n->IsTwo())
		{
			Display(n->L);
			n->A->write();
			Display(n->M1);
			n->B->write();
			Display(n->M2);
		}

		else
		{
			Display(n->L);
			n->A->write();
			Display(n->M1);
			n->B->write();
			Display(n->M2);
			n->C->write();
			Display(n->R);
		}


	}

	int countLevels()
	{
		int count = 0;
		if (m_root == NULL) {count = 0;}
		else
		{
			count = 1;
			treeNode* currentNode = m_root;
			while (currentNode->L)
			{
				count = count +1;
				currentNode = currentNode->L;
			}
		}
		return count;
	}


	//Display tree will set the current node as m_root

	void DisplayTree()
	{
		
		if (! m_root)
		{
			cout << "It is a empty tree!" << endl;
		}

		else
		{
			Display(m_root);
			cout << endl;
		}
	}

};
