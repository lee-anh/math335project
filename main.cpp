#include <iostream>

#include "Game.h"

using namespace std; 

int main(void){
   
    // n = # of times to run the simulation 
    
    int n = 100000; 
    int counter = 0; // count the number of times the condition turns out
    int draw = 0; // just for our records 
    int roundSum = 0; 

    

    for(int i = 0; i < n; i ++){
        //Game *g = new Game(4); // we care about inital hand
        // interesting that making it Game(0) makes the probability essential 50-50 (that is just reliant on which player gets chosen as the conditioned player)
        // but then when we try to use the below constructor, 
        // we get an issue where the number of condition successes is lower than expected 
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
                //g->printBoard(); 
                player1Win = true; 
                break; 
            }
            g->drawCard(1); // draw a new card

             
              // player 2 goes 
            g->playCard(2);
            if(g->checkSequence(2)){
                //g->printBoard(); 
                player2Win = true; 
                break; 
            }
            g->drawCard(2); 

           
            //cout << "Round: " << round << endl; 
            //g->printBoard(); 
            round++; 
            
           // g->printPlayerCards(1); 
            //g->printPlayerCards(2); 
            
          
        }
        roundSum += round; 

        int condPlayer= g->getConditionPlayer();
        //cout << "Cond Player: " << condPlayer << endl; 
        if(condPlayer == 1 && player1Win == true){
            counter++; 
        } else if(condPlayer == 2 && player2Win == true){
            counter++; 
        } else if(player1Win == false && player2Win == false){
            draw++; 
        }   
        
    //cout << "Condition player" << g->getConditionPlayer() << endl; 
    }
    
    cout << n << " trials" << endl; 
    cout << "Number of condition successes: " << counter << endl ;
    cout << "Number of draws: " << draw << endl; 
    cout << "Average number of rounds: " << (float) roundSum/n << endl ;

    

    return 0; 
}