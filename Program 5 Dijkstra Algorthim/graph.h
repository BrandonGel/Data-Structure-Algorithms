#ifndef _GRAPH_H
#define _GRAPH_H

#include "heap.h"
#include "hash.h"

#include <iterator>
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>

class graph 
{

public:

	// The constructor initializes the graph.
	// The vertices are used to initalize the hashtable
	graph(int vertices);

	// Insert a new vertex in the graph
	void insert(const std::string &id, const std::string &id2, int w);

	// Check if the specified id is in the graph.
	// If so, return true; otherwise, return false.
	bool contains(const std::string &id);

	// Use Dijkstra's algorithm to find the shortest weighted-path from
	// starting vertex to all the other vertex"
	void Dijkstra(const std::string &id);

	// Write out an output file
	// If path to a vertex is known, return vertex name, the path distance ,and path; 
	// otherwise, return vertex name and "NO PATH
	void printGraph(const std::string &filename);

private:

	// Each item in the graph contains:
	// node - the vertex
	// name - name of vertex
	// path - consisted of names of vertices to get to the node
	// distance - the distance from starting vertex to destinatio vertex.
	//			  It is initially infinity (or max value of the data type)
	//			  but is updated in Dijkstra's Algorithm 
	// dir - a list of all the edges that comes out from the vertex
	// known - initally false
	//		   become true when the heap delete the node at the root
	//
	// edge - the edge that connects one vertex to another.
	// dest - pointer to the destination vertex
	// weight - the weight from the starting vertex to the destination vertex


	
	
	class edge;
	class node;

	class node {
	public:
		std::string name;
		std::string path;
		std::list<edge> dir;
		int distance = INT32_MAX;
		bool known = false;
	};
	
	class edge {
	public:
		node* dest;
		int weight;
	};

	std::list<node> vertex;  // This is where the vertices are being inserted
	int vertices = 0;	// The number of vertices currently in the graph

	hashTable table; // Map vertex name to node (vertex) pointer
};

#endif //_GRAPH_H
