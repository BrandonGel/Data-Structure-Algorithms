# Spell-Check
Descriptions
-
Use a dictionary and check for any invalid/long words in another file


User Instructions
-
The program prompts the user for the name of the dictionary file, the name of the document file to be spell-checked, and the name of the output file. The program indicate how long, in seconds, it takes to read the dictionary and how long it takes to spell check the text file, measured in terms of CPU time.
- small.txt is a sample dictionary file
- lyrics.txt is a sample input file to be spell-checked
- out.txt is the correct output file for lyrics.txt

Technical Details
-
*Look at the word document for more specific details of the program*

A program that uses a hash table class to read in a "dictionary" and spell check a "document". For the purposes of this assignment, a valid word is defined as any sequence of valid characters, and the valid characters are letters (capital and lowercase), digits (0 - 9), dashes (-), and apostrophes ('). Every other character is considered a word
separator.

A dictionary is defined as a list of recognized words. The dictionary does not specify the meanings of words; it just lists them.

Programming Implementation:
- Hashtable

Hashtable class contains the following PRIVATE functions:
- insert
- find/contain
- hash
- rehash
- getPrime

The constructor of the hashtable class will use the getPrime function for getting a prime number as the capacity of the hashtable.

For collision resolution strategies, linear probing will be used.

The program is case insensitive, and all capital letters in both the dictionary and the document are be converted to lowercase immediately upon seeing them.

To process the dictionary, simply insert every word in the dictionary into the hash table. To spell check the document, locate every valid word in the document (keeping track of line numbers), and lookup (i.e., search for) each word in the hash table to see if it is recognized. An average dictionary contains about 50,000 words, but that some might be as large as 1,000,000 words. 


Dicitionary File Specifications:
- Each row exactly one word per line, with no leading or trailing spaces, followed by a single, Unix-style newline character (\n). 
- Some of the words in the dictionary might not be valid (i.e., they may contain invalid characters). 
- When loading the dictionary, invalid words, and also words that are too long are ignored. 
 
Input File Specification:
- Any text file
- Each line in the document will end with a single, Unix-style newline character (\n).

Output File Specificiation:
- Every unrecognized word in the input file will be displayed, including the line number on which it occurs. 
- Words should only be allowed to grow up to 20 characters. If a word in the document is too long, the program indicate the line number on which this occurs along with the first 20 characters of the word.
- Words in the document that include digits and other characters are ignored in the program. Every character that is not a valid word character is a word separator; e.g., the string "abc@def" represents two valid words, "abc" and "def". Therefore, there cannot be invalid words in the document.
