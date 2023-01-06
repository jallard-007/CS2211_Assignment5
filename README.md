# CS2211_Assignment5

To run the program from the command line, in the repository's root directory:

\$ make <br>
\$ ./sport

## Assignment overview

The 2211 Winter Olympics is fast approaching

## Purpose

This assignment will ask you to apply the following concepts from class:

Basic programming concepts
Intermediate concepts added in Assignment 4
Linked Lists and memory management
Makefiles
Program organization
Design

As before, each sporting event will be stored as a structure with the following attributes:

1. Event code (eg. 0, 1, 2, 3, 4, etc.)
   Each event code must be unique. There is no limit to the number of events but each code will be greater than or equal to 0
2. Event name (eg. "Single's figure skating", "Pair skating", "Curling", "Ice hockey", etc.)
   Only sports up to 50 characters in length are acceptable (including the null character - So think of this as 49+1)
3. Athlete/Team/Competitor count (eg. 10, 11, 12, 13, 14, etc.)
   Only integers 10-99 are acceptable
4. Gender (eg. "Men's", "Women's", and "Mixed" represented in your database as 'M', 'W', and 'X' respectively)
   Only the characters M, W, and X are acceptable

Now, you will also need to store each athlete as a structure with the following attributes:

1. Athlete code (eg. 0, 1, 2, 3, 4, etc.)
   Each event code must be unique. There is no limit to the number of athletes
2. Athlete name (eg. "John Smith", "Jane Doe", etc.)
   Only names up to 50 characters in length are acceptable (including the null character - So think of this as 49+1)
3. Athlete age (eg. 16, 17, 18, etc.)
   Only integers 16-99 are acceptable
4. Gender (eg. "Man", "Woman", and "Unidentified" represented in your database as 'M', 'W', and 'X' respectively))
   Only the characters M, W, and X are acceptable

Your program will then use a linked list of structures to represent all events and a linked list of structures to represent all athletes.

## Implementation

Your program should continuously prompt the user for one of four possible commands:

1. Print help (using command h)
   Print a simple message or messages describing how to use the program.
2. Quit (using command q)
   Quit the program
3. Control events (using command e)
   See below
4. Control athletes (using command a)
   See below

## Events

As in sport_db.c (Assignment 4) all the same commands exist as before:

1. Insert a new event (using command i)
   Prompt the user for the event code
   Assume the user will enter one integer
   This must be unique in your database and cannot conflict with an existing event code. If there is a conflict with an existing code, or if the database is full (you cannot allocate any more memory), tell the user the error and return to the beginning
   Prompt the user for the name of the event
   Assume the user will enter a string of characters of any length
   If the event name is longer than the acceptable length, you should accept as many characters as you can and ignore any additional characters
   Prompt the user for the number of competitors in this event
   Assume the user will enter one integer
   If the number is less than 10 or greater than 99, tell the user the error and return to the beginning
   Prompt the user for the gender of the event
   Assume the user will enter one character (followed by \n of course)
   If a value other than M, W, and X is entered, tell the user the error and return to the beginning
2. Search for an event in the database and print it out (using command s)
   Prompt the user for the event code
   If the event code is found, print out all the values for this event only (see the print command below for more details)
   If the event code is not found, tell the user the error and return to the beginning
3. Update an event in the database (using command u)
   Prompt the user for the event code
   If the event code is found, prompt the user to update all the values for the event (see the insert command above for details)
   If the event code is not found, tell the user the error and return to the beginning
4. Print the entire list of events (using command p)
   Print out a table listing all the events in your database with all the attributes:
   Event Code
   Event Name
   Competitors
   Gender
5. Erase event (ie. "Delete") (using command e)
   Prompt the user for the event code
   If the event code is found, erase the event safely by removing the element from the linked list and freeing the memory
   If the event code is not found, tell the user the error and return to the beginning

## Athletes

Implement the following commands:

1. Insert a new athlete (using command i)
   Prompt the user for the athlete code
   Assume the user will enter one integer
   This must be unique in your database and cannot conflict with an existing athlete code. If there is a conflict with an existing code, or if the database is full (you cannot allocate any more memory), tell the user the error and return to the beginning
   Prompt the user for the name of the athlete
   Assume the user will enter a string of characters of any length
   If the athlete name is longer than the acceptable length, you should accept as many characters as you can and ignore any additional characters
   Prompt the user for the age of the athlete
   Assume the user will enter one integer
   If the number is less than 16 or greater than 99, tell the user the error and return to the beginning
   Prompt the user for the gender of the athlete
   Assume the user will enter one character (followed by \n of course)
   If a value other than M, W, and X is entered, tell the user the error and return to the beginning
2. Search for an athlete in the database and print it out (using command s)
   Prompt the user for the athlete code
   If the athlete code is found, print out all the values for this athlete only (see the print command below for more details)
   If the athlete code is not found, tell the user the error and return to the beginning
3. Update an athlete in the database (using command u)
   Prompt the user for the athlete code
   If the athlete code is found, prompt the user to update all the values for the athlete (see the insert command above for details)
   If the athlete code is not found, tell the user the error and return to the beginning
4. Print the entire list of athletes (using command p)
   Print out a table listing all the events in your database with all the attributes:
   Athlete Code
   Athlete Name
   Age
   Gender
5. Erase athlete (ie. "Delete") (using command e)
   Prompt the user for the athlete code
   If the athlete code is found, erase the athlete safely by removing the element from the linked list and freeing the memory
   If the athlete code is not found, tell the user the error and return to the beginning

## Registration (optional)

For a 10% bonus, add a fifth command (h, q, e, a, and now r for Registration). Controlling registrations will accept all the same commands as events and athletes (i, s, u, p, and e) but it will use a new linked list of structures. Each structure will have the following elements:

Registration code (eg. 0, 1, 2, 3, 4, etc.)
Each registration code must be unique. There is no limit to the number of registrations
Event code (eg. 0, 1, 2, 3, 4, etc.)
Only codes found in the events list are acceptable
Athlete code (eg. 0, 1, 2, 3, 4, etc.)
Only codes found in the athletes list are acceptable

Therefore, if there is an entry in the registration linked list for event 12 and athlete 22, this means that athlete 22 is registered for event 12.
