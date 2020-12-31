// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2019

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


using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
	string lastName;
	string firstName;
	string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

	ifstream input(filename);
	if (!input) {
		cerr << "Error: could not open " << filename << "\n";
		exit(1);
	}

	// The first line indicates the size
	string line;
	getline(input, line);
	stringstream ss(line);
	int size;
	ss >> size;

	// Load the data
	for (int i = 0; i < size; i++) {
		getline(input, line);
		stringstream ss2(line);
		Data *pData = new Data();
		ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
		l.push_back(pData);
	}

	input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

	ofstream output(filename);
	if (!output) {
		cerr << "Error: could not open " << filename << "\n";
		exit(1);
	}

	// Write the size first
	int size = l.size();
	output << size << "\n";

	// Write the data
	for (auto pData : l) {
		output << pData->lastName << " "
			<< pData->firstName << " "
			<< pData->ssn << "\n";
	}

	output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);
void names(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
	string filename;
	cout << "Enter name of input file: ";
	cin >> filename;
	list<Data *> theList;
	loadDataList(theList, filename);

	cout << "Data loaded.\n";

	cout << "Executing sort...\n";

	clock_t t1 = clock();
	sortDataList(theList);
	clock_t t2 = clock();
	double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;

	cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

	cout << "Enter name of output file: ";
	cin >> filename;
	writeDataList(theList, filename);

	return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish
#define BITS 5

char y[11];

int b[1010000];
int tempSSN[1010000];

int mid, j, loc, p;
int m = 999000000;

typedef struct {
	char all[18] = "000000000";
	int ssn;
	Data *data;
} iData;

iData bin[1010000];  
//iData tempbin[1010000]; //For Mergesort
iData temp;


//For T4, a int LSB radixsort
void radixsort(int n)
{
	int i, pos = 0;
	int buckets = 1 << BITS;
	int mask = buckets - 1;
	int bucket[buckets];

	while ((m >> (pos*BITS)) > 0)
	{
		memset(bucket, 0, buckets * 4);
		for (i = 0; i < n; i++)
		{
			bucket[(tempSSN[i] >> (pos*BITS)) & mask]++;
		}
		for (i = 1; i < buckets; i++)
		{
			bucket[i] += bucket[i - 1];
		}
		for (i = n - 1; i >= 0; i--)
		{
			b[--bucket[(tempSSN[i] >> (pos*BITS)) & mask]] = tempSSN[i];
		}
		pos++;

		memset(bucket, 0, buckets * 4);

		for (i = 0; i < n; i++)
		{
			bucket[(b[i] >> (pos*BITS)) & mask]++;
		}
		for (i = 1; i < buckets; i++)
		{
			bucket[i] += bucket[i - 1];
		}
		for (i = n - 1; i >= 0; i--)
		{
			tempSSN[--bucket[(b[i] >> (pos*BITS)) & mask]] = b[i];
		}
		pos++;
	}
}

//insertionsort2 is slower than selectionsort
//For T1,T2, an insertionsort for SSN
/*
void insertionsort2(int low, int high)
{
	for (p = low; p < high; ++p)
	{
		j = p;
		temp = bin[p + 1];

		while (j >= low && bin[j].ssn > temp.ssn)
		{
			bin[j + 1] = bin[j];
			j--;
		}
		bin[j + 1] = temp;
	}
}
*/

//For T1,T2, insertionsort for names
void insertionsort(int low, int high)
{
	for (p = low; p < high; ++p)
	{
		j = p;
		temp = bin[p + 1];

		while (strcmp(bin[j].all, temp.all) > 0)
		{
			bin[j + 1] = bin[j];
			j--;
		}
		bin[j + 1] = temp;
	}
}

//For T1,T2, median of three, partition, and recursive quicksort for names
iData median(int low, int high)
{
	iData left = bin[low];
	iData right = bin[high];
	iData center = bin[(low + high) / 2];

	if ((strcmp(left.all, center.all) > 0))
	{
		temp = center;
		center = left;
		left = temp;
	}
	if ((strcmp(left.all, right.all) > 0))
	{
		temp = left;
		left = right;
		right = temp;
	}
	if ((strcmp(center.all, right.all) > 0))
	{
		temp = center;
		center = right;
		right = temp;
	}

	return bin[high];
}

int partition(int low, int high, iData pivot)
{
	int i = low;
	for (j = low; j < high; j++)
	{
		if (strcmp(bin[j].all, pivot.all) < 0)
		{
			temp = bin[i];
			bin[i] = bin[j];
			bin[j] = temp;
			i++;
		}

	}
	temp = bin[i];
	bin[i] = bin[high];
	bin[high] = temp;

	return i;
}

void quicksort(int low, int high)
{
	while (low < high)
	{
		if (high - low < 20)
		{
			insertionsort(low, high);
			break;
		}
		else
		{
			temp = median(low, high);
			int i = partition(low, high, temp);
			if (i - low < high - i)
			{
				quicksort(low, i - 1);
				low = i + 1;
			}
			else
			{
				quicksort(i + 1, high);
				high = i - 1;
			}
		}
	}
}

//For T1,T2, custom-made strcmp, return 0 if 2 string are equal and return 1 if 2 strings are not equal
int cmp(const char*p1, const char*p2)
{
	const unsigned char *s1 = (const unsigned char *)p1;
	const unsigned char *s2 = (const unsigned char *)p2;
	unsigned char c1, c2;

	for (int i = 0; i < 2; i++)
	{
		c1 = (unsigned char)*s1++;
		c2 = (unsigned char)*s2++;
		if (c1 != c2)
			return 1;
	}

	do
	{
		c1 = (unsigned char)*s1++;
		c2 = (unsigned char)*s2++;
		if (c1 == '\0')
			break;
	} while (c1 == c2);

	if (c1 != c2)
	{
		return 1;
	}
	return 0;
}

// mergesort is slighty slower than quicksort
/*
void merge(int low, int mid, int high) {
	int l1, l2, i;

	for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
		if (strcmp(bin[l1].all,bin[l2].all) <= 0)
			tempbin[i] = bin[l1++];
		else
			tempbin[i] = bin[l2++];
	}

	while (l1 <= mid)
		tempbin[i++] = bin[l1++];

	while (l2 <= high)
		tempbin[i++] = bin[l2++];

	for (i = low; i <= high; i++)
		bin[i] = tempbin[i];
}

void mergesort(int low, int high)
{
	if (low < high) {
		int mid = (low + high) / 2;
		mergesort(low, mid);
		mergesort(mid + 1, high);
		if(strcmp(bin[mid].all,bin[mid+1].all) > 0)
			merge(low, mid, high);
	}
}
*/


// Total 1.096583
void sortDataList(list<Data *> &l)
{
	int i = 0;

	auto it = l.begin();  //iterator(1) at begining of the list
	auto sec = l.begin();
	advance(sec, 1); //iterator(2) after the iterator(1)

	auto beg = l.begin(); //iterator at begining of the list
	auto end = l.end();  //iterator at item after the end of the list

	auto front = l.front();  //reference to the begining of the list
	auto back = l.back(); //reference to the end of the list

	//T4
	//---------------------------------------------------------
	//Description: Only one unique first and last name with unique SSN
	//# of Items: 1 millions +/- (<10,000)
	//Time: : 0.192969 sec

	if (front->firstName == back->firstName && front->lastName == back->lastName)
	{
		//stores the items' SSN (from string to int) into an int array
		for (; it != end; it++, i++)
		{
			memmove(y, (*it)->ssn.c_str(), 11);
			tempSSN[i] = (100000000 * (y[0] - '0') + 10000000 * (y[1] - '0') + 1000000 * (y[2] - '0') + 100000 * (y[4] - '0') + 10000 * (y[5] - '0') + 1000 * (y[7] - '0') + 100 * (y[8] - '0') + 10 * (y[9] - '0') + (y[10] - '0'));
		}

		radixsort(i);

		//put the sorted SSN (from int to string) back to the list
		for (it = beg, i = 0; it != end; it++, i++)
		{
			(*it)->ssn = { (char)((tempSSN[i] / 100000000) + '0'),(char)(((tempSSN[i] / 10000000) % 10) + '0'),(char)(((tempSSN[i] / 1000000) % 10) + '0'),'-',(char)(((tempSSN[i] / 100000) % 10) + '0'),(char)(((tempSSN[i] / 10000) % 10) + '0'),'-',(char)(((tempSSN[i] / 1000) % 10) + '0'),(char)(((tempSSN[i] / 100) % 10) + '0'),(char)(((tempSSN[i] / 10) % 10) + '0'),(char)(((tempSSN[i]) % 10) + '0') };
		}

	}
	//T3
	//---------------------------------------------------------
	//Description: Sorted and different last and first names with unique SSN
	//# of Items: 1 millions +/- (<10,000)
	//Time: 0.239675 sec

	else if ((*it)->lastName == (*sec)->lastName) 
	{
		//stores the first item SSN (from string to int) and Data class item into iData array
		memmove(y, (*it)->ssn.c_str(), 11);
		bin[i].ssn = (100000000 * (y[0] - '0') + 10000000 * (y[1] - '0') + 1000000 * (y[2] - '0') + 100000 * (y[4] - '0') + 10000 * (y[5] - '0') + 1000 * (y[7] - '0') + 100 * (y[8] - '0') + 10 * (y[9] - '0') + (y[10] - '0'));
		bin[i++].data = *it;

		int g = 0;
		int min, z, x;
		auto correct = beg;

		for (; sec != end; it++, sec++, i++)
		{
			//stores the rest of the items' SSN (from string to int) and Data class item into iData array
			memmove(y, (*sec)->ssn.c_str(), 11);
			bin[i].ssn = (100000000 * (y[0] - '0') + 10000000 * (y[1] - '0') + 1000000 * (y[2] - '0') + 100000 * (y[4] - '0') + 10000 * (y[5] - '0') + 1000 * (y[7] - '0') + 100 * (y[8] - '0') + 10 * (y[9] - '0') + (y[10] - '0'));
			bin[i].data = *sec;

			if ((*it)->firstName != (*sec)->firstName)
			{
				//selection Sort
				for (x = g; x < i; x++, correct++)
				{
					min = x;
					for (z = x + 1; z < i; z++)
						if (bin[z].ssn < bin[min].ssn)
							min = z;

					temp = bin[min];
					bin[min] = bin[x];
					bin[x] = temp;

					*correct = bin[x].data; //put the sorted item back to the list
				}
				g = i;
			}
		}
	}
	// T1 & T2
	//---------------------------------------------------------
	//Description: randomly orderd first and last names with unique SSN
	//# of Item s(T1): 1 millions +/- (<10,000)
	//# of Items (T2): 100,000 +/- (<1,000)
	//Time(T1): 0.0623 sec
	//Time(T2): 0.61668 sec
	else 	
	{
		//concatenate the first and last names and stores the concatenated name into iData array
		//stores the rest of the items' SSN (from string to int) and Data class item into iData array
		for (; it != end; i++, it++)
		{
			memmove(bin[i].all, (*it)->lastName.c_str(), (*it)->lastName.length()); //the first nine characters will not have any null character if last name is less than 9 characters because the first 9 characters of char all[18] are already initialized 
			memmove(bin[i].all + 9, (*it)->firstName.c_str(), 9);  //no need to worry if the first name is less than 9 characters
			memmove(y, (*it)->ssn.c_str(), 11);

			bin[i].ssn = (100000000 * (y[0] - '0') + 10000000 * (y[1] - '0') + 1000000 * (y[2] - '0') + 100000 * (y[4] - '0') + 10000 * (y[5] - '0') + 1000 * (y[7] - '0') + 100 * (y[8] - '0') + 10 * (y[9] - '0') + (y[10] - '0'));
			bin[i].data = *it;
		}

		//mergesort(0, i - 1);

		quicksort(0, i - 1);  //Sort the names into how T3 was made

		int g = 0;
		int u = 0;

		/*
		for (; u < i; u++)
		{
			if (strcmp(bin[u].all, bin[u + 1].all) != 0)
			{
				insertionsort2(g, u);
				g = u + 1;
			}
		}
		insertionsort2(g, i);

		for (it = l.begin(), i = 0; it != end; it++, i++)
		{
			*it = bin[i].data;
		}
		*/
		///*
		int min, z, x;
		auto correct = beg;

		for (; u < i; u++)
		{
			if (strcmp(bin[u].all + 9, bin[u + 1].all + 9) != 0)  //check if the current and next names are the same if so expand the range of current names if not sort the current names within that range
			{
				//Selection Sort for SSN
				for (x = g; x < u + 1; x++, correct++)
				{
					min = x;
					for (z = x + 1; z < u + 1; z++)
						if (bin[z].ssn < bin[min].ssn)
							min = z;

					temp = bin[min];
					bin[min] = bin[x];
					bin[x] = temp;

					*correct = bin[x].data;	//put the sorted item back to the list
				}
				g = u + 1;
			}
		}
		//*/
	}
}