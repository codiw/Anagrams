#include "lettercount2.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

/*
* Use your LetterCount class and understanding of recursion
* to implement code capable of identifying all of the anagrams of a given word
* or phrase, where an anagram is the rearrangement of the letters in a word or
* phrase into other words.
*/

void findAnagram(const vector<LetterCount>& dict,LetterCount &inputWord,vector<int>& currentIndices,vector<vector<int>>& allMatches)
{
	for (unsigned int i = 0; i<dict.size(); i++) // Iterate through the dictionary
	{
		LetterCount currentDictionaryWord = dict[i];

		if (inputWord.hasAsMany(currentDictionaryWord))
		{
			currentIndices.push_back(i);
			LetterCount copy = LetterCount(inputWord);
			copy.subtract(currentDictionaryWord);
			findAnagram(dict, copy, currentIndices, allMatches); // recurse with the new word and dictionary
		}

		if (inputWord.totalCount() == 0 && currentIndices.size()>0) // if there are no letters left in input must be anagram
		{
			allMatches.push_back(currentIndices);
			currentIndices.clear();
		}
	}
	currentIndices.clear();
}

int main()
{
	string input;

	vector<LetterCount> dict;
	vector<string> visualDictionary;
	vector<int> currentIndices;
	vector<vector<int>> allMatches;

	ifstream file1;
	file1.open("dictionary.txt");

	while (getline(file1, input))
	{
		LetterCount letterCount(input.c_str());
		dict.push_back(letterCount);
		visualDictionary.push_back(input);
	}

	cout << "Please enter a word or phrase: ";
	cin >> input;

	findAnagram(dict, LetterCount(input.c_str()), currentIndices, allMatches);

	for (unsigned int i = 0; i<allMatches.size(); i++) 
	{
		for (unsigned int j = 0; j<allMatches[i].size(); j++) 
		{
			cout << visualDictionary[allMatches[i][j]] << " ";
		}
		cout << endl;
	}

	file1.close();

	return 0;
}