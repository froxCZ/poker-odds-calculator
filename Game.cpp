/* 
 * File:   Game.cpp
 * Author: frox
 * 
 * Created on May 22, 2014, 12:48 PM
 */

#include "Game.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

Game::Game(int playersCnt) {
    this->playersCnt = playersCnt;
    players = new CardSet*[playersCnt];
    for (int i = 0; i < playersCnt; i++) {
        players[i] = new CardSet(i);
    }
    Reset();
}

Game::Game(const Game& orig) {
    cout << "Game::Game not implemented!" << endl;
}

Game::~Game() {
    for (int i = 0; i < playersCnt; i++)delete players[i];
    delete[] players;
}

void Game::Reset() {
    for (int i = 0; i < playersCnt; i++) {
        players[i]->Reset();
    }
    table.Reset();
    for (int iRank = ACE; iRank >= CARD_2; iRank--) {
        for (int iSuit = 0; iSuit < 4; iSuit++) {
            playedCards[iRank][iSuit] = false;
        }
    }
    turnCounter = START;
}

void Game::SetFlop(string card) {
    table.AddCard(card);
    if (turnCounter != HAND_SET) {
        cout << "internal error - SetFlop NOT called after SetHand" << endl;
        return;
    }
    turnCounter = FLOP_SET;
}

void Game::SetHand(string card1, string card2) {
    players[0]->AddCard(card1);
    players[0]->AddCard(card2);
    turnCounter = HAND_SET;
}

inline int Game::GenerateRandom(int from, int to) {
    return rand() % (to - from) + from;
}

std::ostream& operator<<(std::ostream& os, const Game& game) {
    os << "Table:\t\t" << game.table << endl;
    stringstream idStr;
    for (int i = 0; i < game.playersCnt; i++) {
        idStr.str("");
        idStr.clear();
        idStr << i;
        os << "player" << idStr.str() << ":\t" << *(game.players[i]) << endl;
    }
    return os;
}
