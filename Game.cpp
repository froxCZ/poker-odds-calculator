/* 
 * File:   Game.cpp
 * Author: frox
 * 
 * Created on May 22, 2014, 12:48 PM
 */

#include "Game.h"
#include <iostream>
#include <stdio.h>

Game::Game(int playersCnt) {
    this->playersCnt = playersCnt;
    players = new CardSet*[playersCnt];
    for (int i = 0; i < playersCnt; i++) {
        players[i] = new CardSet(i);
    }
}

Game::Game(const Game& orig) {
    cout << "Game::Game not implemented!" << endl;
}

Game::~Game() {
    for (int i = 0; i < playersCnt; i++)delete players[i];
    delete[] players;
}
void Game::SetHand(string card1, string card2){
    players[0]->AddCard(card1);
    players[0]->AddCard(card2);
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "Table: \t" << game.table << endl;
    stringstream idStr;
    for(int i=0;i<game.playersCnt;i++){        
        idStr.str("");
        idStr.clear();
        idStr << i;
        os << "player"<<idStr.str()<<"\t"<<*(game.players[i])<<endl;
    }
}
