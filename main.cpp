#include <iostream>

#include "Game.h"

int main(void){
    // testing 
    /*
    Game *g = new Game(1); 
    g->printPlayerCards(1); 
    g->printPlayerCards(2); 
    */
    // this is where we will run the simulation 

   
    // n = # of times to run the simulation 
    
    int n = 10; 
    int counter = 0; // count the number of times the condition turns out
    int draw = 0; // just for our records 

    for(int i = 0; i < n; i ++){
        Game *g = new Game(); 
        bool player1Win = false;
        bool player2Win = false; 

    
        while(g->isDeckEmpty() == false){

            // player 1 goes
            g->playCard(1); 
            // check for a sequence
            if(g->checkSequence(1)){
                // player 1 has won 
                player1Win = true; 
                break; 
            }
            g->drawCard(1); // draw a new card

        
            // player 2 goes 
            g->playCard(2);
            if(g->checkSequence(2)){
                // player 1 has won 
                player2Win = true; 
                break; 
            }
            g->drawCard(2); 
            
          
        }
        

        int condPlayer= g->getConditionPlayer();
        
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