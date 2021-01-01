# Sorting People
Sorting Names and SSN

Descriptions
-
Efficiency sort the people based on last name, then first name, and finally Social Security Number (SSN)


User Instructions
-
The program prompts the user for the name of the input file.  Then the program displays the CPU time to sort the text file and asks the user for the output file name.  Finally, the program write the sorted output file.
- T#.txt are the input files (look below for more information)
- CT#.txt are the sorted and correct file for T#.txt respectively

Technical Details
-
*Look at the word document for more specific details of the program*

The program will load data from an input file specified by the user and create a linked list of pointers to data objects using the provided C++ list class. Each data object will consist of three C++ string fields which store the last name, first name, and Social Security Number (SSN) of a hypothetical person. The last names have been chosen randomly from a set of the 500 most common last names according to the 2010 U.S. census. The first names have been chosen randomly from a set of the 250 most common male names and the 250 most common female names in the U.S. between 2010 and 2017.  The ssns have been randomly generated and have the format ddd-dd-dddd, where each character 'd' represents a digit. (Within each dataset, ssns are guaranteed to be unique.)

After creating the list, the program sorts the list. Items are be sorted according to last names; if last names are identical, they are be sorted according to first names; if both last and first names are identical, they are sorted according to SSN (which are guaranteed to be unique). The sorted list is then be written to an output file. 

Programming Implementation:
- Linked list
- Sorting Algorithms
  - quick sort
  - insertion sort
  - selection sort
  - radix sort

Input/Output file Specifications:
- The input and output files will have the same format.
- The first row will be an integer indicating how many rows follow. Each row after that represents a single data object, including a last name, first name, and ssn, separated by single spaces. 
- There will be no leading or trailing whitespace, and each row will be followed by a Unix-style newline character ('\n').


T1-T4 file Specification:
- T1 will contain approximately (within 1 percent of) 100,000 data objects. Each data object will store a randomly selected last name, a randomly selected first name, and a randomly generated social security number (ssns are guaranteed to be unique within T1).
- T2 will contain approximately (within 1 percent of) 1,000,000 data objects. Each data object will store a randomly selected last name, a randomly selected first name, and a randomly generated social security number (ssns are guaranteed to be unique within T2).
- T3 will contain the same data objects as T2, but they have already been sorted according to last names and first names (but not according to social security numbers).
- T4 will contain approximately (within 1 percent of) 1,000,000 data objects. Each data object will store the same last name and the same first name (both selected randomly, but only once), and a randomly generated social security number (ssns are guaranteed to be unique within T4).


