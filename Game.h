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
   // ~Game(); // destructor.. not currently dynamically allocating anything?? 
    bool isDeckEmpty(); 

    bool checkSequence(int player);

    bool drawCard(int player); 

   
    void playCard(int player); 

    int getConditionPlayer(); 

    void printPlayerCards(int player); 

    private:

     // instance variables 
    vector<vector<int>> gameboard;
    queue<int> shuffledDeck; 
    queue<int> player1Cards;
    queue<int> player2Cards; 
    vector<vector<pair<int, int>>> cardMapping; 

    int conditionPlayer; 
    pair<int, int> lastPlacedToken; 
   
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


    bool placeToken(int player, pair<int, int> location); 
    
}; 

#endif 
