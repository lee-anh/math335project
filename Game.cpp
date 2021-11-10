#include "Game.h"

Game::Game(){
    setUpGameAny(); 
    

}

Game::Game(int n){
    conditionCards = n; 
    setUpGameCondition(); 
   
}

void Game::setUpGameAny(){
    setUpBoard(); 
    // create card deck
    createDeckAndDealAny(); 
    createMapping(); 
    conditionPlayer = 1; 
    sequenceLength = 5; 


}

void Game::setUpGameCondition(){
    setUpBoard(); 

    createDeckAndDealCondition(); 
    createMapping(); 
    sequenceLength = 5; 
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

    // wildcards 
    gameboard[0][0] = 3;
    gameboard[0][9] = 3;
    gameboard[9][0] = 3;
    gameboard[9][9] = 3; 


}

void Game::createDeckAndDealAny(){
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
    for(int i = 0; i < (int) temp.size(); i++){
        shuffledDeck.push(temp.at(i)); 
    }

    // deal 7 cards to each player
    for(int i = 0; i < 7; i++){
        // one card to player 1 
        int p1 = shuffledDeck.front(); 
        shuffledDeck.pop(); 
        player1Cards.push(p1); 

        // one cad to player 2
        int p2 = shuffledDeck.front(); 
        shuffledDeck.pop(); 
        player2Cards.push(p2); 

    }

    
}


