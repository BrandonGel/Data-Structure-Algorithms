# DSA1

Descriptions
-
Making a singly-linked list with stacks and queues for integer, double, and string.


User Instructions
-
The program prompts the user for the name of an input text file and an output text file. 

Technical Details
-
*Look at the word document for more specific details of the program*

An abstract base class called SimpleList that provides some aspects of singly linked list functionality is created. The base class includes protected member functions that provide the ability to insert a node at the start of the list, to insert a node at the end of the list, and to remove a node from the start of the list. A private nested class called Node, which contains one field for data (data type value) and another field to point to the next node.  The base class includes a private data member to store the name of the list and a public member function to retrieve it. The base class also includes two public pure virtual member functions for push and pop which are in derived classes. Each of the virtual functions is implemented as one-line member function that calls the appropriate member function of the base class (to insert at the start or end of the list, or to remove from the start of the list).

Two derived classes of SimpleList named Stack and Queue are created. Templates are used for stacks/queues with varying data types: integer, double, string.

Header and tail nodes are implemented at the start and end of each list respectively.

Programming Implementation:
- Linked list
  - Stacks
  - Queues
  
SimpleList (Linked List) class contains the following:
- Private
  - Node Class
    - Public
      - getData
      - getNext (get the pointer of the next node)
      - setNext (set the pointer of the current node)
- Public
  - Push
  - Pop
  - getName (get the name of the SimpleList)
  - isEmpty (check if the SimpleList is empty)
 - Protected
  - insertStart
  - insertEnd
  - remove
  - getHead (get the header node)
  - getTail (get the tail node)

The constructor of SimpleList initialize the head and tail node and its name.

Derived Classes
- Stacks
- Queues

Non-SimpleList Template Functions:
- To search for a SimpleList with a specified name, Worst-case O(N)
- To print the pushed value
- To print the popped value 

The input file contains a list of commands, one per line. Each command will direct the program to create a stack or a queue, to push a value onto a stack or a queue, or to pop a value from a stack or a queue.

Input File Specifications:
- must contain one command per line
- The command must consist of two or three words, depending on the type of command, separated by single spaces. The line must have no leading whitespace before the first word or trailing whitespace after the last word. For the purposes of this assignment, a "word" is defined to be a sequence of letters and digits, except for words representing values of integers or doubles, which might also contain a single negative sign, and/or in the case of doubles, a single decimal point.
-  All commands (i.e., all lines in the text file) will end with a single Unix-style newline character ('\n').
- The first word of each command must be "create", "push", or "pop" (all lowercase letters). The second word must be a valid name for a stack or a queue. The first character of every name must be one of 'i', 'd', or 's' (all lowercase), standing for integer, double, or string; this represents the data type that is stored in the particular stack or queue. The rest of the name must consist of only letters and digits. Both uppercase and lowercase letters are allowed, and the program should be case sensitive.
- *All commands in the input file will be valid!*

Input File Commands Specifications:
-"create": there must be a third word that will be either "stack" or "queue" (all lowercase letters). This represents the type of list being created. No two lists may have the same name. However, two lists storing different data types (e.g., one list storing integers and another storing strings) may have the same name other than the first characters (in this case, 'i' or 's'). There cannot be a stack and a queue of the same data type that share the same name.
-"push": there must be a third word representing a value to be pushed onto the stack or queue. This value must match the appropriate type of the specified stack or queue, and it must fit into a single variable (e.g., an integer will fit in a 32-bit signed int); if the value is a string, it must be a single word, as defined above (i.e., containing only letters and digits).
- "pop": there must not be a third word.


Output file Specifications:
- After each command is read, your program should output the string "PROCESSING COMMAND: " followed by the text of the command and then a single Unix-style newline character.
- One space in between the ':' and text of the command. All output should be written to the specified output file.

Output File Commands Specifications:
- If the command is a "create" command, and:
  - the name of the stack/queue that is specified has already been created, the program outputs the string "ERROR: This name already exists!".
  - the name is new, the stack/queue is created, and no additional output is be written.
- If the command is a "push" command, and:
  - the specified name does not exist, the program outputs the string "ERROR: This name does not exist!".
  - the stack or queue does exist, the push operation is applied, and no additional output is be written.
- If the command is a "pop" command, and:
  - the specified name does not exist, the program outputs the string "ERROR: This name does not exist!".
  - the stack/queue does exist, but it is empty, the program outputs the string "ERROR: This list is empty!". 
  - the stack/queue does exist and is not empty, the pop operation is applied, and the program should output "Value popped: " followed by the value that is popped from the stack or queue.  


