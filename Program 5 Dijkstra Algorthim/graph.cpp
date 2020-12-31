#include "graph.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <iterator>

#define help() (std::cout << "help" << std::endl)

//Intialized the hashtable with a starting size
graph::graph(int vertices):table(vertices*2)
{
}


void graph::insert(const std::string &id, const std::string &id2, int w)
{
	// Check if the starting vertex is in the graph
	if(!table.contains(id))
	{
		//Create and insert a new node in the graph
		node N;
		N.name = id;
		vertex.push_back(N);  
		table.insert(id, &(vertex.back())); //Put the node in the hashtable
		vertices++; // Numbers of vertices in the graph increase by 1
	}
	// Check if the destination vertex is in the graph
	if (!table.contains(id2))
	{
		//Create and insert a new node in the graph
		node N;
		N.name = id2;
		vertex.push_back(N);
		table.insert(id2, &(vertex.back())); //Put the node in the hashtable
		vertices++;  // Numbers of vertices in the graph increase by 1
	}

	//Get the starting and destination node pointer from hashtable
	bool b, b2;
	node* start = static_cast<node*>(table.getPointer(id, &b));
	node* end = static_cast<node*>(table.getPointer(id2, &b2));

	//Make a new edge from starting vertice;
	edge sgt;
	(sgt).dest = end;  //Assign edge destination
	(sgt).weight = w;  //Assign edge weight
	(*start).dir.push_back(sgt);  //Insert the edge to adjacent list of the starting vertex
}


bool graph::contains(const std::string &id)
{
	return table.contains(id);
}


void graph::Dijkstra(const std::string &id)
{
	//Get the pointer of the starting vertex from user
	//Set the distance and path of the starting vertex to itself
	bool b;
	node* start = static_cast<node*>(table.getPointer(id, &b));
	start->distance = 0;  
	start->path = start->name;

	//Insert the vertices into the heap
	heap min(vertices);
	for (auto it = vertex.begin(); it != vertex.end(); it++)
	{
		min.insert((*it).name, (*it).distance, &(*it));
	}

	//When the root get deleted in the heap, assign the root pointer to ppData 
	node* ppData;
	while (min.deleteMin(nullptr,nullptr, &ppData) != 1) //Keep deleting the root of the node till the heap is empty
	{
		//Set the root pointer to be known in the Dijkstra Algorithm
		(*ppData).known = true;

		//If the root pointer has no path from the starter vertex to itself, then continue
		if (ppData->path == "")
			continue;

		//Look through the adjacent edges of the root pointer
		for (auto it : ppData->dir)
		{
			//If the adjacent edge's destination vertex is not known, check if the shortest path to the destination vertex is optimized
			if (!(it.dest)->known)
			{
				int cost = it.weight;  //Cost of the edge to destination vertex 
				int total = ppData->distance + cost; //New destination vertex distance = root distance + cost

				//New destination vertex distance < old destination vertex distance
				//Update the destination vertex distance and path and the position in the heap
				if (total < (it.dest)->distance)
				{
					(it.dest)->path = ppData->path + ", " + (it.dest)->name;
					(it.dest)->distance = total;
					min.setKey((it.dest)->name, total);
				}
			}				
		}		
	}
}



void graph::printGraph(const std::string &filename)
{
	std::ofstream output(filename);	//Open Output File

	// Print out the path from the start vertex to each other vertex
	// If there is no path from start vertex to one of the other vertices, then print out "NO PATH".
	for(auto it : vertex)
	{
		if (it.path != "")
			output << it.name + ": " + std::to_string(it.distance) + " [" + it.path + "]" << std::	endl;
		else
			output << it.name + ": NO PATH" << std::endl;
	}
	output.close();
}

