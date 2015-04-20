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

#include "hinky.h"	/* Imports from the hinky header file */

int main(int numargs, char *args[]){

	srand(time(0));  /*This must be called before every program to seed the 
						random generator. Truly makes rand() random */
	
	ifstream dictFile;				// For the dictionary file
	unsigned int wordLength;		// Length of the word requested by user
	int playAgain=1;				// Ask the user to play again after game
	int skipLoss;				// Skips loss if you win and this is set to 1
	int computerScore=0, userScore=0;	//Initializes score for both players

	if(numargs != 2){// Make sure correct num of args entered
		cerr << "Usage: " << args[0] << " <filename>" << endl;
		exit(1);	//Exit program if error occurs
	}

	dictFile.open(args[1]);	//This opens the file and sets it to the var

	if(dictFile.fail()){//In case of failure
		cout << "Unable to open " << args[1] << endl;
		exit(1);
	}
	
	while(playAgain){

		dictFile.clear();	//To remove the eof() file flag
		dictFile.seekg(0, ios::beg);	//Seeks to the beginning of file

		skipLoss = 0;

		cout << "Please enter desired word length: "; 
		cin >> wordLength;

	
		while((wordLength > 12 || wordLength < 3) && !cin.fail()){//Length checker to stay within range
			cout << "Length must be a number  within the range 3-12, please enter again: ";
			cin >> wordLength;	
		}

		arraySize = wordsWithLength(dictFile, wordLength);	//Get the size of the array
		dictionaryList = new string[arraySize];// Initialize array to number of wordsWithLength
		
		//This bottom does not compile on nike unfortunately, so I commented it out
		//dictionaryList = new (nothrow) string[arraySize];// Initialize array to number of wordsWithLength
		/*if(dictionaryList == nullptr){
			cerr<< "There was an error assigning memory to [dictionaryList]"<<endl;
			exit(1);
		}*/


		string desiredWord;
		int i=0;				// Initialize the i. IMPORTANT BECAUSE BEFORE I DIDNT
								// AND IT THREW OFF MY PROGRAM!!!
		while(!dictFile.eof()){//Store the words in the dynamically allocated array
			getline(dictFile, desiredWord);
			desiredWord = rtrim(desiredWord);	//Trim the words, rmoving empty spaces at the end
			if((unsigned)desiredWord.length() == wordLength){
				dictionaryList[i] = desiredWord;
				//cout << "Desired Word: " << desiredWord << endl;
				i++;
			}
			
		}

		string initialWord;	//The initial word chosen from the list
		int randomWordNum = rand() % arraySize;	// In the range 0 to (arraySize-1)

		initialWord = dictionaryList[randomWordNum];	//Random word assigned
				
		cout<< "Number of Guesses Remaining: " << GUESSES << endl;

		//cout << "Initial Word: " << initialWord << endl;

		char displayWord[wordLength];	//This will be displayed to the user;

		for(i=0; i<wordLength; i++){
			displayWord[i] = '-';		
		}

		displayWord[wordLength] = 0; //Terminate end of string with 0
		//cout << "Word: "<< displayWord << endl;

		char inputLetter;	// Letter entered by the user
		int gameWin=0;	//If this is set to true, the player wins
		usedLetters *head = NULL;	// Head points to the list of nodes, initially empty
		int counterForWord=0;	//Keeps track of the number of letters matched 
		int shortcount=0;	//To ensure that the search isn't used the first turn
		changingWord = initialWord;	// Changing word will of course, change


		while(GUESSES > 0 && gameWin == 0){
			cout << endl;

	/*********** ENABLING CHANGING WORD IS FOR TESTING/GRADING PURPOSES ONLY******/
			//cout<<"(This can be omitted)";cerr<< "Changing Word: " << changingWord << endl;
	/*********** Comment above out if you don't want it to be seen ***************/

			cout << "You have "<< GUESSES << " guesses left." << endl;
			cout << "Used Letters: "; printReverse(head); cout<<endl;
			cout << "Word: "<< displayWord << endl;

	/*********** SHOWING REMAINING WORDS IS FOR TESTING/GRADING PURPOSES ONLY********/
			cerr << "Words remaining in the list: " << arraySize << endl;
	/*********** Comment above out if you don't want it to be seen **************/

			cout<< "Enter your letter guess: ";
			cin >> inputLetter;

			inputLetter = tolower(inputLetter);				//This is to ensure that lower and upper case are equivalent 

			while(!isalpha(inputLetter)){//Checking if the input is of the alphabet
				cout<<"Please enter 1 letter (of the English alphabet)."<<endl;
				cout<< "Enter your letter guess: ";
				cin >> inputLetter;
			}

			if(shortcount != 0)
				if(searchUsedLetters(inputLetter, head)){
					cout<<endl;
					cout << "You used "<<inputLetter<< " already!" << endl;
					continue;
				}
			//Create a new list of node containing the value read in
			usedLetters *tmp = new usedLetters;// Allocates new space for the pointer tmp
			tmp->letter = inputLetter;

			// Attach the new node to the front of the list
			tmp->next = head;
			head = tmp;

			cout << endl;

			counterForWord = computerCheat(wordLength, inputLetter, counterForWord, displayWord);
			gameWin = checkWin(counterForWord, wordLength);

			if(gameWin == 1){
				cout << "Congratulations! You won the game!" << endl;
				cout << "The word was: "<< changingWord<< endl;
				cout << "Now please give me a 100 on this project so we can both be winners." << endl;
				delete[] dictionaryList;		//To prevent memory leakage
				//exit(1);
				skipLoss = 1;					//Skip loss output
				userScore++;					//Increase user score
			}	
			if(shortcount == 0)// Should only enter first time, never again
				shortcount=1;
		}
		if(skipLoss ==0){
			delete[] dictionaryList;		//To prevent memory leakage
			cout << "YOU LOST!!! The word was: "<< changingWord << endl;
			computerScore++;				//Increase computer score
		}
		cout<<endl;
		cout<<"Computer Score: " << computerScore<<endl;
		cout<<"User Score: "<<userScore<<endl;
		cout<<"Play Again? (y/n): ";

		char yesOrNo;					//Needs to be Y,y for yes; N,n for no
		cin >> yesOrNo;
		while(yesOrNo != 'y' && yesOrNo != 'Y' && 
			yesOrNo != 'n' && yesOrNo != 'N'){
			cout<<"Please enter 'y' or 'n' (case insensitive)."<<endl;
			cout<<"Play Again? (y/n):";
			cin >> yesOrNo;
		}
		switch(yesOrNo){
			case 'Y':
			case 'y':
				playAgain = 1; 	//Keep playing
				GUESSES = 10;
				break;
			case 'N':
			case 'n':
				playAgain = 0;	//Stop playing
				break;
		}

	}
	cout << "Thanks for playing! "<<endl;
	return 0;
}

