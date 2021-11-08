#include "Game.h"

Game::Game(){
    setUpGame(); 
}

void Game::setUpGame(){
    setUpBoard(); 
    // create card deck
    createDeck(); 
    createMapping(); 


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
    vector<int> temp = vector<int>(); 

    // see google sheet for deck mapping 
    for(int i = 0; i < 48; i++){
        // 2 of each card 
        temp.push_back(i);
        temp.push_back(i); 
    }

    
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(temp.begin(), temp.end(), default_random_engine(seed)); 

    // put everything in the queue
    for(int i = 0; i < temp.size(); i++){
        shuffledDeck.push(temp.at(i)); 
    }

    
}


void Game::createMapping(){
    
    cardMapping = vector<vector<pair<int, int>>>(); 
    // initialization 
    for(int i = 0; i < 48; i++){
        vector<pair<int,int>> temp = vector<pair<int, int>>(); 
        temp.push_back(pair<int, int>(0, 0)); 
        temp.push_back(pair<int, int>(0, 0)); 
        cardMapping.push_back(temp); 
    }

    // assignments 

    // A Hearts
    cardMapping[0][0] = pair<int, int>(1, 5); 
    cardMapping[0][1] = pair<int, int>(4, 6); 

    // 

}

bool Game::checkSequence(int player, int x, int y){
    bool vertical = checkVertical(player, y); 
    bool horizontal = checkHorizontal(player, x); 
    bool diagonal = checkDiagonal(player, x, y); 

    // I think this syntax is ok?
    if(vertical || horizontal || diagonal){
        return true; 
    } 
    return false; 

}


bool Game::checkVertical(int player, int y){
    int counter = 0; 
    // for each row 
    for(int row = 0; row < gameboard.size(); row++){
        int col = gameboard.at(row).at(y); 
        if(col == 3 || col == player){
            counter++; 
        } else {
            counter = 0; 
        }

        if(counter == 5){
            return true;
        }
    }

    return false; 
    
}

bool Game::checkHorizontal(int player, int y){
    vector<int> row = gameboard.at(y); 
    int counter = 0; 
    for(int i = 0; i < row.size(); i++){
        if(row.at(i) == 3 || i == player){
            counter++; 
        } else {
            // reset counter 
            counter = 0; 
        }

        if(counter == 5){
            return true; 
        }

    }

    return false; 
}

bool Game::checkDiagonal(int player, int x, int y){
    // get x and y to the corner most position 
    while(x > 0  && y > 0){
        x--; 
        y--; 
    }

    int counter = 0 ;
    while(x < gameboard.size() && y  < gameboard.size()){
        if(gameboard[x][y] == 3 || gameboard[x][y] == player){
            counter++; 
        } else {
            counter = 0; 
        }

        if(counter == 5){
            return true; 
        } 
        x++; 
        y++; 

    }

    return false; 
}


bool Game::drawCard(int player){
    if(shuffledDeck.size() == 0){
        return false; 
    }
    int card = shuffledDeck.front(); 
    shuffledDeck.pop(); 

    if(player == 1){
        player1Cards.push(card); 
    } else if (player == 2){
        player2Cards.push(card); 
    } 

    return true; 
}

void Game::playCard(int player){
    if(player == 1){
        int card = player1Cards.front(); 
        player1Cards.pop(); 
        // TODO: look up the card here
        // if the place has been taken 

    } else if (player == 2){
        int card = player2Cards.front(); 
        player2Cards.pop(); 

    }
}


bool Game::placeToken(int player, pair<int, int> location){
    if(gameboard[location.first][location.second] == 0){
        gameboard[location.first][location.second] = player; 
        return true; 
    } 

    return false; 

}
