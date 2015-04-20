/* This is a test file testing to see the effectiveness of the trimming methods */

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
#include <iostream>			// Contains cout and cin
#include <cstring>			// Contains the string class

using namespace std;		// To shorten std::cout and std::cin

//	Trim from the start
static inline std::string &ltrim(std::string &s){
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), 
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

//	Trim from the end
static inline std::string &rtrim(std::string &s){
	s.erase(std::find_if(s.rbegin(), s.rend(), 
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

//	Trim from both ends
static inline std::string &trim(std::string &s){
	return ltrim(rtrim(s));
}

int main(){
	string test = "Cool ";

	cout<< "Test Length: "<< test.length() << endl;

	string testTrimmed = rtrim(test);		//After it has been trimmed
	cout<< "TestTrimmed Length: "<< testTrimmed.length() << endl;


}