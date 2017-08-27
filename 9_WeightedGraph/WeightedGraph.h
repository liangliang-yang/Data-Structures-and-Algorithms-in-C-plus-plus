// WeightedGraph.h
// HW_9
// Created by Liangliang Yang on 07/18/2016

#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
#define _CRT_SECURE_NO_WARNINGS 

#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include <math.h>
#include <cmath>

using namespace std;


class WeightedGraph
{

private:

	struct Edge
	{
		int start; // index of start and end nodes
		int end;
		double weight;
		Edge(int startIndex, int endIndex, double weightValue)
		{
			start = startIndex;
			end = endIndex;
			weight = weightValue;
		}

	};

	struct Node
	{
		string nodeName;
		//Node(const string& name)
		Node(string& name)
		{
			nodeName = name;
		}

		// list of incoming and outgoing edges to the node
		vector<Edge*> In;
		vector<Edge*> Out;

	};



	vector<Node*> m_nodes; // list of nodes in the graph
	vector<Edge*> m_edges; // list of edges


public:

	WeightedGraph() {}
	
	~WeightedGraph()
	{
		for (unsigned i = 0; i < m_nodes.size(); i++)
		{
			delete m_nodes[i];
		}
		m_nodes.clear();
		for (unsigned i = 0; i < m_edges.size(); i++)
		{
			delete m_edges[i];
		}
		m_edges.clear();

	}


	//void AddNode(const string& nodeName)
	void AddNode(string& nodeName)
	{
		Node* newNode = new Node(nodeName);
		m_nodes.push_back(newNode);
	}

	//void AddEdge(const string& startnodeName, const string& endnodeName, double weightValue)
	void AddEdge(string& startnodeName, string& endnodeName, double weightValue)
	{
		int startIndex = FindNode(startnodeName);
		int endIndex = FindNode(endnodeName);

		if(startIndex == -1 || endIndex == -1)
		{
			return;
		}

		Edge* newEdgeforth = new Edge(startIndex, endIndex, weightValue);
		Edge* newEdgeback = new Edge(endIndex, startIndex, weightValue);

		m_edges.push_back(newEdgeforth);
		m_edges.push_back(newEdgeback);

		// add the incoming and outgoing edges to the node struct
		m_nodes[startIndex]->Out.push_back(newEdgeforth);
		m_nodes[endIndex]->In.push_back(newEdgeforth);
		m_nodes[startIndex]->In.push_back(newEdgeback);
		m_nodes[endIndex]->Out.push_back(newEdgeback);

	}

	vector<string> split(string str, char delimiter)
	{
		vector<string> v0;
		stringstream ss(str); // turn the string into a stream
		string token;

		while(getline(ss, token, delimiter))
		{
			v0.push_back(token);
		}
		 return v0;
	}

	void set(string& strNode, string& strEdge)
	{
		// delete the old graph objects

		for (unsigned i = 0; i < m_nodes.size(); i++)
		{
			delete m_nodes[i];
		}
		m_nodes.clear();
		for (unsigned i = 0; i < m_edges.size(); i++)
		{
			delete m_edges[i];
		}
		m_edges.clear();

		vector<string> vnode;
		vector<string> vedge;

		vnode = split(strNode, ',');   // set the m_nodes
		for(unsigned i=0; i<vnode.size(); i++)
		{
			AddNode(vnode[i]);
		}

		vedge = split(strEdge, ';');  // set the m_edges
		for (unsigned j=0; j<vedge.size(); j++)
		{
			vector<string> vtemp = split(vedge[j], ',');
			string startnodeName = vtemp[0];
			string endnodeName = vtemp[1];
			double weightValue = stod(vtemp[2]);

			AddEdge(startnodeName, endnodeName, weightValue);
		}


	}

	//int FindNode(const string& Name) 
	int FindNode(string& Name) // find and return the index of a nodeName
	{
		int index = -1;
		for (unsigned i=0; i<m_nodes.size(); i++)
		{
			if (m_nodes[i]->nodeName == Name)
			{
				index = i;
				return index;
			}
		}
		return index;
	}

	vector<Edge*> getOut(Node* N)  // get all the outgoing edges from a node
	{
		vector<Edge*> output;
		for(unsigned i=0; i<m_edges.size(); i++)
		{
			Node* start = m_nodes[m_edges[i]->start];
			if(start == N)
			{
				output.push_back(m_edges[i]);
			}
		}
		return output;
	}

	int outdegree(Node* N)  // get the outdegree for a node
	{
		vector<Edge*> output;
		for(unsigned i=0; i<m_edges.size(); i++)
		{
			Node* start = m_nodes[m_edges[i]->start];
			if(start == N)
			{
				output.push_back(m_edges[i]);
			}
		}
		
		int out = output.size();
		return out;
	}

	void getIn(Node* N, vector<Edge*> input)  // get all the incoming edges from a node
	{
		for(unsigned i=0; i<m_edges.size(); i++)
		{
			Node* end = m_nodes[m_edges[i]->end];
			if(end == N)
			{
				input.push_back(m_edges[i]);
			}
		}

	}

