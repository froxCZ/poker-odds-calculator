/* 
 * File:   CardSet.h
 * Author: frox
 *
 * Created on May 22, 2014, 1:51 PM
 */

#ifndef CARDSET_H
#define	CARDSET_H
#include "Constants.h"
#include <sstream>
#include <list>

class CardSet {
    #define RANK_GAP 1000000
    enum RANK {HIGH_CARD = 10,ONE_PAIR=3*RANK_GAP,TWO_PAIRS=4*RANK_GAP,THREE=5*RANK_GAP,FLUSH=6*RANK_GAP,FULL_HOUSE=7*RANK_GAP,POKER=8*RANK_GAP,STRAIGHT_FLUSH=9*RANK_GAP};
public:
    int cards[CARDS_CNT];
    int suits[SUITS_CNT];    
    int set[CARDS_CNT][SUITS_CNT];
    int cardsCnt;   
    CardSet();
    CardSet(const CardSet& orig);
    int evaluate();
    virtual ~CardSet();
    friend std::ostream& operator<<(std::ostream& os, const CardSet& obj);
    static short StrToCard(char*str);
    static char* CardToSuit(short cardId);    
private:
    int GotStraightFlush();
    int GotPoker();
    int GotFullHouse();
    int GotFlush();
    int GotStraight();
    int GotThree();
    int GotTwoPairs();
    int GotOnePair();
    int GotHighCard();
   

};

#endif	/* CARDSET_H */

