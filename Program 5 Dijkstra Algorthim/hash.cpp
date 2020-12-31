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

//Array of prime numbers
int prime[215] = { 25013, 30011, 35023, 40009, 45007, 50021, 55001, 60013, 65003, 70001, 75011, 80021, 85009, 90001, 95003, 100003, 105019, 110017, 115001, 120011, 125003, 130003, 135007, 140009, 145007, 150001, 155003, 160001, 165001, 170003, 175003, 180001, 185021, 190027, 195023, 200003, 205019, 210011, 215051, 220009, 225023, 230003, 235003, 240007, 245023, 250007, 255007, 260003, 265003, 270001, 275003, 280001, 285007, 290011, 295007, 300007, 305017, 310019, 315011, 320009, 325001, 330017, 335009, 340007, 345001, 350003, 355007, 360007, 365003, 370003, 375017, 380041, 385001, 390001, 395023, 400009, 405001, 410009, 415013, 420001, 425003, 430007, 435037, 440009, 445001, 450001, 455003, 460013, 465007, 470021, 475037, 480013, 485021, 490001, 495017, 500009, 505027, 510007, 515041, 520019, 525001, 530017, 535013, 540041, 545023, 550007, 555029, 560017, 565013, 570001, 575009, 580001, 585019, 590021, 595003, 600011, 605009, 610031, 615019, 620003, 625007, 630017, 635003, 640007, 645011, 650011, 655001, 660001, 665011, 670001, 675029, 680003, 685001, 690037, 695003, 700001, 705011, 710009, 715019, 720007, 725009, 730003, 735001, 740011, 745001, 750019, 755009, 760007, 765007, 770027, 775007, 780029, 785003, 790003, 795001, 800011, 805019, 810013, 815029, 820037, 825001, 830003, 835001, 840023, 845003, 850009, 855031, 860009, 865001, 870007, 875011, 880001, 885023, 890003, 895003, 900001, 905011, 910003, 915007, 920011, 925019, 930011, 935003, 940001, 945031, 950009, 955037, 960017, 965023, 970027, 975011, 980027, 985003, 990001, 995009, 1000003, 1005007, 1010003, 1015009, 1020001, 1025009, 1030019, 1035007, 1040021, 1045003, 1050011, 1055017, 1060009, 1065011, 1070009, 1075007, 1080007, 1085003, 1090003, 1095023 };

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
	//std::cout << h << std::endl;
	
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
		//help();
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
	// Find if the key exists in the hashtable and check for any lazy deletion
	// Return h if found
	int h = hash(key);
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
			if (old[i].isOccupied && !old[i].isDeleted)
				insert(old[i].key, old[i].pv);
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


