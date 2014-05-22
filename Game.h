/* 
 * File:   Game.h
 * Author: frox
 *
 * Created on May 22, 2014, 12:48 PM
 */

#ifndef GAME_H
#define	GAME_H
#include "Player.h"
#include "CardSet.h"
#include <string>
#include <list>

using namespace std;

class Game {
public:
    Player** players;
    int playersCnt;
    CardSet table;
    int turnCounter;
    list<int> playedCardsIndexes;
    //we keep track of played cards, instead of cards left, since amount of played cards will be lower than stack stacks -> faster to search
    static char cardsIndex[52];
    Game(int playersCnt);
    Game(const Game& orig);
    virtual ~Game();
    friend std::ostream& operator<<(std::ostream& os, const Game& obj);
    void RunSimulation();
    void StartGame(); //reset variables, deals cards, puts 3 cards on river    
    void FinishGame(); //runs turns to finish the game and prints results and winner.
    void SetHand(string card1, string card2);
    void SetRiver(string cards[], int cardsCnt);
private:
    void RunTurn(); //does one turn. If game finished, does nothing.
    int GetCardFromDeck();
    void CardToRiver();
    inline short GenerateRandom(int from, int to);
};
/*
 * Card representation for indexing:
 * Number of each card = value of card + color number
 * value of cards goes from 20 to 100 and continues over 110 to 140 over J,Q,K,A.
 * color goes from 0 to 3 for colors respectively: hearts, diamonds, clubs, spades
 * so J of hearts will be 110 + 0 = 110
 * and A of clubs is 140 + 2 = 142
 */

#endif	/* GAME_H */

