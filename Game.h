#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std; 

class Game
{
    public:
    Game(); // constructor
   // ~Game(); // destructor.. not currently dynamically allocating anything?? 
    
    bool checkSequence(int player, int x, int y);

    bool drawCard(int player); 

    /**
     * Uses the look up table to determine what positions 
     * Checks to see which position are free
     * If both positions are free, then determines the position by a coin toss 
     * There will be no dead cards 
     */ 
    void playCard(int player); 

    private:
    /**
     * To be called in the constructor
     * Takes care of dealing inital cards
     * Shuffling the deck
     * Populating the lookup table
     * Initalizing the gameboard 
     */ 
    void setUpGame();

    void setUpBoard(); 

    void createDeck(); 
    void dealInitalCards(); 
    void shuffleAndEnqueueCards();

    void createMapping(); 
    
    vector<vector<int>> gameboard;
    queue<int> shuffledDeck; 
    queue<int> player1Cards;
    queue<int> player2Cards; 
    vector<vector<pair<int, int>>> cardMapping; 

    bool checkVertical(int player, int y);
    bool checkHorizontal(int player, int x);
    bool checkDiagonal(int player, int x, int y); 


    bool placeToken(int player, pair<int, int> location)
    



    





}; 

#endif 
