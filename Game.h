#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std; 

class Game
{
    public:
    Game(); // constructor
   // ~Game(); // destructor.. not currently dynamically allocating anything?? 
    
    bool checkSequence(int player);

    bool drawCard(int player); 

    /**
     * Uses the look up table to determine what positions 
     * Checks to see which position are free
     * If both positions are free, then determines the position by a coin toss 
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
    vector<vector<int>> gameboard;
    queue<int> shuffledDeck; 
    queue<int> player1Cards;
    queue<int> player2Cards; 

    bool checkVertical(int player);
    bool checkHorizontal(int player);
    bool checkDiagonal(int player); 
    



    





}; 

#endif 