void Game::createDeckAndDealCondition(){
    // [0, 11] Hearts
    // [12, 23] Spades
    // [24, 35] Diamonds
    // [36, 47] Clubs
    vector<int> conditionPlayerCards = vector<int>(); 
    // choose a random suit 
    random_device rd;
    mt19937 rng(rd()); 
    uniform_int_distribution<int> uni(0, 3); 
    // might need to do: auto random_integer = uni(rng); instead
    int random_integer = uni (rng); 

    int min = 0; 
    int max = 0; 
    if(random_integer ==  0){
        // select 5 random from [0, 11]
        min = 0; 
        max = 11; 
        
    } else if (random_integer == 1){
        // select 5 random from [12, 23]
        min = 12;
        max = 23; 
        
    } else if (random_integer == 2){
        // select 5 random from [24, 35]
        min = 24; 
        max = 35; 

    } else {
        // select 5 random from [36, 47]
        min = 36;
        max = 47; 
    }


    // choose 5 cards from the chosen suit 
    uniform_int_distribution<int> uni2(min, max);
        // cannot get the same number more than twice... keep drawing until you get that? 
        int drawn_cards = 0; 
        while(drawn_cards < conditionCards){
            int rand_int = uni2 (rng);
            int counter = 0; 
            for(int j = 0; j <  (int) conditionPlayerCards.size(); j++){
                if(conditionPlayerCards.at(j) == rand_int){
                    counter++; 
                }
            } 
            if(counter < 2){
                conditionPlayerCards.push_back(rand_int); 
                drawn_cards++; 
            }
        }

   
   

    vector<int> temp_deck = vector<int>(); 
    // shuffle and enqueue the deck 
    for(int i = 0; i < 48; i++){
        int toPush = 2; 
        for(int j = 0; j < (int) conditionPlayerCards.size(); j++){
            if(conditionPlayerCards.at(j) == i){
                toPush--; 
            }
        }

        for(int j = 0; j < toPush; j++){
            temp_deck.push_back(i); 
        }
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(temp_deck.begin(), temp_deck.end(), default_random_engine(seed)); 

    // put everything in the queue
    for(int i = 0; i < (int) temp_deck.size(); i++){
        shuffledDeck.push(temp_deck.at(i)); 
    }

    // set the condition player and push their cards to their hand 
     // decide which player 
    uniform_int_distribution<int> uni3(0, 1);
    int rand_int3 = uni3(rng); 
    if(rand_int3 == 0){
        conditionPlayer = 1; 
        // enquue 
        for(int i = 0; i < (int) conditionPlayerCards.size(); i++){
            player1Cards.push(conditionPlayerCards.at(i)); 
        }
        
        // draw additional cards 
        for(int i = 0; i < (7-conditionCards); i++){
            int cardDrawn = shuffledDeck.front();
            shuffledDeck.pop(); 
            player1Cards.push(cardDrawn); 
        }
        
    } else {
        conditionPlayer = 2; 
        // enque 
         for(int i = 0; i < (int) conditionPlayerCards.size(); i++){
            player2Cards.push(conditionPlayerCards.at(i)); 
        }
        
        // draw additional cards 
        for(int i = 0; i < (7-conditionCards); i++){
            int cardDrawn = shuffledDeck.front();
            shuffledDeck.pop(); 
            player2Cards.push(cardDrawn); 
        }
        
    }
    
    

    // deal to the non condition player 
    if(conditionPlayer == 1){
        // deal to player 2
        for(int i = 0; i < 7; i++){
            int cardDrawn = shuffledDeck.front(); 
            shuffledDeck.pop(); 
            player2Cards.push(cardDrawn); 
        }

    } else {
        // deal to player 1
        for(int i = 0; i < 7; i++){
            int cardDrawn = shuffledDeck.front(); 
            shuffledDeck.pop(); 
            player1Cards.push(cardDrawn); 
        }
    }



}



void Game::createMapping(){
    
    cardMapping = vector<vector<pair<int, int>>>(); 
    // initialization 
    for(int i = 0; i < 48; i++){
        vector<pair<int,int>> temp = vector<pair<int, int>>(); 
        temp.push_back(make_pair<int, int>(0, 0)); 
        temp.push_back(make_pair<int, int>(0, 0)); 
       // temp.push_back(make_pair<int, int>(0, 0 )); 
        cardMapping.push_back(temp); 
    }

    // assignments 

    // A Hearts
    cardMapping[0][0] = make_pair<int, int>(1, 5); 
    cardMapping[0][1] = make_pair<int, int>(4, 6); 

    // 2 Hearts
    cardMapping[1][0] = make_pair<int, int>(5, 4); 
    cardMapping[1][1] = make_pair<int, int>(8, 7); 

    // 3 Hearts
    cardMapping[2][0] = make_pair<int, int>(8, 8); 
    cardMapping[2][1] = make_pair<int, int>(5, 5); 

    // 4 Hearts
    cardMapping[3][0] = make_pair<int, int>(4, 5); 
    cardMapping[3][1] = make_pair<int, int>(7, 8); 

    // 5 Hearts
    cardMapping[4][0] = make_pair<int, int>(4, 4); 
    cardMapping[4][1] = make_pair<int, int>(6, 8); 

    //6 Hearts
    cardMapping[5][0] = make_pair<int, int>(5, 8); 
    cardMapping[5][1] = make_pair<int, int>(4, 3); 

    //7 Hearts
    cardMapping[6][0] = make_pair<int, int>(4, 8); 
    cardMapping[6][1] = make_pair<int, int>(5, 3); 

    //8 Hearts
    cardMapping[7][0] = make_pair<int, int>(3, 8); 
    cardMapping[7][1] = make_pair<int, int>(6, 3); 

    //9 Hearts
    cardMapping[8][0] = make_pair<int, int>(2, 8); 
    cardMapping[8][1] = make_pair<int, int>(6, 4); 

    //10 Hearts
    cardMapping[9][0] = make_pair<int, int>(1, 8); 
    cardMapping[9][1] = make_pair<int, int>(6, 5);

    //Q Hearts
    cardMapping[10][0] = make_pair<int, int>(1, 7); 
    cardMapping[10][1] = make_pair<int, int>(6, 6);  

    //K Hearts
    cardMapping[11][0] = make_pair<int, int>(1, 6); 
    cardMapping[11][1] = make_pair<int, int>(5, 6); 

    //A Spades
    cardMapping[12][0] = make_pair<int, int>(2, 1); 
    cardMapping[12][1] = make_pair<int, int>(4, 9); 

    //2 Spades
    cardMapping[13][0] = make_pair<int, int>(0, 1); 
    cardMapping[13][1] = make_pair<int, int>(8, 6); 

    //3 Spades
    cardMapping[14][0] = make_pair<int, int>(0, 2); 
    cardMapping[14][1] = make_pair<int, int>(8, 5); 

    //4 Spades
    cardMapping[15][0] = make_pair<int, int>(0, 3); 
    cardMapping[15][1] = make_pair<int, int>(8, 4); 

    //5 Spades
    cardMapping[16][0] = make_pair<int, int>(0, 4); 
    cardMapping[16][1] = make_pair<int, int>(8, 3); 

    //6 Spades
    cardMapping[17][0] = make_pair<int, int>(0, 5); 
    cardMapping[17][1] = make_pair<int, int>(8, 2); 

    //7 Spades
    cardMapping[18][0] = make_pair<int, int>(0, 6); 
    cardMapping[18][1] = make_pair<int, int>(8, 1); 

    //8 Spades
    cardMapping[19][0] = make_pair<int, int>(0, 7); 
    cardMapping[19][1] = make_pair<int, int>(7, 1); 

    //9 Spades
    cardMapping[20][0] = make_pair<int, int>(0, 8); 
    cardMapping[20][1] = make_pair<int, int>(6, 1); 

    //10 Spades
    cardMapping[21][0] = make_pair<int, int>(1, 9); 
    cardMapping[21][1] = make_pair<int, int>(5, 1); 

    // Q Spades
    cardMapping[22][0] = make_pair<int, int>(2, 9); 
    cardMapping[22][1] = make_pair<int, int>(4, 1); 

    // K Spades
    cardMapping[23][0] = make_pair<int, int>(3, 9); 
    cardMapping[23][1] = make_pair<int, int>(3, 1); 

    //A Diamonds
    cardMapping[24][0] = make_pair<int, int>(7, 6); 
    cardMapping[24][1] = make_pair<int, int>(9, 1); 

    //2 Diamonds
    cardMapping[25][0] = make_pair<int, int>(2, 2); 
    cardMapping[25][1] = make_pair<int, int>(5, 9); 

    //3 Diamonds
    cardMapping[26][0] = make_pair<int, int>(2, 3); 
    cardMapping[26][1] = make_pair<int, int>(6, 9); 

    //4 Diamonds
    cardMapping[27][0] = make_pair<int, int>(2, 4); 
    cardMapping[27][1] = make_pair<int, int>(7, 9); 

    //5 Diamonds
    cardMapping[28][0] = make_pair<int, int>(2, 5); 
    cardMapping[28][1] = make_pair<int, int>(8, 9); 

    //6 Diamonds
    cardMapping[29][0] = make_pair<int, int>(2, 6); 
    cardMapping[29][1] = make_pair<int, int>(9, 8); 

    //7 Diamonds
    cardMapping[30][0] = make_pair<int, int>(2, 7); 
    cardMapping[30][1] = make_pair<int, int>(9, 7); 

    //8 Diamonds
    cardMapping[31][0] = make_pair<int, int>(3, 7); 
    cardMapping[31][1] = make_pair<int, int>(9, 6); 

    //9 Diamonds
    cardMapping[32][0] = make_pair<int, int>(4, 7); 
    cardMapping[32][1] = make_pair<int, int>(9, 5); 

    //10 Diamonds
    cardMapping[33][0] = make_pair<int, int>(5, 7); 
    cardMapping[33][1] = make_pair<int, int>(9, 4); 

    //Q Diamonds
    cardMapping[34][0] = make_pair<int, int>(6, 7); 
    cardMapping[34][1] = make_pair<int, int>(9, 3); 

    //K Diamonds
    cardMapping[35][0] = make_pair<int, int>(7, 7); 
    cardMapping[35][1] = make_pair<int, int>(9, 2); 

    //A Clubs
    cardMapping[36][0] = make_pair<int, int>(7, 5); 
    cardMapping[36][1] = make_pair<int, int>(8, 0);

    //2 Clubs
    cardMapping[37][0] = make_pair<int, int>(1, 4); 
    cardMapping[37][1] = make_pair<int, int>(3, 6);  

    //3 Clubs
    cardMapping[38][0] = make_pair<int, int>(1, 3); 
    cardMapping[38][1] = make_pair<int, int>(3, 5); 

    //4 Clubs
    cardMapping[39][0] = make_pair<int, int>(1, 2); 
    cardMapping[39][1] = make_pair<int, int>(3, 4); 

    //5 Clubs
    cardMapping[40][0] = make_pair<int, int>(1, 1); 
    cardMapping[40][1] = make_pair<int, int>(3, 3); 

    //6 Clubs
    cardMapping[41][0] = make_pair<int, int>(1, 0); 
    cardMapping[41][1] = make_pair<int, int>(3, 2); 

    //7 Clubs
    cardMapping[42][0] = make_pair<int, int>(2, 0); 
    cardMapping[42][1] = make_pair<int, int>(4, 2); 

    //8 Clubs
    cardMapping[43][0] = make_pair<int, int>(3, 0); 
    cardMapping[43][1] = make_pair<int, int>(5, 2); 

    //9 Clubs
    cardMapping[44][0] = make_pair<int, int>(4, 0); 
    cardMapping[44][1] = make_pair<int, int>(6, 2); 

    //10 Clubs
    cardMapping[45][0] = make_pair<int, int>(5, 0); 
    cardMapping[45][1] = make_pair<int, int>(7, 2); 

    //Q Clubs
    cardMapping[46][0] = make_pair<int, int>(6, 0); 
    cardMapping[46][1] = make_pair<int, int>(7, 3); 

    //K Clubs
    cardMapping[47][0] = make_pair<int, int>(7, 0); 
    cardMapping[47][1] = make_pair<int, int>(7, 4); 

    

}

bool Game::isDeckEmpty(){
    return(shuffledDeck.empty()); 
}

bool Game::isPlayerEmpty(){
    return(player1Cards.empty()); 
}

bool Game::checkSequence(int player){
    int x = lastPlacedToken.first;
    int y = lastPlacedToken.second; 
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
    for(int row = 0; row < (int)gameboard.size(); row++){
        int col = gameboard.at(row).at(y); 
        if(col == 3 || col == player){
            counter++; 
        } else {
            counter = 0; 
        }

        if(counter == sequenceLength){
            return true;
        }
    }

    return false; 
    
}

bool Game::checkHorizontal(int player, int y){
    vector<int> row = gameboard.at(y); 
    int counter = 0; 
    for(int i = 0; i < (int) row.size(); i++){
        if(row.at(i) == 3 || i == player){
            counter++; 
        } else {
            // reset counter 
            counter = 0; 
        }

        if(counter == sequenceLength){
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
    while(x < (int) gameboard.size() && y  < (int) gameboard.size()){
        if(gameboard[x][y] == 3 || gameboard[x][y] == player){
            counter++; 
        } else {
            counter = 0; 
        }

        if(counter == sequenceLength){
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
    queue<int> *playerCards; 
    if(player == 1){
        playerCards = &(player1Cards); 

    } else if (player == 2){
        playerCards = &(player2Cards); 

    }

    int card = playerCards->front(); 
        playerCards->pop(); 
        // TODO: look up the card here
        pair<int, int> position = cardMapping.at(card).at(0); 

        // TODO: Randomize choosing between position 1 and position 2
        bool pos1Result = placeToken(player, position); 
        //cout << "Pos1Result: " <<  pos1Result << endl; 
        if(pos1Result == false){
            // position1 has been taken, try position2
            position = cardMapping.at(card).at(1); 
            placeToken(player, position); 
            //cout << "Played at pos2" << endl; 
        }
}

int Game::getConditionPlayer(){
    return conditionPlayer; 
}

void Game::printPlayerCards(int player){
    queue<int> temp; 
    if(player == 1){
        temp = player1Cards; 
    } else if (player == 2){
        temp = player2Cards; 
    }
    cout << "Player " << player << " cards: "; 
    for(int i = 0; i < 7; i++){
        int toPrint = temp.front(); 
        cout << toPrint << " "; 
        temp.pop(); 
        temp.push(toPrint); 
    }
    cout << endl; 
}

bool Game::placeToken(int player, pair<int, int> location){
    //cout << "Test: " << location.first << ", " << location.second << endl; 
    if(gameboard[location.first][location.second] == 0){
        gameboard[location.first][location.second] = player; 
       // cout << "Player " << player << " played at " << location.first << ", " << location.second << endl; 
        lastPlacedToken = location; 
        return true; 
    } 

    return false; 

}

void Game::printBoard(){
    for(int i = 0; i < (int) gameboard.size(); i++){
       
        for(int j = 0; j < (int) gameboard.size(); j++){
            cout << gameboard[i][j] << " " ; 
        }
        cout << endl; 
    }
    cout << endl; 
}