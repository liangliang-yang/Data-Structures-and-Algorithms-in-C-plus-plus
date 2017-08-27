// My234tree.h
// HW_6
// Created by Liangliang Yang on 07/02/2016

#pragma once

//#include "treeNode.h"
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

		bool Is_One_and_Leaf()
		{
			return (A != NULL && B == NULL && C == NULL && L == NULL && M1 == NULL && M2 == NULL && R == NULL);
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

		T* Obj_with_key (int key)
		{
			T* obj = NULL;
			if (C && C->GetKey() == key) { obj = C; }
			if (B && B->GetKey() == key) { obj = B; }
			if (A->GetKey() == key) { obj = A; }
			return obj;
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

	
	// this function not been used
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




	// this function not been used
	treeNode* FindParent(treeNode* child)  // it is the case that the child must inside the tree, not consider the other cases 
	{
		if (child == m_root) // first check special case
		{
			return NULL;
		}
		treeNode* parentNode = NULL;
		treeNode* currentNode = m_root;

		while (!currentNode->IsLeaf())
		{
			if (child == currentNode->L || child == currentNode->M1 || child == currentNode->M2 || child == currentNode->R)
			{
				parentNode = currentNode;
				return parentNode;
			}
			else
			{
				currentNode = Branch(currentNode, child->A->GetKey());
			}
		}

		return parentNode;
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


	void Swap(T& obj1, T& obj2)
	{
		T temp = obj1;
		obj1 = obj2;
		obj2 = temp;
	}

	void Swap(T* obj1, T* obj2)
	{
		T temp = *obj1;
		*obj1 = *obj2;
		*obj2 = temp;
	}


	treeNode* SplitNode(treeNode* Node) 
	{
		
		treeNode* newNode = new treeNode(Node->B);
		treeNode* newLeft = new treeNode(Node->A);
		treeNode* newRight = new treeNode(Node->C); 

		// in the treeNode.h, the constructor has already set all to NULL, so only need to change those non-NULL parts

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

		// in the treeNode.h, the constructor has already set all to NULL, so only need to change those non-NULL parts

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
		if (P == NULL)  
		{
			P= SplitNode(N); 
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


	treeNode* FindMin(treeNode* N) // find and return the node contains the min value in the subtree tree of node N
	{
		if (N->IsLeaf())
		{
			return N;
		}
		while (N->L)
		{
			N = N->L;
		}
		return N;
	}

	treeNode* FindMax(treeNode* N) // find and return the node contains the max value in the subtree tree of node N
	{
		while (!N->IsLeaf())
		{
			if (N->C)
			{
				N = N->R;
			}
			else if (N->B)
			{
				N = N-> M2;
			}
			else
			{
				N = N->M1;
			}
		}
		return N;
	}

	T* FindMin_of_Right(treeNode* N, T* keyObj)  // find the obj that contains min in the right subtree, just consider the case when N has two or three items
	{
		T* targetObj = NULL;
		treeNode* targetNode = NULL;
		if (N->C && keyObj == N->C)
		{
			targetNode = FindMin(N->R);
			targetObj = targetNode->A;
		}
		if (N->B && keyObj == N->B)
		{
			targetNode = FindMin(N->M2);
			targetObj = targetNode->A;
		}
		if (keyObj == N->A)
		{
			targetNode = FindMin(N->M1);
			targetObj = targetNode->A;
		}
		return targetObj;
	}

	treeNode* FindSibling(treeNode* currentNode, treeNode* parentNode)
	{
		treeNode* siblingNode = NULL;
		if (currentNode == parentNode->L)
		{
			if (parentNode->M1->B)
			{
				siblingNode = parentNode->M1;
			}
		}
		else if (currentNode == parentNode->M1)
		{
			if (parentNode->L->B)
			{
				siblingNode = parentNode->L;
			}
			else if (parentNode->M2->B)
			{
				siblingNode = parentNode->M2;
			}
		}
		else if (currentNode == parentNode->M2)
		{
			if (parentNode->M1->B)
			{
				siblingNode = parentNode->M1;
			}
			else if (parentNode->R->B)
			{
				siblingNode = parentNode->R;
			}
		}
		else
		{
			if (parentNode->M2->B)
			{
				siblingNode = parentNode->M2;
			}
		}

		return siblingNode;
	}

	// rotate the tree, happens when there is only one item in the current node, and sibling node has two or three items
	void Rotate(treeNode* currentNode, treeNode* parentNode, treeNode* siblingNode)
	{
		// if current key < sibling key, process the left rotate
		if (currentNode->A->GetKey() < siblingNode->A->GetKey())
		{
			T* tempA = siblingNode->A;
			treeNode* tempL = siblingNode->L;
			siblingNode->A = siblingNode->B;
			siblingNode->B = siblingNode->C;
			siblingNode->C = NULL;
			siblingNode->L = siblingNode->M1;
			siblingNode->M1 = siblingNode->M2;
			siblingNode->M2 = siblingNode->R;
			siblingNode->R = NULL;
			
			if (currentNode == parentNode->L)
			{
				currentNode->B = parentNode->A;
				currentNode->M2 = tempL;
				parentNode->A = tempA;
			}
			else if (currentNode == parentNode->M1)
			{
				currentNode->B = parentNode->B;
				currentNode->M2 = tempL;
				parentNode->B = tempA;
			}
			else // currentNode == parentNode->M2
			{
				currentNode->B = parentNode->C;
				currentNode->M2 = tempL;
				parentNode->C = tempA;
			}

		}
		
		//else will process the right rotate, right rotate has two cases, where sibling has 2 or 3 items
		else
		{
			if (siblingNode->C)  // sibling has three items
			{
				T* tempC = siblingNode->C;
				treeNode* tempR = siblingNode->R;
				siblingNode->C = NULL;
				siblingNode->R = NULL;
				currentNode->B = currentNode->A;
				currentNode->M1 = currentNode->L;
				currentNode->M2 = currentNode->M1;

				if (currentNode == parentNode->M1)
				{
					currentNode->A = parentNode->A;
					currentNode->L = tempR;
					parentNode->A = tempC;
				}
				else if (currentNode == parentNode->M2)
				{
					currentNode->A = parentNode->B;
					currentNode->L = tempR;
					parentNode->B = tempC;
				}
				else  // currentNode == parentNode->R
				{
					currentNode->A = parentNode->C;
					currentNode->L = tempR;
					parentNode->C = tempC;
				}
			}
			else  // sibling has two items
			{
				T* tempB = siblingNode->B;
				treeNode* tempM2 = siblingNode->M2;
				siblingNode->B = NULL;
				siblingNode->M2 = NULL;
				currentNode->B = currentNode->A;
				currentNode->M1 = currentNode->L;
				currentNode->M2 = currentNode->M1;

				if (currentNode == parentNode->M1)
				{
					currentNode->A = parentNode->A;
					currentNode->L = tempM2;
					parentNode->A = tempB;
				}
				else if (currentNode == parentNode->M2)
				{
					currentNode->A = parentNode->B;
					currentNode->L = tempM2;
					parentNode->B = tempB;
				}
				else  // currentNode == parentNode->R
				{
					currentNode->A = parentNode->C;
					currentNode->L = tempM2;
					parentNode->C = tempB;
				}
			}
		}
	}

	void Borrow_from_parent(treeNode* currentNode, treeNode* parentNode)
	{
		if (currentNode == parentNode->L)
		{
			currentNode->B = parentNode->A;
			currentNode->C = parentNode->M1->A;
			currentNode->M2 = parentNode->M1->L;
			currentNode->R = parentNode->M1->M1;
			//T* tempA = parentNode->A;
			parentNode->A = parentNode->B;
			parentNode->B = parentNode->C;
			parentNode->C = NULL;
			parentNode->L = currentNode;
			parentNode->M1 = parentNode->M2;
			parentNode->M2 = parentNode->R;
			parentNode->R = NULL;
		}
		else if (currentNode == parentNode->M1)
		{
			currentNode->C = currentNode->A;
			currentNode->A = parentNode->L->A;
			currentNode->B = parentNode->A;
			currentNode->M2 = currentNode->L;
			currentNode->R = currentNode->M1;
			currentNode->L = parentNode->L->L;
			currentNode->M1 = parentNode->L->M1;
			//T* tempA = parentNode->A;
			parentNode->A = parentNode->B;
			parentNode->B = parentNode->C;
			parentNode->C = NULL;
			parentNode->L = currentNode;
			parentNode->M1 = parentNode->M2;
			parentNode->M2 = parentNode->R;
			parentNode->R = NULL;
		}
		else if (currentNode == parentNode->M2)   
		{
			currentNode->C = currentNode->A;
			currentNode->A = parentNode->M1->A;
			currentNode->B = parentNode->B;
			currentNode->M2 = currentNode->L;
			currentNode->R = currentNode->M1;
			currentNode->L = parentNode->M1->L;
			currentNode->M1 = parentNode->M1->M1;
			//T* tempA = parentNode->A;
			//parentNode->A = parentNode->B;
			parentNode->B = parentNode->C;
			parentNode->C = NULL;
			//parentNode->L = currentNode;
			parentNode->M1 = currentNode;
			parentNode->M2 = parentNode->R;
			parentNode->R = NULL;
		}
		else  //currentNode == parentNode->R
		{
			currentNode->C = currentNode->A;
			currentNode->A = parentNode->M2->A;
			currentNode->B = parentNode->C;
			currentNode->M2 = currentNode->L;
			currentNode->R = currentNode->M1;
			currentNode->L = parentNode->M2->L;
			currentNode->M1 = parentNode->M2->M1;
			//T* tempA = parentNode->A;
			//parentNode->A = parentNode->B;
			//parentNode->B = parentNode->C;
			parentNode->C = NULL;
			//parentNode->L = currentNode;
			parentNode->M2 = currentNode;
			//parentNode->M2 = parentNode->R;
			parentNode->R = NULL;
		}
		

	}

	void Borrow_from_sibling(treeNode* currentNode, treeNode* parentNode)
	{
		treeNode* siblingNode = FindSibling(currentNode, parentNode);
		if (siblingNode)
		{
			Rotate(currentNode, parentNode, siblingNode);
			return;
		}
	}

	void Merge(treeNode* currentNode, treeNode* parentNode, treeNode* siblingNode)
	{
		// first check if it can borrow from sibling node
		siblingNode = FindSibling(currentNode, parentNode);
		if (siblingNode)
		{
			Rotate(currentNode, parentNode, siblingNode);
			//return;
		}
		else
		{
			Borrow_from_parent(currentNode, parentNode);
		}
	}


	void remove(int key)
	{
		// special case one
		if (!m_root) { return; }

		// special case two
		if (m_root->IsLeaf())
		{
			if (!m_root->ContainsKey(key))
			{ 
				return; 
			}
			else 
			{
				DeleteKey_from_Leaf(m_root, key);
				return;
			}

		}

		// special case three, very important for input 4
		if (m_root->IsOne() && m_root->L->Is_One_and_Leaf() && m_root->M1->Is_One_and_Leaf())
		{
			T* tempA = m_root->A;
			m_root->A = m_root->L->A;
			m_root->B = tempA;
			m_root->C = m_root->M1->A;
			m_root->L = NULL;
			m_root->M1 = NULL;
			m_root->M2 = NULL;
			m_root->R = NULL;
			if (!m_root->ContainsKey(key))
			{ 
				return; 
			}
			else 
			{
				DeleteKey_from_Leaf(m_root, key);
				return;
			}
		}


		treeNode* currentNode = m_root;
		treeNode* parentNode = NULL;
		treeNode* siblingNode = NULL;

		while (currentNode)
		{
			if (currentNode->IsOne() && currentNode != m_root) 
			{
				Merge(currentNode, parentNode, siblingNode);
			}

			else
			{
				if (!currentNode->ContainsKey(key))  // if node not contains the key, just branch
				{
				parentNode = currentNode;
				currentNode = Branch(currentNode, key);
				}
				else  // node contains the key
				{
					if (currentNode->IsLeaf()) // if the node is leaf, just delete it
					{
						DeleteKey_from_Leaf(currentNode, key);
						return;
					}
					else // case when the node is an internal node
					{
						T* keyObj = currentNode->Obj_with_key(key);
						T* minRight = FindMin_of_Right(currentNode, keyObj);
						T* temp = minRight;
						remove(minRight->GetKey());
						Swap(temp, keyObj);
						return;
					}
				}
			}

		}

	}



	void DeleteKey_from_Leaf(treeNode* N, int key)  // delete the item with key, consider only the case when the node contains two or more items
	{
		if (N->IsFull())
		{
			if (N->C->GetKey() == key) { N->C = NULL; }
			if (N->B->GetKey() == key) 
			{
				N->B = N->C;
				N->C = NULL;
			}
			if (N->A->GetKey() == key) 
			{
				N->A = N->B;
				N->B = N->C;
				N->C = NULL;
			}
		}
		if (N->IsTwo())
		{
			if (N->B->GetKey() == key) { N->B = NULL;}
			if (N->A->GetKey() == key)
			{
				N->A = N->B;
				N->B = NULL;
			}
		}

		if (N->IsOne())  // only will happen when there is only one level and one item in the tree 
		{
			if (N->A->GetKey() == key)
			{
				N->A = NULL;
			}
		}
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
		//treeNode* currentNode = m_root;
		
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
