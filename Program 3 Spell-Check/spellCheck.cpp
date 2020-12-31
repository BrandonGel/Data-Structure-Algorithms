#include "hash.h"

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
int n = 25000;
hashTable *ht = new hashTable(n);
string acc = "abcdefghijklnmopqrstuvwxyz-\'1234567890";
int lim = acc.length();


//Loading Dictionary into Hash Table
void loadDict(const string &filename)
{
	ifstream input(filename); //Open Dictionary File
	if (!input) {
		cerr << "Error: could not open " << filename << "\n";  //If Dictionary File Failed
		exit(1);
	}

	string line;
	for (int i = 0; !input.eof(); i++)   //Loading the Dictionary into the Hash Table
	{
		getline(input, line);
		int j = 0;
		for (int j = 0; j < line.length(); j++)
			line[j] = tolower(line[j]);
		int x = ht->insert(line);
	}

	input.close();  //Close Dictionary File
}


void check(const string &filename, const string &out)
{

	ifstream input(filename); //Open Input File
	if (!input) {
		cerr << "Error: could not open " << filename << "\n"; // If Input File Failed
		exit(1);
	}

	ofstream output(out);	//Open Output File
	if (!output) {
		cerr << "Error: could not open " << out << "\n"; // If Output File Failed
		exit(1);
	}


	string line;
	for (int i = 1; !input.eof(); i++)
	{
		getline(input, line);
		int len = line.length();

		int oj = 0;  // Position of first character of a word
		int j = 0;  // Position of the current character of the word
		int dig = 0;  // if there is a digit in a word, then dig = 1

		while ((len != 0) && (j <= len))
		{
			line[j] = tolower(line[j]);  // Lowercase all the characters in the line

			int l = 0; // The index of acc[]
			for (; l < lim; l++) // Find if there a word seperator
			{
				if (line[j] == acc[l])
				{
					if (l > 27)  // acc[28], acc[29], ..., acc[37] are digits
						dig = 1;
					break;
				}
			}

			if (l == lim)  //Check if there is a word seperator
			{
				string ss = line.substr(oj, j - oj);  //get the word based on the character position in the line

				if (j != oj && dig == 0)  // make sure that the word isn't a word seperator or there is any digit in the word
				{
					if (ss.length() > 20)	//Check if the word is greater than 20 characters
					{
						output << "Long word at line " << i << ", starts: " << ss.substr(0, 20) << endl;
					}
					else if (!ht->contains(ss))		//Check if the word is not in the Hash Table or contains a digit
					{
						output << "Unknown word at line " << i << ": " << ss << endl;
					}
				}
				oj = j + 1; //Update the oj position to the first character of the next word
				dig = 0; //Reset dig to 0 for the next word on the line
			}
			j++;  //Update the current position of j to the next character of the word
		}


	}
	output.close();
}

int main()
{
	string filename, out;

	//Dictionary File Input	
	cout << "Enter name of dictionary : ";
	cin >> filename;

	//Dictionary Hashtable Time
	clock_t t1 = clock();
	loadDict(filename);		//Loading Dictionary
	clock_t t2 = clock();
	double timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;  // Time Take to Load Dictionary
	cout << "Total time(in seconds) to load dictionary : " << timeDiff << endl;

	//Input and Output File
	cout << "Enter name of input file : ";
	cin >> filename;
	cout << "Enter name of output file: ";
	cin >> out;

	t1 = clock();
	check(filename, out);  //Check the Input File and Create the Output in Output File
	t2 = clock();
	timeDiff = ((double)(t2 - t1)) / CLOCKS_PER_SEC;	// Time Take to do the check Function
	cout << "Total time(in seconds) to check document : " << timeDiff << endl;
	return 0;
}

