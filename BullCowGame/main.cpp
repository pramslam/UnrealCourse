/* This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC pattern, and is responsible for all
user interactions. For game logic see the FBullCowGame Class.

*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
FText RepeatGuess(FText);
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;		// instantiate the game, which we reuse each game

// ENTRY POINT 
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();

		bPlayAgain = AskToPlayAgain();
		}
	while (bPlayAgain);

	return 0;
}

// FUNCTION DEFINITIONS
// introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows: The Word Game.\n";
	std::cout << "Can you guess the word I am thinking of?\n";
	std::cout << "Bulls are letters in the right place.\n";
	std::cout << "Cows are letters in the wrong place.\n\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// main instance of the game
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for number of turns asked for guesses
	// while NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() < MaxTries)
	{
		FText Guess = GetValidGuess();
		
		//submit valid guess to game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ".\n\n";
	}

	PrintGameSummary();
	return;
}
// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetMaxTries() - BCGame.GetCurrentTry();
		std::cout << CurrentTry << " tries left. " << "Enter your guess: ";
		std::getline(std::cin, Guess);

		// check guess validity
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n\n";
			break;
		case EGuessStatus::OK:
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);	// keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl << std::endl;;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