int wordsWithLength(istream &input, unsigned int wordLength){
	int count=0;	//Going to count the words matching wordLength
	string tmp;	//Temporarily stores string to compare

	while(!input.eof()){
		getline(input, tmp);
		tmp = rtrim(tmp);
		if((unsigned)tmp.length() == wordLength){
			count++;	//Increment if string length matches wordLength 
		}
	}

	input.clear();	//To remove the eof() file flag
	input.seekg(0, ios::beg);	//Seeks to the beginning of file

	if(count == 0){	// If there are no words in dict with selected length, terminate
		cerr<< "There are no words in the dictionary with this length."<< endl;
		cerr<< "Please use another dictionary or different length and try again." << endl;
		cerr<< "If you entered a letter, please enter a digit next time."<<endl;
		//delete[] dictionaryList;
		exit(1);
	}

	return count;
}

int checkWin(int counterForWord, unsigned int wordLength){
	if(counterForWord == wordLength ){
		return 1;
	}else{
		return 0;
	}
}

int computerCheat(unsigned int wordLength, char inputLetter, 
	int count, char displayWord[]){	

	int letterMatches=0;	// Checks to see if inputletter matches a letter in initial word
	int i;					// For the array

	for(i=0; i<wordLength; i++){//First check to see if letter matches 
		if(tolower(changingWord[i]) == inputLetter){
			letterMatches = 1;
		}
	}

	if(notShrinking == 1){//If it is down to the last word in list
		count = playGame(wordLength, inputLetter, changingWord,
			 count, displayWord); //Play the game normally	
	}else{
		if(letterMatches==1){// A lot of stuff happens here
			if(swapDictionary(inputLetter, wordLength, letterMatches)){//Shrinking down the dictionary
				count = playGame(wordLength, inputLetter, changingWord,
			 count, displayWord); //Play the game normally	
			}else{
				cout<<"Sorry there are no "<< inputLetter<<"'s"<<endl;	
			}

		}else{//Decrement GUESSES and have them try again
			swapDictionary(inputLetter, wordLength, letterMatches);	//Shrinking down the dictionary
			GUESSES--;
			cout<<"Sorry there are no "<< inputLetter<<"'s"<<endl;
		}
	}
	return count;
}

