#include "Game.h"

Game::Game(){
    setUpGameAny(); 

}

Game::Game(int n){
    setUpGameCondition(); 
}

void Game::setUpGameAny(){
    setUpBoard(); 
    // create card deck
    createDeckAndDealAny(); 
    // createMapping(); 
    conditionPlayer = 1; 


}

void Game::setUpGameCondition(){
    setUpBoard(); 

    createDeckAndDealCondition(); 
    //createMapping(); 
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
        while(drawn_cards < 5){
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

    // set the condition player and push their cards onto the deck
     // decide which player 
    uniform_int_distribution<int> uni3(0, 1);
    int rand_int3 = uni3(rng); 
    if(rand_int3 == 0){
        conditionPlayer = 1; 
        // enquue 
        for(int i = 0; i < (int) conditionPlayerCards.size(); i++){
            player1Cards.push(conditionPlayerCards.at(i)); 
        }
        // draw 2 more cards 
        for(int i = 0; i < 2; i++){
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
        // draw 2 more cards
        for(int i = 0; i < 2; i++){
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
        temp.push_back(make_pair<int, int>(0, 0 )); 
        cardMapping.push_back(temp); 
    }

    // assignments 

    // A Hearts
    cardMapping[0][0] = make_pair<int, int>(1, 5); 
    cardMapping[0][1] = make_pair<int, int>(4, 6); 

    // TODO: Mujtaba

}

bool Game::isDeckEmpty(){
    return(shuffledDeck.empty()); 
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

        if(counter == 5){
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
    while(x < (int) gameboard.size() && y  < (int) gameboard.size()){
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
    queue<int> playerCards; 
    if(player == 1){
        playerCards = player1Cards; 

    } else if (player == 2){
        playerCards = player2Cards; 

    }

    int card = playerCards.front(); 
        playerCards.pop(); 
        // TODO: look up the card here
        pair<int, int> position = cardMapping.at(card).at(0); 

        // TODO: Randomize choosing between position 1 and position 2
        bool pos1Result = placeToken(player, position); 
        if(pos1Result == false){
            // position1 has been taken, try position2
            position = cardMapping.at(card).at(0); 
            placeToken(player, position); 
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
    if(gameboard[location.first][location.second] == 0){
        gameboard[location.first][location.second] = player; 
        lastPlacedToken = location; 
        return true; 
    } 

    return false; 

}

