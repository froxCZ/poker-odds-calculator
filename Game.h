/* 
 * File:   Game.h
 * Author: frox
 *
 * Created on May 22, 2014, 12:48 PM
 */

#ifndef GAME_H
#define	GAME_H
#include "CardSet.h"
#include <string>
#include <list>

using namespace std;
class Game {
public:
    CardSet** players;
    int playersCnt;
    CardSet table;
    int turnCounter;
    bool playedCards[CARDS_CNT][SUITS_CNT];
    bool setHandToOther;
    int sharedCards;
    Game(int playersCnt);
    Game(const Game& orig);
    virtual ~Game();
    friend std::ostream& operator<<(std::ostream& os, const Game& obj);
    void Reset(); //reset variables, deals cards, puts 3 cards on river    
    int FinishGame(bool verbose); //runs turns to finish the game and returns winnerId. (O == me!!)
    void SetHand(string card1, string card2);
    void SetHandToOthers();
    void SetFlop(string card1,string card2,string card3);
    bool AddSharedCard(string card);
    bool AddSharedCard(int rank, int suit);
    void SetCardToPlayer(CardSet*player,int rank, int suit);
private:
    void SetCardToAll(int rank,int suit);
    bool RunTurn(); //does one turn and returns true. If game finished, returns false
    void DrawCard(int&rank,int&suit);
    inline int GenerateRandom(int from, int to);
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

