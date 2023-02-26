//
//  main.cpp
//  Assignment 2
//
//  Created by Joy Mugo (MUGJD2103) on 27/07/2022.
//

#include <iostream>
#include <cstring>

using namespace std;

int stringLength ( char str [] ) //Calculates length of a string
 {
     int i = 0;
     while (str[i] != '\0' )
         i++;
     return i;
 }

char* revealCreate ( char secretWord[] ) //Creates the format of the secret word that gets revealed over time
{
    const int LEN = stringLength(secretWord);
    char* reveal = new char[LEN];
    for ( int i = 0 ; i < LEN ; i++)
        reveal[i] = '*';
    reveal[LEN] = '\0';
    return reveal;
}

int numOfLives ( char secretWord[] ) // Calculates number of lives
{
    int lives = 0;
    int len = stringLength(secretWord);
    if ( len < 10 )
        lives = 10;
    else if ( len > 15 )
        lives = 20;
    else
        lives = len + 5;
    
    return lives;
}

int checkGuess ( char secretWord[] , char guess ) //Checks if the guess is in the secretword and counts how many times it appears
 {
    int count = 0;
    for ( int i = 0 ; secretWord[i] != '\0'; i++)
         if ( secretWord[i] == guess )
             count++;
     return count;
 }
 
int* guessResult ( char secretWord[] , char guess ) // Creates an array that holds the indexes where the guess appears in the secret word
{
    int* temp = new int;
    if ( checkGuess(secretWord,guess) > 0)
        for ( int i = 0, k = 0 ; secretWord[i] != '\0'; i++)
             if ( secretWord[i] == guess )
             {
                 temp[k] = i;
                 k++;
             }
  
    return temp;
}

void changeReveal ( char reveal[] , char secretWord[] , char guess ) //Alters the reveal variable if the guess is correct.
{
    int* temp = guessResult(secretWord,guess);
    int size = checkGuess(secretWord,guess);
    if ( checkGuess(secretWord,guess) > 0 )
    {
        for ( int i = 0 ; i < size ; i++)
            reveal[temp[i]] = secretWord[temp[i]];
        cout << "Got it!" << endl;
    }
    else
        cout << "Sorry." << endl;
    cout << endl;
}

bool wordFound ( char reveal[] , char secretWord[] ) //Checks if all characters of the secret word have been revealed.
{
    bool check = false;
    for ( int i = 0 ; reveal[i] != '\0'; i++)
    {
        if ( reveal[i] == secretWord[i] )
            check = true;
        else
        {
            check = false;
            break;
        }
    }
    return check;
}

void gameResult ( char reveal[] , char secretWord[] , int lives ) //Outputs the result of the game.
{
    
    if ( wordFound(reveal,secretWord) == true)
        cout << "Good. You correctly guessed the word: " << secretWord << endl;
    else if ( lives == 0 && wordFound(reveal,secretWord) == false)
        cout << "Sorry no more lives. The word is " << secretWord << endl;
    
}



 int main ()
 {
     bool play = true;
     while ( play == true )
     {
        const char* secretWord = new char;
        cout << "Enter the secret word (all in lower case) : ";
        cin >> secretWord;
        cout << "============================================" << endl;
         
         char* reveal = revealCreate(secretWord);
         int lives = numOfLives(secretWord);
         int count = 1;
         
         while (lives != 0 && wordFound(reveal,secretWord) == false)
         {
             cout << "Word so far: " << reveal << endl;
             char guess;
             cout << "Take a guess number " << count << ": ";
             count++;
             cin >> guess;
             changeReveal(reveal, secretWord, guess);
             lives--;
         }
         
         gameResult(reveal, secretWord, lives);
         
         char repeat;
         cout << "Do you want to play one more time? y/n? ";
         cin >> repeat;
         cout << endl;
         if ( repeat == 'n')
         {
             cout << "Bye!" << endl;
             play = false;
         }
     }
     return 0;
 }

