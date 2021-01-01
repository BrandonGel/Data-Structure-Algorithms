# Spell-Check
Descriptions
-
uses bottom-up dynamic programming to efficiently solve the 1998 regional ACM Programming Contest. 
http://www.acmgnyr.org/year1998/prob_g.html


User Instructions
-
The program prompts the user for the name of the name of the document file to check for any valid merge and the name of the output file. 
in.txt is a sample dictionary file
out.txt is the correct output file for lyrics.txt

Technical Details
-
*Look at the word document for more specific details of the program*

The problem defines a "merge" of two strings as a third string containing all the characters from each of the original two strings mixed together. The two sets of characters can be interspersed, but the characters from each individual string cannot be permuted. 

The program will accept three strings at a time; we'll call them A, B, and C. All strings will consist of only lowercase letters. A and B will contain at most 1000 letters, and C will contain at most 2000 letters. The program determine whether or not C is a valid merge of A and B. If so, the program outputs C with the characters from A converted to uppercase. If more than one merge is possible, the letters of A should be made to occur as early as possible. If no merge is possible, the output file reads "*** NOT A MERGE ***".

Input/Output File Specifications:

The input file will consist of multiple sets of three strings, one string per line.  Every line in the input file will be, and every line in the output file should be, followed by a single Unix-style newline character.

Programming Implementation:
- Dynamic Programming (Bottom-up)

A global 2D matrix will be used where the rows represent the first word's character position, and the columns represent the second word'character position.