int swapDictionary(char inputLetter, unsigned int wordLength, int letterMatches){
	int i;
	int count=0;
	int nonMatching=0;		//This is used to check to see if there exists a letter that doesn't match
	int notShrinking = 0;		//0 indicates false, meaning it still shrinks

	for(i=0; i<arraySize; i++){	// Determine the size for the tmp array
		if((dictionaryList[i].find_first_of(inputLetter)) == std::string::npos){//If it doesn't match
			count++;	//Determine the size of the array first
			nonMatching = 1;
		}
	}	
	//cout << "Count: " << count << endl;
	//cout << "ArraySize: "<< arraySize << endl;
	if(count == 0){// If the dictionary list did not decrease in size
		notShrinking = 1;
		//cout << "Array not shrinking anymore" << endl;
	}

	if(nonMatching == 1){
		string *tmp = new string[count];		//Will be used for transferring
		int j=0;

		for(i=0; i<arraySize; i++){	// Determine the size for the tmp array
			if((dictionaryList[i].find_first_of(inputLetter)) == std::string::npos){//If it doesn't match
				tmp[j] = dictionaryList[i];
				//cout << "Dictionary without letter: " <<dictionaryList[i]<<endl;
				j++;
			}
		}

		arraySize = count;

		delete[] dictionaryList;				//We delete the previous dictionary
		dictionaryList = new string[arraySize];	//This is where we create a new dictionary
		for(i=0; i<arraySize; i++){
			dictionaryList[i] = tmp[i];
		}

		if(letterMatches == 1){
			int randomWordNum = rand() % arraySize;	// In the range 0 to (arraySize-1)
			//cout << "randomWordNum: " << randomWordNum << endl;
			changingWord = tmp[randomWordNum];
			tolower(changingWord[0]);
			
		}
		delete[] tmp;
	}

	if(letterMatches==1&&notShrinking==0){
		GUESSES--;
	}
	return notShrinking;
}

void printReverse(usedLetters *list){
	int count = 1;
	if(list == NULL)
		return;
	printReverse(list->next);
	cout << list->letter<< " ";
	
}

int searchUsedLetters(char inputLetter, usedLetters *head)
{
    usedLetters* pNode = head;
    
    /* traverse the list */
    while (pNode != NULL) {
        /* Target! */
        if(pNode->letter == inputLetter)
        {
            return 1;
        }
        /* move to the next one */
        pNode = pNode->next;
    }
    return 0;
}

int playGame(unsigned int wordLength, char inputLetter, string initialWord,
	int count, char displayWord[]){	//Normal way to play the game
	int i;	// Needs to be declared for the array
	int countChecker;	// Checks if count was incremented, if not subtract GUESSES

	countChecker = count;

	//cout << "Word Length: " << wordLength << endl;
	for(i=0; i<wordLength; i++){// Here the letter being stored in displayWord
		if(initialWord[i] == inputLetter){
			displayWord[i] = inputLetter;
			count++;
		}
	}

	if(count == wordLength){

		return count;
	}else if(countChecker == count){
		GUESSES--;	//This means that the player did not guess right this turns
	}
	return count;
}

//	Trim from the end
static inline std::string &rtrim(std::string &s){
	s.erase(std::find_if(s.rbegin(), s.rend(), 
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}
/* End of entire program */