/* This is the console executable, that makes use of the BullCow Class
This acts as the view in a MVC pattern, and is responsible for all
user interactions. For game logic see the FBullCowGame Class.

*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

//FUNCTION DECLARATIONS
void PrintIntro();
void PlayGame();
FText GetValidGuess();
FText RepeatGuess(FText);
bool AskToPlayAgain();

FBullCowGame BCGame;		// instantiate the game

//ENTRY POINT 
int main()
{
	std::cout << BCGame.GetCurrentTry();

	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();

		//TODO Add Game Summary
		bPlayAgain = AskToPlayAgain();
		}
	while (bPlayAgain);

	return 0;
}

//FUNCTION DEFINITIONS
void PrintIntro()
{
	// introduce the game
	std::cout << "\n\n Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	// loop for number of turns asked for guesses
	// while NOT won and there are still tries remaining

	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		RepeatGuess(Guess);
		
		//submit valid guess to game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << ".\n\n";
	}

	//TODO summarise Game
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
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". " << "Enter your guess: ";
		std::getline(std::cin, Guess);

		// check guess validity
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		case EGuessStatus::Used_Numbers:
			std::cout << "Please enter only letters.\n";
			break;
		case EGuessStatus::OK:
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);	// keep looping until we get no errors
	return Guess;
}

FText RepeatGuess(FText Guess)
{
	// repeat guess back to them
	std::cout << "Your guess was: " << Guess << std::endl;
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
