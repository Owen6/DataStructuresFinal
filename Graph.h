/*
*	Andrew Ngo, Owen Boxx
*	May 6, 2020
*	CS 302 Final Project - Traveling Salesman Problem
*	Header file for classes, include implementation
*/

#ifndef Graph_H
#define Graph_H

#include <iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

/************************* BEGINNING OF POINT CLASS *************************/
// Declaration of Point class
class Point
{
	public:
	int value;
	string cityName;
	friend bool operator== (const Point &lhs, const Point &rhs);
};

// Definition of overloaded comparison operator== for Point class
bool operator== (const Point &lhs, const Point &rhs)
{
		return (lhs.value == rhs.value && lhs.cityName == rhs.cityName);
}
/**************************** END OF POINT CLASS ****************************/

/************************* BEGINNING OF EDGE CLASS *************************/
// Declaration of Edge class
class Edge
{
	public:
	Point source, dest;
	int cost;
	friend bool operator== (const Edge &lhs, const Edge &rhs);
	friend ostream& operator<< (ostream &os, const Edge &e);
};

// Definition of overloaded comparison operator== for Edge class
bool operator== (const Edge &lhs, const Edge &rhs)
{
	if ((lhs.source == rhs.source && lhs.dest == rhs.dest))
	{
		return true;
	}
	else if ((lhs.source == rhs.dest && lhs.dest == rhs.source))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Definition of overloaded insertion operator for Edge class
ostream& operator<< (ostream &os, const Edge &e)
{
	os << e.source.cityName << " to " << e.dest.cityName << "	";
	return os;
}
/**************************** END OF EDGE CLASS ****************************/

/************************* BEGINNING OF VERTEX CLASS *************************/
// Vertex class declaration
class Vertex
{
	public:
	Point source;
	vector<Point> dest;
	friend ostream& operator<< (ostream &os, const Vertex &v);
};

// Definition of overloaded insertion operator<< for Vertex class
ostream& operator<< (ostream &os, const Vertex &v)
{
		os << v.source.cityName;
		return os;
}
/**************************** END OF VERTEX CLASS ****************************/

/************************* BEGINNING OF GRAPH CLASS *************************/
// Declaration of Graph class
class Graph
{
	private:
		vector<Vertex> m_adjList;
		vector<Edge> m_edgeList;

	public:
		Graph(vector<Edge> &edge);
		Vertex* findVertex(const Point &point);
		void linkVertices(const Edge &edge, bool toggleRecursion = true);
		bool isEdge(Edge& edge);
		void shortestPath();
		int getCost(Point y, Point z);
		friend ostream& operator<< (ostream &os, const Graph &obj);
};

// Definition of parameterized constructor for Graph class
Graph::Graph(vector<Edge> &edges)
{
		for (size_t i = 0; i < edges.size(); i++)
		{
				m_edgeList.push_back(edges[i]);
				linkVertices(edges[i]);
		}
		shortestPath();
}

// Definition of findVertex() function for Graph class
// Purpose: finds vertices
Vertex* Graph::findVertex(const Point &point)
{
		for (size_t i = 0; i < m_adjList.size(); i++)
		{
				if (m_adjList[i].source == point)
				{
						return &m_adjList[i];
				}
		}
		return nullptr;
}

// Definition of linkVertices() function for Graph class
// Purpose: recursively links vertices
void Graph::linkVertices(const Edge &edge, bool toggleRecursion)
{
		/// Check for vertex in graph with source == edge.source
		if (findVertex(edge.source))
		{
				for (size_t i = 0; i < m_adjList.size(); i++)
				{
						if (m_adjList[i].source == edge.source)
						{
								m_adjList[i].dest.push_back(edge.dest);
						}
				}
		}
		else
		{
				Vertex newVertex;
				newVertex.source = edge.source;
				newVertex.dest.push_back(edge.dest);
				m_adjList.push_back(newVertex);
		}

		if (toggleRecursion)
		{
				linkVertices(Edge {edge.dest, edge.source}, false);
		}
}

// Definition of isEdge() function for Graph class
// Purpose: returns bool of whether a passed edge is an edge or not
bool Graph::isEdge(Edge& edge)
{
	for(size_t i = 0; i < m_edgeList.size(); i++)
	{
		if(edge == m_edgeList[i])
		{
			return true;
		}
	}
	return false;
}

// Definition of overloaded insertion operator<< for Graph class
ostream& operator<< (ostream &os, const Graph &obj)
{
	for(size_t i = 0; i < obj.m_adjList.size(); i++)
	{
		os << obj.m_adjList[i];
		os << '\n';
	}

	return os;
}

// Definition of shortestPath function for Graph class
// Purpose: outputs shortest path to terminal
void Graph::shortestPath()
{
		vector<int> index;
		for (int i = 1; i < 5; i++)
			index.push_back(i);

		vector<int> path;
		int cheapest = INT_MAX;

		do {
				int weight = 0;
				int j = 0;
				int miles;
				
				cout << m_adjList[j];
				for (int i = 0; i < index.size(); i++)
				{
						miles = getCost(m_adjList[j].source, m_adjList[index[i]].source);
						weight += miles;
						cout << " to " << m_adjList[index[i]];
						j = index[i];
				}
				miles = getCost(m_adjList[j].source, m_adjList[0].source);
				weight += miles;

				if(cheapest > weight)
				{
					cheapest = weight;
					path = index;
				}
				cout << " and back to " << m_adjList[0] << "- " << weight << " miles, Cost(gallons): " << (weight/40) << endl;
		} while (next_permutation(index.begin(), index.end()));

		cout << "\nThe most cost effective path is:\n " << m_adjList[0];
		for(int n = 0; n < path.size(); n++)
		{
			cout <<" to " << m_adjList[path[n]];
		}
		cout << " and back to " << m_adjList[0] << " \nWith " << cheapest <<" miles, Cost(gallons): " << (cheapest/40) << endl;
}

// Definition of getCost function for Graph class
int Graph::getCost(Point y, Point z)
{
	for(int i = 0; i < m_edgeList.size(); i++)
	{
		if ((y == m_edgeList[i].source && z == m_edgeList[i].dest) || (y == m_edgeList[i].dest && z == m_edgeList[i].source))
		{
			return m_edgeList[i].cost;
		}
	}
	
	Edge temp;
	temp.source = y;
	temp.dest = z;
	int sourceCost = INT_MAX, destCost = INT_MAX;
	int sourceIndex, destIndex;
	if(!isEdge(temp))
	{
		for(int k = 1; k < m_edgeList.size(); k++)
		{
			if (y == m_edgeList[k].source || y == m_edgeList[k].dest)
			{
				if (sourceCost > m_edgeList[k].cost)
				{
					sourceCost = m_edgeList[k].cost;
					sourceIndex = k;
				}
			}
			
			if (z == m_edgeList[k].dest ||	z == m_edgeList[k].source)
			{
				if (destCost > m_edgeList[k].cost)
				{
					destCost = m_edgeList[k].cost;
					destIndex = k;
				}
			}
		}
		return (sourceCost + destCost);
	}
}
/**************************** END OF GRAPH CLASS ****************************/

#endif //CLASSES_H
