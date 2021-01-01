# Binary-Heap
Descriptions
-
Use a binary heap to store named IDs with integers value

User Instructions
-
The program prompts the user for entering the capacity of the binary heap.  Then the program will display the user, a list of choice to pick:
1) Insert a new item into the binary heap
2) Set the key of a specified item
3) Delete a specified item
4) Perform a deleteMin
5) Quit


Technical Details
-
*Look at the word document for more specific details of the program*

A class called "heap" provides programmers with the functionality of a priority queue using a binary heap implementation. Each item inserted into the binary heap will specify a unique string id, an integer key, and optionally any pointer. The implementation of the class use pointers to void in order to handle pointers to any type of data. When a heap is declared, a capacity will be passed to its constructor representing the maximum number of items that may be in the heap at one time; the heap will never be allowed to grow past its initial capacity.

Programming Implementation:
- Hashtable
- Heap or Binary Heap (Priority Queue)

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
 
