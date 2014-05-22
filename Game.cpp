/* 
 * File:   Game.cpp
 * Author: frox
 * 
 * Created on May 22, 2014, 12:48 PM
 */

#include "Game.h"
#include <iostream>

Game::Game(int playersCnt) {
    this->playersCnt = playersCnt;
    players = new Player*[playersCnt];
    for (int i = 0; i < playersCnt; i++) {
        players[i] = new Player(i);
    }
}

Game::Game(const Game& orig) {
    cout << "Game::Game not implemented!" << endl;
}

Game::~Game() {
    for (int i = 0; i < playersCnt; i++)delete players[i];
    delete players;
}

std::ostream& operator<<(std::ostream& os, const Game& obj){
    os << "Game";
}
