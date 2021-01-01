# Dijkstra's algorithm
Descriptions
-
The program will determine the shortest path in a specified graph from a specified starting vertex to each other vertex in the graph with Dijkstra's algorithm efficiency with a binary heap implementation. 

User Instructions
-
Your program prompts the user to enter the name of a file specifying the graph.  Once the program is finished reading in the graph, the user will be prompted to enter the id of a starting vertex. The user will be re-prompted until they enter a valid index (i.e., a string id representing a vertex that exists in the graph). The program then applies Dijkstra's algorithm to determine the shortest path to each node from the specified starting vertex. When the algorithm has finished determining the shortest path to each node, your program output the CPU time, in seconds, that was spent executing the algorithm.The program then asks the user for the name of an output file.  If there is no path from the specified starting vertex to any existing vertex in the graph, the output should be "NO PATH"

Technical Details
-
*Look at the word document for more specific details of the program*

A graph class is constructed with Dijkstra's algorithm function.  A private nested node/vertex class and an edge class were constructed to store nodes/vertices and edges respectively in the graph. The graph stores all new incoming nodes/vertices a linked list.  A node/vertex class is constructede field of each node/vertice store an adjacency list or linked list of edge for the node.  The edge will contains a pointer to the destination node and the edge cost.

Whenever a new vertex is encountered, a hash item is added with the new vertex id to the hash table with a void pointer to point to the new node. To locate a node corresponding to a source vertex, getPointer member function of the hash table class will be used. The hashtable class will determine whether or not a starting vertex entered by the user is valid.

For Dijkstra's algorithm, to find the node correspoinding to each vertex, void pointer parameter of deleteMin will be used to have access to the node immediately

Programming Implementation:
- Linked List 
- Hashtable
- Heap of Binary Heap (Priority Queue)
- Graph

Hashtable class contains the following PRIVATE functions:
- insert
- find/contain
- hash
- rehash
- getPrime
- getPointer
- setPointer
- remove

The constructor of the hashtable class will use the getPrime function for getting a prime number as the capacity of the hashtable.

For collision resolution strategies, linear probing will be used.

The remove function in the hashtable will be using lazy-deletion.  The lazy-deleted hash item will be deleted when a rehash function will be called.

Heap contains the following functions:
- Public
  - insert
  - deleteMin
  - setKey (providing both increaseKey and decreaseKey)
  - remove
- Private
  - getPos (get position)
  - percolateUp
  - percolateDown

The constructor of the heap class accepts an integer  representing the capacity of the binary heap.

All operation are implemented to be average case logartihimic time or better algorithms, O(log N).
In order to achieve setKey and remove in average-case logarithmic time, the program will use a hashtable which each hash entry or ID includes a pointer to the associated node in the heap allows you to find the item in constant average time, O(1).
The insert operation use an average-case constant time algorithm, O(1).
 
Graph class contains the following PUBLIC functions and PRIVATE nested classes:
-Public
 - insert
 - contain/find
 - Dijkstra
 - printGraph
-Private
 - class edge
 - class node
 
 The constructor of the graph class accepts an integer representing the number of vertices that may be in the graph and hashtable
 
Input File Specifications:
- Every row in the input file represents an edge in the graph. 
- Each row consists of two string ids representing the source vertex and destination vertex of the edge (in that order) followed by a positive integer less than a million representing the cost/distance/weight of the edge. 
- All vertex ids will consist only of lowercase and capital letters and digits.
- The source vertex of an edge will never be the same as the destination vertex, but it is possible that multiple edges might connect the same vertices.
- The rows will contain no leading or trailing whitespace, single spaces will separate fields, and all rows will end with a single Unix-style newline character.

Output File Specifications:
- The output file contians one row for every vertex that exists in the graph, with vertices listed in the same order that they first appear in the input file.
- Each row in the output file contains a vertex id followed by a colon, a single space, and then the shortest distance from the specified starting vertex to the given vertex.
- All of these distances are guaranteed to be less than one billion.
- After the distance, the row contains one space, a left bracket, the path from the starting vertex to the current vertex, a right bracket, and finally a single Unix-style newline character. 
- Vertices in the path are separated by a comma followed by a single space. There should not be any space or comma before the first vertex in the path (the specified starting vertex) or after the last vertex in the path.
- If there is no path from the specified starting vertex to any existing vertex in the graph, the corresponding output row contains the vertex id followed by a colon, a single space, and then the text "NO PATH" followed by a single Unix-style newline character. 
