# DSA1
Making a singly-linked list with stack and queues

This project was given by my professor.  Given a text file with certain commands on making either a stack or queue with a type of int, double ,or string, pushing a value into that list, and poping a value out of the list.  

The commands for making a new list must have the word "create" in the beginning. Then it must have either "i" for int, "d" for double, or "s" for string for the beginning of the list and an unique name for the list. Finally it must have either "stack" or "queue".  
In creating a list with an unique name, print out "Processing Command" and then create command.

EX: "create i1 queue" => "PROCESSING COMMAND: create i1 queue".

If not, print out "ERROR: This name already exists!". 

EX: "create i1 queue" => "PROCESSING COMMAND: create i1 queue" =>  "\nERROR: This name already exists!".

The commands for pushing a value into a list must have the word "push" in the beginning.  Then it must have the name of the list created before.  Finally it must have a value to be push into the list.

In pushing a value in a list , print out "Processing Command:" and then push command.

EX: "push i1 50" => "PROCESSING COMMAND: push i1 50".

If the name of the list was not created, then print "ERROR: This name does not exist!".

EX: "push dHelloWorld 50" => "PROCESSING COMMAND: push dHelloWorld 50" => "\nERROR: This name does not exist!".

The commands for popping a value out of a list must have the word "pop" in the beginning.  Finally it must have the name of the list created before.
In popping a value in a list , print out "Processing Command:", then pop command, and finally "Value popped" plus the value.

EX: "pop sR2D2" => "PROCESSING COMMAND: pop sR2D2" => "\nValue popped: 123abcDEF".

If the name of the list was not created, then print "ERROR: This name does not exist!".

EX: "pop i2" => "PROCESSING COMMAND: pop i2" => "\nERROR: This name does not exist!".

If the list is empty, then print out "ERROR: This list is empty!".

EX:"pop dHelloWorld" => "PROCESSING COMMAND: pop dHelloWorld" => "ERROR: This list is empty!".



Text.cpp is a final version that I used as test file before making another version to be submitted for grading.
dsa1prog1.cpp is the final version that I sent to my professor for grading.
programfinal.cpp is a file created my friend who allowed me to look at and share with
input#.txt is the test file sent by my professor us to test our program
output.txt is the correct ouptut file sent by my professor for the input.txt

