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
    setHandToOther = false;
    sharedCards = 0;
}

void Game::SetFlop(string card1, string card2, string card3) {    
    if (turnCounter != HAND_SET) {
        cout << "internal error - SetFlop NOT called after SetHand" << endl;
        return;
    }
    if (AddSharedCard(card1) &&
            AddSharedCard(card2) &&
            AddSharedCard(card3)) {
        turnCounter = FLOP_SET;
    } else {
        cout << "could not set flop" << endl;
    }
}

bool Game::AddSharedCard(string card) {
    int rank, suit;
    if (CardSet::StrToCard(card, rank, suit) == false)return false;
    AddSharedCard(rank, suit);
    return true;
}

bool Game::AddSharedCard(int rank, int suit) {
    SetCardToAll(rank, suit);
    sharedCards++;
    return true;
}

int Game::FinishGame(bool verbose) {
    while (RunTurn());
    if (setHandToOther == false)SetHandToOthers();
    int maxScore = players[0]->GetFigureScore();
    int winnerId = 0;
    for (int i = 1; i < playersCnt; i++) {
        int otherScore = players[i]->GetFigureScore();
        if (otherScore > maxScore) {
            maxScore = otherScore;
            winnerId = i;
        }
    }
    if (verbose) {
        if (winnerId == 0) {
            cout << "I won with ";
        } else {
            cout << "player" << winnerId << " won with ";
        }
        cout << CardSet::GetScoreName(maxScore) << "!" << endl;
    }
    return winnerId;
}

void Game::SetHand(string card1, string card2) {
    int rank, suit;
    if (CardSet::StrToCard(card1, rank, suit) == false)return;
    SetCardToPlayer(players[0], rank, suit);
    if (CardSet::StrToCard(card2, rank, suit) == false)return;
    SetCardToPlayer(players[0], rank, suit);
    turnCounter = HAND_SET;
}

void Game::SetHandToOthers() {
    int rank, suit;
    for (int iPlayer = 1; iPlayer < playersCnt; iPlayer++) {
        DrawCard(rank, suit);
        SetCardToPlayer(players[iPlayer], rank, suit);
        DrawCard(rank, suit);
        SetCardToPlayer(players[iPlayer], rank, suit);
    }
}

void Game::SetCardToPlayer(CardSet*player, int rank, int suit) {
    player->AddCard(rank, suit);
    playedCards[rank][suit] = true;
}

void Game::SetCardToAll(int rank, int suit) {
    for (int i = 0; i < playersCnt; i++) {
        SetCardToPlayer(players[i], rank, suit);
    }
    SetCardToPlayer(&table, rank, suit);
}

bool Game::RunTurn() {
    int rank, suit;
    if (sharedCards != 5) {
        DrawCard(rank, suit);
        AddSharedCard(rank, suit);
        return true;
    }
    return false;
}

void Game::DrawCard(int& rank, int& suit) {
    do {//TODO: can get to infinite loop if all cards are drawn.
        rank = GenerateRandom(CARD_2, ACE);
        suit = GenerateRandom(0, 3);
    } while (playedCards[rank][suit] == true);
    playedCards[rank][suit] = true;
}

inline int Game::GenerateRandom(int from, int to) {
    to++;
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
