// 
//
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

#include "graph.h"

using namespace std;

#define help() (cout << "help" << endl)


//Loading Dictionary into Hash Table
void loadGraph(const string &filename, graph &greed)
{
	ifstream input(filename); //Open Dictionary File
	if (!input) {
		cerr << "Error: could not open " << filename << "\n";  //If Dictionary File Failed
		exit(1);
	}

	string line, start, end;  // start- starting vertex 
							  // end - ending vertex
	int weight; // weight from starting vertex to ending vertex

	while(!input.eof())
	{
		getline(input, line);
		stringstream ss(line);
		ss >> start >> end >> weight;
		// When the vertex id is not found in hashtable,
		// insert vertex id into hashtable
		greed.insert(start, end, weight);
	}

	input.close();  //Close Dictionary File
}


int main()
{
	string filename, start;
	int n = 500;
	graph greed(n);  //Initalize the graph to have n vertices

	//Graph File Input	
	cout << "Enter name of graph file: ";
	cin >> filename;
	loadGraph(filename, greed);	//Loading Graph

	//Get the starting vertex from the user
	while (1)
	{
		cout << "Enter ID of the starting vertex: ";
		cin >> start;
		if (greed.contains(start))
			break;
		cout << "\nERROR, that input is not valid!" << endl;
	}

	//CPU time to find the shortest path from starting vertex
	clock_t t1 = clock();
	greed.Dijkstra(start);	// Dijkstra's algorithm to find the shortest path
	clock_t t2 = clock();
	double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;  // Time taken to find the shortest path
	cout << "Total time (in seconds) for Dijkstra's Algorithm : " << timeDiff << endl;
	
	//Output File
	cout << "Enter name of output file: ";
	cin >> filename;
	greed.printGraph(filename);//loadOut(filename, greed); //Loading Output file
	return 0;
}
