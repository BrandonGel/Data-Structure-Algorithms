#include "hash.h"
#include "heap.h"

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <vector>

#define help() (std::cout << "help" << std::endl)

int prime[38] = { 503,557,601,653,701,751,809,853,907,953,1009,1051,1103,1151,1201,1259,1301,1361,1423,1471,1523,1571,1621,1693,1741,1801,1861,1913,1973,2027,2081,2131,2203,2251,2309,2351,2411,2467 };

hashTable::hashTable(int size)
{	
	capacity = getPrime(size);  // Hashtable's capacity is set to the least prime number greater than it from the prime array above
	filled = 0;	// Set the number of objects in the hashtable to 0
	data.resize(capacity);  // Set the size of the hash table
}


int hashTable::insert(const std::string &key, void *pv)
{
	// When hash table is above half-capacity, rehash
	// Return 2 if rehashing fails
	if (capacity / 2 <= filled)
	{
		if (!rehash())
			return 2;
	}

	// Find if the key exists in the hashtable and check for any lazy deletion
	// Return 1 if found
	int h = hash(key);
	while ((data[h].isOccupied == true) || (data[h].isDeleted == true))
	{
		if (data[h].key == key)
			return 1;
		h = (h + 1) % capacity;
	}

	//Insert a new object into the hash table 
	data[h].key = key;
	data[h].isOccupied = true;
	data[h].pv = pv; // Point to the node of the ID in the heap
	filled++; // Number of objects in the hashtable increases by 1
	return 0;
}

bool hashTable::contains(const std::string &key)
{
	//h is the position of the key in hashtable
	//h is not -1 means key is in hashtable
	int h = findPos(key);
	if (h != -1) 
	{
		return true;
	}
	return false;
}

void* hashTable::getPointer(const std::string &key, bool *b)
{
	//h is the position of the key in hashtable
	//h is not -1 means key is in hashtable
	int h = findPos(key);
	if (h != -1)	
	{
		*b = 1; //let the user know that hashitem is in the hashtable regardless a null pointer is returned
		return data[h].pv;
	}
	*b = 0; //let the user know that hashitem isn't in the hashtable, so a null pointer is returned
	return nullptr;
}

int hashTable::setPointer(const std::string &key, void *pv)
{
	//h is the position of the key in hashtable
	//h is not -1 means key is in hashtable
	int h = findPos(key);
	if (h != -1)
	{
		data[h].pv = pv;  // Assign a new pointer to a node in the heap in the hashitem with the given key
		return 0;
	}
	return 1;
}


bool hashTable::remove(const std::string &key)
{
	//h is the position of the key in hashtable
	//h is not -1 means key is in hashtable
	int h = findPos(key);
	if (h != -1)  
	{
		data[h] = hashItem();	//Clear the hashitem
		data[h].isDeleted = true;  //lazy deletion
		return true;
	}
	return false;
}

// Found Online: https://www.cs.princeton.edu/courses/archive/fall05/cos226/lectures/hash.pdf
int hashTable::hash(const std::string &key)
{
	//Set the position of the key in the hashtable
	unsigned int h = 7;
	for (int i = 0; i < key.length(); i++) 
		h = h*31 + key[i];
	h %= capacity; //Added this to prevent h from going over the size of the hashtable
	return h;
}

int hashTable::findPos(const std::string &key)
{
	//Get the position of the key in hashtable
	int h = hash(key);
	
	// Find if the key exists in the hashtable and check for any lazy deletion
	// Return h if found
	while ((data[h].isOccupied == true) || (data[h].isDeleted == true))
	{
		if (data[h].key == key)
			return h;
		h = (h + 1) % capacity; // Check the next index 
	}
	return -1;
}

bool hashTable::rehash()
{
	//Create a second hashtable to hold the listed words from first hashtable
	std::vector<hashItem> old = data;
	int ocapacity = capacity;

	//Clear the first hashtable and expanded its capacity
	data.clear();
	capacity = getPrime(2 * capacity);
	filled = 0;
	data.resize(capacity);

	//Place all the listed words from the second hashtable to the first hashtable
	try
	{
		for (int i = 0; i < ocapacity; i++)
			if (old[i].isOccupied)
				insert(old[i].key);
	}
	catch (std::bad_alloc& e)
	{
		return false;
	}
	return true;
}


 unsigned int hashTable::getPrime(int size)
{
	 //Get the next biggest prime number greater than the hashtable size
	for (int x : prime)
		 if (size < x)
			 return x;
}