	int indegree(Node* N)  // get all the incoming edges from a node
	{
		vector<Edge*> input;
		for(unsigned i=0; i<m_edges.size(); i++)
		{
			Node* end = m_nodes[m_edges[i]->end];
			if(end == N)
			{
				input.push_back(m_edges[i]);
			}
		}

		int in = input.size();
		return in;
	}


	int GetDegree(string& nodeName)
	{
		int nodeIndex = FindNode(nodeName);
		int degree = 0;

		// first check whether the node is valid
		if(nodeIndex == -1) 
		{
			degree = nodeIndex;
		}
		else
		{
			//int degree = 0;
			degree = outdegree(m_nodes[nodeIndex]) + indegree(m_nodes[nodeIndex]);
			//degree = outdegree(m_nodes[nodeIndex]);

			//cout << "degree is: " << degree << endl;
		}

		return degree;
	}




	vector<Node*> Shortest_Path(string& startnodeName, string& endnodeName)
	{
		vector<Node*> truePath;  //the true path that need to be returned
		int startIndex = FindNode(startnodeName);
		int endIndex = FindNode(endnodeName);

		// if nodes not in the list
		if(startIndex == -1 || endIndex == -1)
		{
			//cout << "no path" << endl;
			truePath.clear();
			return truePath;
		}

		// if node is isolated
		if(m_nodes[startIndex]->Out.empty() || m_nodes[endIndex]->In.empty())
		{
			truePath.clear();
			return truePath;
		}

		//double Inf = std::numeric_limits<double>::infinity();
		float Inf = INFINITY;

		vector<double> cost;
		vector<bool> visited;

		for (int i=0; i<m_nodes.size(); i++)
		{
			if (i == startIndex)
			{
				cost.push_back(0);
			}
			else
			{
				cost.push_back(Inf);
			}

			visited.push_back(false);
		}

		// set start as the current node

		Node* currentNode = m_nodes[startIndex];
		int currentIndex = startIndex;
		Node* startNode = m_nodes[startIndex];
		Node* endNode = m_nodes[endIndex];

		int lowestUnvisited = currentIndex;

		while (currentNode != endNode && cost[lowestUnvisited] != Inf)
		{

			int test = currentNode->Out.size();

			for (int j=0; j<currentNode->Out.size(); j++)
			{
				if (cost[currentIndex] + currentNode->Out[j]->weight < cost[currentNode->Out[j]->end])
				{
					cost[currentNode->Out[j]->end] = cost[currentIndex] + currentNode->Out[j]->weight;
				}
			}

			visited[currentIndex] = true;
		
			// find the unvisited node with lowest cost

			//vector<Node*> unvisitedNode; 
			vector<int> unvisitedIndex;

			for (int k=0; k<visited.size(); k++)
			{

				if (!visited[k])
				{
					//unvisitedNode.push_back(m_nodes[k]);
					unvisitedIndex.push_back(k);
				}
				
			}

			if (!unvisitedIndex.empty())
			{
				lowestUnvisited = unvisitedIndex[0];
			}
				
			for (int i=0; i<unvisitedIndex.size(); i++)
			{
				if (cost[unvisitedIndex[i]] < cost[lowestUnvisited])
				{
					lowestUnvisited = unvisitedIndex[i];
				}
			}
			
			unvisitedIndex.clear();


			currentIndex = lowestUnvisited;
			currentNode = m_nodes[currentIndex];
		}

		if (currentNode != endNode)
		{
			//cout << "no path" << endl;
			truePath.clear();
			return truePath;
		}

		vector<Node*> reversePath;
		

		currentIndex = FindNode(currentNode->nodeName);

		if (currentNode == endNode)
		{
			reversePath.push_back(endNode);
		}


		while (currentNode != startNode)
		{
			int size = currentNode->In.size();
			for(int j=0; j<size; j++)
			{
				//while (currentNode != startNode)
				//{
					if(cost[currentIndex] - currentNode->In[j]->weight == cost[currentNode->In[j]->start])
					{
						
						currentIndex = currentNode->In[j]->start;
						currentNode = m_nodes[currentIndex];
						break;
					}
				//}
			}

			reversePath.push_back(currentNode);
		}

		for(int k=reversePath.size()-1; k>=0; k--)
		{
			truePath.push_back(reversePath[k]);
		}

		return truePath;
	}

	void display(vector<Node*> path)
	{
		if (path.empty())
		{
			cout << "no path" << endl;
		}
		else
		{
			for(int i=0; i<path.size(); i++)
			{
				cout << path[i]->nodeName << ",";
			}

			cout << endl;
		}
	}

	int pathLength(vector<Node*> pathNode)
	{
		int length = 0;

		for (int i=0; i<pathNode.size()-1; i++)
		{
			for (int j=0; j<pathNode[i]->Out.size(); j++)
			{
				if(pathNode[i]->Out[j]->end == FindNode(pathNode[i+1]->nodeName))
				{
					length = length + pathNode[i]->Out[j]->weight;
					break;
				}
			}
		}

		return length;
	}




};

#endif
