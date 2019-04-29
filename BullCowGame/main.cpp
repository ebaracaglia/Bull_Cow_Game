/*
This is the console executable that makes use of the 
BullCow class. This acts as the view in te MVC pattern
and it is responsible for all user interactions. For 
game logic see the FBullCowGame class
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//to make sintax Unreal friendly
using Ftext = std::string;
using int32 = int;

//function prototypes as outside a class
void PrintIntro();
void PlayGame();
Ftext GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate (=create an instance) of a new game, which we re-use across plays


//entry point of the application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while  (bPlayAgain);

	return 0; //exit the application
}


//introduce the game
void PrintIntro() 
{
	std::cout << "\n\n\Welcome to Bulls and Cows\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letters isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
						 
	// loop asking for guesses WHILE the game is NOT won
	// and there are still tries remaining
	while(!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		Ftext Guess = GetValidGuess(); 

		//submit valid guess and receive number of bulls and cows
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

//loop continually until the user gives a valid guess
Ftext GetValidGuess() 
{
	Ftext Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do 
	{
		//get guess from the player 
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";

		std::getline(std::cin, Guess);

		//check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letters word. \n\n";
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram (word with all different letters). \n\n";
			break;

		case EGuessStatus::Not_LowerCase:
			std::cout << "Please enter a word with letters all in lower case. \n\n";
			break;

		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get valid guesses from the player
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)";
	Ftext Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.isGameWon())
	{
		std::cout << "Well done, you won! \n";
	}
	else
	{
		std::cout << "Better luck next time\n";
	}
}
