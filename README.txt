Name: Cesar Acosta

Date: 12/03/14

Class: CSCI 1730 (Maria Hybinette)

Purpose: In this assignment you will write a variation of hangman. 
Here, your program will take the place of one of the players in the game. 
The twist is that this program will not select one particular word 
(specified by dashes), but instead the program cheats by adaptively dodging 
the opposing player's guesses, and keep track of a set of possible words 
instead of a particular one word. The 'program' will maintains a list of 
words in the English language, and as the opposing player guess letters 
it will continuously pares down the word list to try to dodge the player's 
guesses as much as possible.



Compile: This program needs to be compiled with the following command:
	compile:
		g++ hinky.cpp -o hinky
	clean:
		rm hinky
This should compile the file correctly.
Also use the command: [make] to compile and then [make clean] to remove the
executable.

How To Use:
	Parameters for Hinky Hangman game: ./hinky [nameOfFile.txt]
		Ex: ./hinky fiveHundredWords.txt
			./hinky thousandHundredWords.txt
			./hinky twoThousandHundredWords.txt
			./hinky dictionary.txt
	Instructions:
		When you run the program, you will be asked to input a length
		between 3-12. Once you do this then you will then commence the 
		hangman game with 10 guesses. The goal is to guess the word correctly
		before you run out of guesses. Each time you incorrectly enter a letter,
		you will be deducted a guess. You will not be deducted a guess if you
		already used a certain letter, but you will be prompted to input a 
		different letter.

When Using the program:
	This program uses an algorithm that essentially tricks the user into
	thinking that they cannot get the first couple of guesses correctly. 
	What the computer does is that it cheats. The way the computer cheats
	in this program is by randomly selecting a word at the beginning after the 
	word length is inputted. Then after the user enters a letter, the computer
	checks the letter to see if it matches the word it selected. If it does match
	then the computer deletes all the words with that letter then selects another
	word at random. If the letter does not match the already selected word, the computer still deletes all words in the list with the letter, but it does not
	change its current word. Once the user enters a letter wherein that letter is in all words of the list, then the computer stops deleting and a normal
	game of hangman ensues where the user will need to guess the current letter.
	The computer cheating in the beginning has a significant effect on the user 
	as it will cause the user to lose more on average, especially with a bigger dictionary.

!!!!!!!!!IMPORTANT FOR GRADERS!!!!!!!!!
	For grading/testing purposes, you can choose to reveal the word that the 
	computer chooses. Bear in mind that the word will be constantly switching
	and even if you enter a letter that is in the word, the program will tell you
	that it is not in it. This is the computer cheating and a normal user will
	not be able to tell. The word will stay constant only when the dictionary
	cannot shrink anymore. You can also choose to comment out the words remaining
	in the list. I left it on already for grading purposes.

	IF YOU WANT TO REVEAL WORD:
		Go to line 99 of my program and uncomment it out, in order to view the word the computer uses.
	IF YOU WANT TO REVEAL NUMBER IN LIST REMAINING:
		Go to line 107 of my program and uncomment it out(if not done already),
		in order to view the number of words remaining in the list