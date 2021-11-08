#include "Game.h"

Game::Game(){
    setUpGame(); 
}

void Game::setUpGame(){
    setUpBoard(); 
    // create card deck



}


void Game::setUpBoard(){
    // gameboard of all 0s; 
    gameboard = vector<vector<int>>();
    for(int i = 0; i < 10; i ++){
        vector<int> temp = vector<int>(); 
        for(int j = 0; j < 10; j++){
            temp.push_back(0); 
        }
        gameboard.push_back(temp); 
    }


}

void Game::createDeck(){
    
}