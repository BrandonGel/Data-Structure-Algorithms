#include "heap.h"

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#define help() (std::cout << "help" << std::endl)


heap::heap(int capacity) :mapping(capacity * 2)
{
	// Allocate space for the nodes (0 slot is not used)
	data.resize(capacity + 1);
	heap::capacity = capacity;
	filled = 0;
}


int heap::insert(const std::string &id, int key, void *pv)
{

	if (capacity == filled) // If full
		return 1;
	else if (mapping.contains(id)) // If Id found
		return 2;

	mapping.insert(id);  //add the id string to the hash table

	//Restructure the heap to have the inserted item
	data[0].id = id;
	data[0].key = key;
	data[0].pData = pv;
	int hole = ++filled;
	percolateUp(hole);

	return 0;
}

int heap::setKey(const std::string &id, int key)
{
	//If no Id found
	if (!mapping.contains(id))
		return 1;
	bool b; //an indicator if the key is in the hashtable 
	node *pn = static_cast<node*> (mapping.getPointer(id, &b)); // get the pointer to the node containing the string Id
	int pos = getPos(pn); //get the position of the node in the vector
	int pk = (*pn).key;  //getting the original key value 
	(*pn).key = key;	//assigning the new key value

	if (pk > key) //compare the original and new key value 
	{
		data[0] = std::move(*pn);
		percolateUp(pos);
	}
	else if (pk < key)
		percolateDown(pos);

	return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
	// If empty
	if (filled == 0)
		return 1;

	//If the followings aren't null pointers, then assigns the root value to the followings

	if (pId != nullptr) 
	{
		*pId = data[1].id;
	}
	if (pKey != nullptr) 
	{
		*pKey = data[1].key;
	}
	if (ppData != nullptr) 
	{
		*(static_cast<void **> (ppData)) = data[1].pData;
	}

	//Remove the root value from the hash tables and heap
	mapping.remove(data[1].id);
	data[1] = std::move(data[filled--]);
	percolateDown(1); //Restructure the heap 
	return 0;
}


int heap::remove(const std::string &id, int *pKey, void *ppData)
{
	// If Id not found
	if (!mapping.contains(id))
		return 1;

	bool b; //check if the key is in the hashtable 
	node *pn = static_cast<node *> (mapping.getPointer(id, &b)); // get the pointer to the node containing the string Id
	int pos = getPos(pn);  // get the position of the pointer to the node containing the string Id

	//If the followings aren't null pointers, then assigns the root value to the followings
	if (pKey != nullptr)
	{
		*pKey = data[pos].key;
	}
	if (ppData != nullptr)
	{
		*(static_cast<void**>(ppData)) = data[pos].pData;
	}

	setKey(id, data[1].key-1);
	deleteMin();

	return 0;
}

void heap::percolateUp(int posCur)
{
	//Loop and move the inserted item up on the heap
	//if the inserted item < value of the node at the current height
	for (; data[0].key < data[posCur / 2].key; posCur /= 2)
	{
		data[posCur] = std::move(data[posCur / 2]);
		mapping.setPointer(data[posCur].id, &data[posCur]);
	}
	data[posCur] = std::move(data[0]);
	mapping.setPointer(data[posCur].id, &data[posCur]);
}


void heap::percolateDown(int posCur)
{
	//Loop and move the inserted item down on the heap
	//if the inserted item >= value of the node at the current height
	int child;
	node tmp = std::move(data[posCur]);
	for (; posCur * 2 <= filled; posCur = child)
	{
		child = posCur * 2;
		if (child != filled && data[child + 1].key < data[child].key )
			++child;
		if (data[child].key < tmp.key)
		{
			data[posCur] = std::move(data[child]);
			mapping.setPointer(data[posCur].id, &data[posCur]);
		}
		else
			break;
	}
	data[posCur] = std::move(tmp);
	mapping.setPointer(data[posCur].id, &data[posCur]);
}

int heap::getPos(node *pn)
{
	int pos = pn - &data[0];  //Calculate the position of the indicated node
	return pos;
}