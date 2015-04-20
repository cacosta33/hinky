/* 
Name: Cesar Acosta
Date: 11/29/14
Class: CSCI 1730
Instructor: Maria Hybinette
Purpose: In this assignment you will write a variation of hangman. 
Here, your program will take the place of one of the players in the game. 
The twist is that this program will not select one particular word 
(specified by dashes), but instead the program cheats by adaptively dodging 
the opposing player's guesses, and keep track of a set of possible words 
instead of a particular one word. The 'program' will maintains a list of 
words in the English language, and as the opposing player guess letters 
it will continuously pares down the word list to try to dodge the player's 
guesses as much as possible.
*/

#include <iostream>	/* Contains the standard cout and cin functions */
#include <fstream>	/* Includes ifstream(read) and ofstream(write) */
#include <stdlib.h>	/* Includes the definition for NULL and other error handling */
#include <cstdlib>	/* Includes rand() */
#include <cstring>	/* Includes the library necessary for using strings */

//The following down below are for the trimming method
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;	//To shorten cout and cin

int GUESSES = 10;	//Number of initial guesses for player

//Global array that will constantly change itself
string *dictionaryList;	//	Contains the initial words
int arraySize;			//	Size of initial array
string changingWord;	//	This word will NOT be constant
int notShrinking=0;		//	When the dictionary doesn't shrink anymore

struct usedLetters{		//Contains the letters already entered by user
	char letter;
	usedLetters *next;
};

/* Returns the number of words that fit the lentgh, used for the size of the array */
int wordsWithLength(istream &input, unsigned int wordLength); 

/* Contains the algorithm that forms the basis for the computer being able to
cheat, hence the name. Essentially deletes old dictionaryList and creates new one */
int computerCheat(unsigned int wordLength, char inputLetter, 
	int count, char displayWord[]);

/* The function that keeps the game going until the player runs out of guesses
or the player guesses the word correctly */
int playGame(unsigned int wordLength, char inputLetter, string initialWord,
	int count, char displayWord[]);

/* This function keeps track of the letters that were typed by using a struct list
and prints the reverse of it which it how it was entered initially */
void printReverse(usedLetters *list);

/* This function simply checks for a win, which is determined if the counter for 
the word matches the word length. The counter for the word is incremented each time
a letter is guessed correctly. */
int checkWin(int counterForWord, unsigned int wordLength);

/* This function is used to search the linked list to see if a letter has already
been used */
int searchUsedLetters(char inputLetter, usedLetters *head);

/* This is used for changing the dictionaryList whenever changing words, it
returns whether it shrinks or not so that when it stops shrinking, it goes
ahead and applies the letter to see if it matches the word */
int swapDictionary(char inputLetter, unsigned int wordLength, int letterMatches);

/* This method is used for trimming the words at the end, where in dictionary.txt
there are spaces found at the end, which confused the program into thinking a 
word had more chars then it actually had. */
static inline std::string &rtrim(std::string &s);