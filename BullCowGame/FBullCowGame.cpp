#pragma once
#include "FBullCowGame.h"
#include <map>

//to make sintax Unreal friendly
#define TMap std::map
using int32 = int;
using Ftext = std::string;

FBullCowGame::FBullCowGame()  //default constructor 
{
	Reset();
}

void FBullCowGame::Reset()
{
	constexpr int32 CURRENT_TRY = 1;
	const FString HIDDEN_WORD = "planet"; //this MUST be an isogram

	MyCurrentTry = CURRENT_TRY;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,6}, {4,8}, {5,10}, {6,12} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const 
{ 
	return MyCurrentTry; 
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::isGameWon() const
{
	return bGameIsWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess is not isogram
	{
		return EGuessStatus::Not_Isogram; //return appropriate error
	}
	else if (!IsLowerCase(Guess)) //if the guess is not all lowercase
	{
		return EGuessStatus::Not_LowerCase; //return appropriate error
	}
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{
		return EGuessStatus::Wrong_Lenght; //return appropriate error
	}
	else //otherwise
	{
		return EGuessStatus::OK; //return OK
	}
}

//receives a VALID guess , increments turn and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	for (int32 HWChar = 0; HWChar < WordLength; HWChar++) //loop through all letters in the hidden word; HWChar = Hidden Word Character
	{
		for (int32 GWChar = 0; GWChar < WordLength; GWChar++) //compare letters against the guess
		{ 
			if (Guess[GWChar] == MyHiddenWord[HWChar]) //if they match; GWChar = Guess Word Character
			{ 
				if (HWChar == GWChar) //if they are in the same place
				{
					BullCowCount.Bulls++; //increment the bulls 
				}
				else
				{
					BullCowCount.Cows++; //increment the cows 
				}
			}
		}					
	}
	if (BullCowCount.Bulls == WordLength) 
	{ 
		bGameIsWon = true; 
	}
	else { bGameIsWon = false; }
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; //set up our map
	for (auto Letter : Word) //for all letters in range Word
	{ 
		Letter = tolower(Letter); //handle mixed cases 
		if (LetterSeen[Letter])//if the letter is in the map
		{
			return false; //we do NOT have an isogram
		}
		else //otherwise
		{
			LetterSeen[Letter] = true; //we add the letter to the map
		}
	}
	return true; 
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{ 
		if (!islower(Letter)) //if NOT a lower case letter
		{
			return false; //return false
		}
		else { return true; } //otherwise, it means the word is all in lower case (=true)
	}
}
