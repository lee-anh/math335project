#include <iostream>

#include "Game.h"

using namespace std; 

int main(void){
   
    // n = # of times to run the simulation 
    
    int n = 1000; 
    int counter = 0; // count the number of times the condition turns out
    int draw = 0; // just for our records 

    

    for(int i = 0; i < n; i ++){
        //Game *g = new Game(7); // we care about inital hand
        Game *g = new Game(); // we care about player 1
        bool player1Win = false;
        bool player2Win = false; 
        int round = 0; 
        
        // should change this to player cards is empty b/c they might still have cards to play
        while(g->isPlayerEmpty() == false){

            // player 1 goes
            g->playCard(1); 
            // check for a sequence
            if(g->checkSequence(1)){
                // player 1 has won 
               // g->printBoard(); 
                player1Win = true; 
                break; 
            }
            g->drawCard(1); // draw a new card

            
            // player 2 goes 
            g->playCard(2);
            if(g->checkSequence(2)){
                // player 1 has won 
               // g->printBoard(); 
                player2Win = true; 
                break; 
            }
            g->drawCard(2); 
            //cout << "Round: " << round << endl; 
           // g->printBoard(); 
            round++; 
            
           // g->printPlayerCards(1); 
            //g->printPlayerCards(2); 
            
          
        }
        

        int condPlayer= g->getConditionPlayer();
        //cout << "Cond Player: " << condPlayer << endl; 
        if(condPlayer == 1 && player1Win == true){
            counter++; 
        } else if(condPlayer == 2 && player2Win == true){
            counter++; 
        } else if(player1Win == false && player2Win == false){
            draw++; 
        }   
        

    }
    cout << n << " trials" << endl; 
    cout << "Number of condition successes: " << counter << endl ;
    cout << "Number of draws: " << draw << endl; 

    

    return 0; 
}