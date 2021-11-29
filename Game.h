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
    vector<int> player1Cards;
    vector<int> player2Cards; 
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
    bool checkSequence(int player, int x, int y, int seq); 
    bool checkVertical(int player, int y, int seq);
    bool checkHorizontal(int player, int x, int seq);
    bool checkDiagonal(int player, int x, int y, int seq); 

    // play card helper function 
    pair<int, int> optimalMove(int player);
    bool placeToken(int player, pair<int, int> location); 
    
}; 

#endif 
