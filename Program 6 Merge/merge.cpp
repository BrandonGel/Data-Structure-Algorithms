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

//#define help() (cout << "help" << endl)  //for debugging
int arr[1001][1001];

void load(string in, string out)
{
	ifstream input(in);	//Open Input File
	if (!input) {
		cerr << "Error: could not open " << in << "\n"; // If Input File Failed
		exit(1);
	}

	ofstream output(out);	//Open Output File
	if (!output) {
		cerr << "Error: could not open " << out << "\n"; // If Output File Failed
		exit(1);
	}

	while (!input.eof())
	{
		// Get the first two word and merged word
		string A, B, C;
		getline(input, A);
		if (A == "")
			break;
		getline(input, B);
		getline(input, C);

		// The words' length
		int lenA = A.length();
		int lenB = B.length();
		int lenC = C.length();

		// Proceed if the lengtht of the first two words equal to the merged word
		if (lenA + lenB == lenC)
		{
			// Initalize the array lenA+1 by lenB+1 to be -1
			for (int i = 0; i < lenA + 1; i++)
			{
				for (int j = 0; j < lenB + 1; j++)
				{
					arr[i][j] = -1;
				}
			}

			// Check for the starting point
			if (A[0] == C[0])
			{
				arr[1][0]++;
			}
			if (B[0] == C[0])
			{
				arr[0][1]++;
			}

			// Fill in the data entries
			for (int i = 0; i < lenA + 1; i++)
			{
				for (int j = 0; j < lenB + 1; j++)
				{
					if (arr[i][j] == -1)
					{
						continue;
					}
					if (C[arr[i][j] + 1] == A[i])
					{
						arr[i + 1][j] = arr[i][j] + 1;
					}
					if (C[arr[i][j] + 1] == B[j])
					{
						arr[i][j + 1] = arr[i][j] + 1;
					}
					
				}
			}

			// Backtracking to see if the merged word is a valid merge
			if (arr[lenA][lenB] != -1)
			{
				lenC--;
				while (lenC > -1)
				{
					lenC--;
					if (arr[lenA][lenB - 1] == lenC && lenB > 0)
					{
						lenB--;
					}
					else
					{
						C[lenC + 1] = toupper(C[lenC + 1]);
						lenA--;
					}
				}
				output << C << endl;
			}
			else
			{
				output << "*** NOT A MERGE ***" << endl;
			}

		}
		else
		{
			output << "*** NOT A MERGE ***" << endl;
		}
	}
	output.close();
}

int main()
{
	string in, out;

	// Input File
	cout << "Enter name of input file: ";
	cin >> in;
	cout << "Enter name of output file: ";
	cin >> out;

	load(in, out);	//Loading Input and Output File 

	return 0;
}