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
    Game(int n); 


   // ~Game(); // destructor.. currently don't need
    
    bool isDeckEmpty(); 
    bool isPlayerEmpty(); 
    bool checkSequence(int player);

    bool drawCard(int player); 

   
    void playCard(int player); 
    int getConditionPlayer(); 

    void printPlayerCards(int player); 

    void printBoard(); 

    private:

     // instance variables 
    vector<vector<int>> gameboard;
    queue<int> shuffledDeck; 
    queue<int> player1Cards;
    queue<int> player2Cards; 
    vector<vector<pair<int, int>>> cardMapping; 

    int conditionPlayer; 
    pair<int, int> lastPlacedToken; 
    int sequenceLength; 
    int conditionCards; 
   
    // set up helper functions
    void setUpGameAny();
    void setUpGameCondition();
    void setUpBoard(); 
    void createDeckAndDealAny(); 
    void createDeckAndDealCondition(); 
    void createMapping(); 
    
   
    // check sequence helper functions 
    bool checkVertical(int player, int y);
    bool checkHorizontal(int player, int x);
    bool checkDiagonal(int player, int x, int y); 

    // play card helper function 
    bool placeToken(int player, pair<int, int> location); 
    
}; 

#endif 
